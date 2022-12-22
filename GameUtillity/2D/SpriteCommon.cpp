#include "SpriteCommon.h"
#include "CalcTransform.h"
#include <cassert>
#include <memory>

using YGame::SpriteCommon;
using YDX::PipelineSet;

YMath::Mat4 SpriteCommon::projection_ = YMath::Mat4::Identity();
PipelineSet SpriteCommon::pplnSet_;
YGame::TextureManager* SpriteCommon::pTexManager_ = nullptr;

void SpriteCommon::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/SpriteVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/SpritePS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	psBlob_ = ps;
}

void SpriteCommon::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
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
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		}
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
		pplnDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
		pplnDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

		// ラスタライザの設定
		pplnDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

		// デプスステンシルステートの設定
		pplnDesc_.DepthStencilState.DepthEnable = false; // 深度テストしない
		pplnDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き

		// 図形の形状設定
		pplnDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}

	// プリミティブ形状の設定
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // 三角形ストリップ
}

void SpriteCommon::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pTexManager_);
	pTexManager_ = state.pTexManager_;
	projection_ = YMath::MatOrthoGraphic();
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	pplnSet_.Initialize(pplnState.get(), state.rootParams_);
}

void SpriteCommon::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}
