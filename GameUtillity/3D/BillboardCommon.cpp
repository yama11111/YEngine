#include "BillboardCommon.h"
#include <cassert>
#include <memory>

using YGame::BillboardCommon;
using YGame::TextureManager;
using YDX::PipelineSet;

PipelineSet BillboardCommon::pplnSet_;
TextureManager* BillboardCommon::pTexManager_ = nullptr;

void BillboardCommon::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* gs = nullptr;
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/BillboardVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// ジオメトリシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/BillboardGS.hlsl", "main", "gs_5_0", gs, errorBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/BillboardPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	gsBlob_ = gs;
	vsBlob_ = vs;
	psBlob_ = ps;
}

void BillboardCommon::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
{
	// シェーダー読み込み
	ShaderSet shdrs;
	shdrs.Load(errorBlob_);

	// 頂点レイアウトの設定
	inputLayout_ =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};

	// テクスチャサンプラーの設定
	{
		D3D12_STATIC_SAMPLER_DESC sampleDesc{};
		sampleDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横折り返し   (タイリング)
		sampleDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 縦折り返し   (タイリング)
		sampleDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 奥行折り返し (タイリング)
		sampleDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // ボーダーの時は黒
		sampleDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 全てリニア補間
		sampleDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミニマップ最大値
		sampleDesc.MinLOD = 0.0f;              // ミニマップ最小値
		sampleDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		sampleDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーからのみ使用可能

		sampleDesc_.push_back(sampleDesc);
	}

	// パイプライン設定
	{
		// シェーダーの設定
		pplnDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
		pplnDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
		pplnDesc_.GS.pShaderBytecode = shdrs.gsBlob_.Get()->GetBufferPointer();
		pplnDesc_.GS.BytecodeLength = shdrs.gsBlob_.Get()->GetBufferSize();
		pplnDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
		pplnDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

		// ラスタライザの設定
		pplnDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

		// デプスステンシルステートの設定
		pplnDesc_.DepthStencilState.DepthEnable = false; // 深度テストしない
		pplnDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き

		// 図形の形状設定
		pplnDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

		// 画像の透過適用
		//pplnDesc_.BlendState.AlphaToCoverageEnable = true;
	}

	// プリミティブ形状の設定
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; // ポイントリスト
}


void BillboardCommon::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pTexManager_);
	pTexManager_ = state.pTexManager_;
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	pplnSet_.Initialize(pplnState.get(), state.rootParams_);
}

void BillboardCommon::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}
