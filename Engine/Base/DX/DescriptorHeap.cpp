#include "DescriptorHeap.h"
#include "YAssert.h"
#include <imgui.h>

using YDX::DescriptorHeap;

ID3D12Device* DescriptorHeap::spDevice_ = nullptr;
ID3D12GraphicsCommandList* DescriptorHeap::spCmdList_ = nullptr;

void DescriptorHeap::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList)
{
	assert(pDevice);
	assert(pCmdList);

	spDevice_  = pDevice;
	spCmdList_ = pCmdList;
}

void DescriptorHeap::Initialize()
{

	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見えるように
	heapDesc.NumDescriptors = MaxSRVCount_ + MaxUAVCount_ + MaxCBVCount_;

	// 設定をもとにデスクリプタヒープ(SRV,UAV,CBV用)を生成
	Result(spDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_)));


	// インクリメントサイズ取得
	incSize_ = spDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);


	// カウント初期化
	immutableCounter_.ResetCount();
	mutableCounter_.ResetCount();


	// CPU の先頭ハンドルを取得
	immutableCounter_.startHandle_.cpu_ = mutableCounter_.startHandle_.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();

	// GPU の先頭ハンドルを取得
	immutableCounter_.startHandle_.gpu_ = mutableCounter_.startHandle_.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();


	// 全不変許容カウント
	UINT AllImmutableCount = ImmutableSRVCount_ + ImmutableUAVCount_ + ImmutableCBVCount_;

	// 不変許容カウント分だけハンドルを進める
	mutableCounter_.startHandle_.cpu_.ptr += static_cast<SIZE_T>(incSize_ * AllImmutableCount);
	mutableCounter_.startHandle_.gpu_.ptr += static_cast<SIZE_T>(incSize_ * AllImmutableCount);

}


DescriptorHeap::Handle DescriptorHeap::CreateSRV(
	ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, const bool isMutable)
{
	// SRV追加
	Handle handle = AddSRV(isMutable);

	// ハンドルの指す位置にSRV作成
	spDevice_->CreateShaderResourceView(buff, &srvDesc, handle.cpu_);

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateUAV(
	ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc, const bool isMutable)
{
	// UAV追加
	Handle handle = AddUAV(isMutable);

	// ハンドルの指す位置にUAV作成
	spDevice_->CreateUnorderedAccessView(buff, nullptr, &uavDesc, handle.cpu_);

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateCBV(
	const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, const bool isMutable)
{
	// CBV追加
	Handle handle = AddCBV(isMutable);

	// ハンドルの指す位置にCBV作成
	spDevice_->CreateConstantBufferView(&cbvDesc, handle.cpu_);

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::AddSRV(const bool isMutable)
{
	// 不変カウントが許容値を超えたら弾く
	assert(immutableCounter_.srvCount_ < ImmutableSRVCount_);
	// カウントが最大値を超えたら弾く
	assert(immutableCounter_.srvCount_ + mutableCounter_.srvCount_ < MaxSRVCount_);


	// 戻り値用
	Handle handle{};

	// SRVカウント
	UINT srvCount = 0;

	// 既に使っている分
	UINT alreadyCount = 0;


	// 可変なら可変用
	if (isMutable)
	{
		// 値代入
		handle = mutableCounter_.startHandle_;
		srvCount = mutableCounter_.srvCount_;

		// 許容値分
		alreadyCount = ImmutableSRVCount_;

		// カウントを進める
		mutableCounter_.srvCount_++;
	}
	// それ以外なら不変用
	else
	{
		// 値代入
		handle = immutableCounter_.startHandle_;
		srvCount = immutableCounter_.srvCount_;

		// 0
		alreadyCount = 0;

		// カウントを進める
		immutableCounter_.srvCount_++;
	}

	// SRVがある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (srvCount + alreadyCount));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (srvCount + alreadyCount));

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::AddUAV(const bool isMutable)
{
	// 不変カウントが許容値を超えたら弾く
	assert(immutableCounter_.uavCount_ < ImmutableUAVCount_);
	// カウントが最大値を超えたら弾く
	assert(immutableCounter_.uavCount_ + mutableCounter_.uavCount_ < MaxUAVCount_);


	// 戻り値用
	Handle handle{};

	// UAVカウント
	UINT uavCount = 0;

	// 既に使っている分
	UINT alreadyCount = 0;


	// 可変なら可変用
	if (isMutable)
	{
		// 値代入
		handle = mutableCounter_.startHandle_;
		uavCount = mutableCounter_.uavCount_;

		// 最大SRV + 許容値分
		alreadyCount = MaxSRVCount_ + ImmutableUAVCount_;

		// カウントを進める
		mutableCounter_.uavCount_++;
	}
	// それ以外なら不変用
	else
	{
		// 値代入
		handle = immutableCounter_.startHandle_;
		uavCount = immutableCounter_.uavCount_;

		// 最大SRV分
		alreadyCount = MaxSRVCount_;

		// カウントを進める
		immutableCounter_.uavCount_++;
	}

	// UAV + 最大SRVがある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount + alreadyCount));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount + alreadyCount));

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::AddCBV(const bool isMutable)
{
	// 不変カウントが許容値を超えたら弾く
	assert(immutableCounter_.cbvCount_ < ImmutableCBVCount_);
	// カウントが最大値を超えたら弾く
	assert(immutableCounter_.cbvCount_ + mutableCounter_.cbvCount_ < MaxCBVCount_);


	// 戻り値用
	Handle handle{};

	// CBVカウント
	UINT cbvCount = 0;

	// 既に使っている分
	UINT alreadyCount = 0;


	// 可変なら可変用
	if (isMutable)
	{
		// 値代入
		handle = mutableCounter_.startHandle_;
		cbvCount = mutableCounter_.cbvCount_;

		// 最大SRV + 最大UAV + 許容値分
		alreadyCount = MaxSRVCount_ + MaxUAVCount_ + ImmutableCBVCount_;

		// カウントを進める
		mutableCounter_.cbvCount_++;
	}
	// それ以外なら不変用
	else
	{
		// 値代入
		handle = immutableCounter_.startHandle_;
		cbvCount = immutableCounter_.cbvCount_;

		// 最大SRV + 最大UAV分
		alreadyCount = MaxSRVCount_ + MaxUAVCount_;

		// カウントを進める
		immutableCounter_.cbvCount_++;
	}

	// CBV + 最大SRV + 最大UAVがある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount + alreadyCount));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount + alreadyCount));

	// ハンドルを返す
	return handle;
}

void DescriptorHeap::SetDrawCommand()
{
	// SRVヒープの設定コマンド
	ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap_.Get() };
	spCmdList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}


void DescriptorHeap::ShowCount()
{
	ImGui::Begin("DescriptorCount");
	
	ImGui::Text("----- Immutable -----");
	{
		ImGui::Text("SRV : %u", immutableCounter_.srvCount_);
		ImGui::Text("UAV : %u", immutableCounter_.uavCount_);
		ImGui::Text("CBV : %u", immutableCounter_.cbvCount_);
	}
	ImGui::Text("----- Mutable -----");
	{
		ImGui::Text("SRV : %u", mutableCounter_.srvCount_);
		ImGui::Text("UAV : %u", mutableCounter_.uavCount_);
		ImGui::Text("CBV : %u", mutableCounter_.cbvCount_);
	}

	ImGui::End();
}