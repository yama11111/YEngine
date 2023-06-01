#include "PipelineSet.h"
#include "YAssert.h"
#include <memory>

using YDX::PipelineSet;

ID3D12Device* PipelineSet::spDevice_ = nullptr;
ID3D12GraphicsCommandList* PipelineSet::spCmdList_ = nullptr;

void PipelineSet::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	spDevice_ = pDevice;
	spCmdList_ = pCommandList;
}

void PipelineSet::CreateRootSignature(
	const std::vector<D3D12_ROOT_PARAMETER>& rootParams,
	const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs)
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rsDesc{};
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rsDesc.pParameters = rootParams.data();					 // ルートパラメータの先頭アドレス
	rsDesc.NumParameters = (UINT)rootParams.size();			 // ルートパラメータ数
	rsDesc.pStaticSamplers = samplerDescs.data();			 // テクスチャサンプラーの先頭アドレス
	rsDesc.NumStaticSamplers = (UINT)samplerDescs.size();	 // テクスチャサンプラー数

	// ルートシグネチャのシリアライズ
	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr; // ルートシグネチャオブジェクト
	Result(D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, errorBlob.GetAddressOf()));

	// ルートシグネチャの生成
	Result(spDevice_->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature_)));
}

void PipelineSet::CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc)
{
	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature_.Get();

	// パイプランステートの生成
	Result(spDevice_->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState_)));
}

void PipelineSet::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// 未定義なら弾く
	assert(primitive != D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);

	// 代入
	primitive_ = primitive;
}

void PipelineSet::Initialize(
	const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplerDescs,
	const std::vector<D3D12_ROOT_PARAMETER>& rootParams,
	D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc,
	const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// ルートシグネチャ生成
	CreateRootSignature(rootParams, samplerDescs);

	// パイプラインステート生成
	CreatePipelineState(pipelineDesc);

	// プリミティブ形状設定
	SetPrimitiveTopology(primitive);
}

void PipelineSet::SetDrawCommand()
{
	// パイプラインステートの設定コマンド
	spCmdList_->SetPipelineState(pipelineState_.Get());

	// ルートシグネチャの設定コマンド
	spCmdList_->SetGraphicsRootSignature(rootSignature_.Get());

	// プリミティブ形状の設定コマンド
	spCmdList_->IASetPrimitiveTopology(primitive_);
}
