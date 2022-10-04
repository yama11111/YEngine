#include "PipelineState.h"
#include "Utility/Result.h"

using DX::PipelineState;
using DX::Utility::Result;

DX::Device* PipelineState::dev = nullptr;

PipelineState::PipelineState() :
	blendDesc(desc.BlendState.RenderTarget[0])
{
}

void DX::PipelineState::StaticInit()
{
	dev = Device::GetInstance();
}

void DX::PipelineState::Create(ID3D12RootSignature* rootSignature, ShaderSet& shaders,
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout, const int dimension)
{
	// シェーダーの設定
	desc.VS.pShaderBytecode = shaders.vsBlob->GetBufferPointer();
	desc.VS.BytecodeLength = shaders.vsBlob->GetBufferSize();
	desc.PS.pShaderBytecode = shaders.psBlob->GetBufferPointer();
	desc.PS.BytecodeLength = shaders.psBlob->GetBufferSize();

	// サンプルマスクの設定
	desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない
	desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	desc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	// ブレンドステート
	blendDesc = desc.BlendState.RenderTarget[0];
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

	blendDesc.BlendEnable = true;                // ブレンドを有効にする
	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // ソースの値を100%使う
	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // デストの値を  0%使う

	// 半透明合成
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // ソースのアルファ値
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - ソースのアルファ値

	// 頂点レイアウトの設定
	desc.InputLayout.pInputElementDescs = inputLayout.data();
	desc.InputLayout.NumElements = (UINT)inputLayout.size();
	// 図形の形状設定
	desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// その他の設定
	desc.NumRenderTargets = 1; // 描画対象は1つ
	desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	desc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// パイプラインにルートシグネチャをセット
	desc.pRootSignature = rootSignature;

	switch (dimension)
	{
	case Two:
		// ラスタライザの設定
		desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

		// デプスステンシルステートの設定
		desc.DepthStencilState.DepthEnable = false; // 深度テストしない
		desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き
		break;
	case Three:
		// ラスタライザの設定
		desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング

		// デプスステンシルステートの設定
		desc.DepthStencilState.DepthEnable = true; // 深度テスト
		desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
		desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
		desc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット
		break;
	default:
		Result::Assert(false);
		return;
		break;
	}

	// パイプランステートの生成
	CreateState();
}

void PipelineState::ChangeSolid()
{
	// ポリゴン内塗りつぶし
	desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	CreateState();
}
void PipelineState::ChangeWire()
{
	// ワイヤーフレーム
	desc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	CreateState();
}

void PipelineState::SetBlendAdd()
{
	// 加算合成
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // ソースの値を100%使う
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // デストの値を100%使う
	CreateState();
}
void PipelineState::SetBlendSub()
{
	// 減算合成
	blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT; // 減算(デスト - ソース)
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // ソースの値を100%使う
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // デストの値を100%使う
	CreateState();
}
void PipelineState::SetBlendInversion()
{
	// 色反転
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR; // 1.0f - デストカラーの値
	blendDesc.DestBlend = D3D12_BLEND_ZERO;          // デストの値を  0%使う
	CreateState();
}
void PipelineState::SetBlendAlpha()
{
	// 半透明合成
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // ソースのアルファ値
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - ソースのアルファ値
	CreateState();
}

ID3D12PipelineState* DX::PipelineState::Get()
{
	return pplnState.Get();
}

void PipelineState::CreateState()
{
	// パイプランステートの生成
	Result::Check(dev->Get()->
		CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pplnState)));
}
