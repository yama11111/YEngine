#include "ConstBufferManager.h"
#include "YAssert.h"

using DX::ConstBufferManager;

ID3D12GraphicsCommandList* ConstBufferManager::pCmdList_ = nullptr;

void ConstBufferManager::StaticInitialize(ID3D12GraphicsCommandList* pCommandList)
{
	Assert(pCommandList != nullptr);
	pCmdList_ = pCommandList;
}

void ConstBufferManager::CreateCB(ConstBuffer<MaterialData>& cb, const Math::Vec4& color)
{
	// 生成用情報
	GPUResource::CreateStatus state;
	// ヒープ設定
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;
	// リソース設定
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Height = 1;
	state.resDesc_.Width = (sizeof(MaterialData) * 0xff) & ~0xff;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	cb.rsc_.Create(state);

	// 定数バッファのマッピング
	Result(cb.rsc_.Get()->Map(0, nullptr, (void**)&cb.map_));
	// 値を書きこむと自動的に転送される
	cb.map_->color_ = color;
}

void ConstBufferManager::CreateCB(ConstBuffer<TransformData>& cb)
{
	GPUResource::CreateStatus state;
	// ヒープ設定
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;
	// リソース設定
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Height = 1;
	state.resDesc_.Width = (sizeof(TransformData) * 0xff) & ~0xff;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	cb.rsc_.Create(state);

	// 定数バッファのマッピング
	Result(cb.rsc_.Get()->Map(0, nullptr, (void**)&cb.map_));
	// 値を書きこむと自動的に転送される
	cb.map_->mat_ = Math::Mat4::Identity();
}

void ConstBufferManager::SetDrawCommand(ConstBuffer<MaterialData>& cb)
{
	// 定数バッファビュー(マテリアル)の設定コマンド
	pCmdList_->SetGraphicsRootConstantBufferView(rpIndexM_, cb.rsc_.Get()->GetGPUVirtualAddress());
}

void ConstBufferManager::SetDrawCommand(ConstBuffer<TransformData>& cb)
{
	// 定数バッファビュー(3D変換行列)の設定コマンド
	pCmdList_->SetGraphicsRootConstantBufferView(rpIndexT_, cb.rsc_.Get()->GetGPUVirtualAddress());
}