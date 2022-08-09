#include "DXPipelineState.h"
#include "Result.h"

DXPipelineState::DXPipelineState() :
	blendDesc(pipelineDesc.BlendState.RenderTarget[0])
{
}

void DXPipelineState::Create(ID3D12RootSignature* rootSignature, 
	DXShaderManager& shaderM, std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout)
{
	// グラフィックスパイプライン設定
	// シェーダーの設定
	pipelineDesc.VS.pShaderBytecode = shaderM.vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = shaderM.vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = shaderM.psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = shaderM.psBlob->GetBufferSize();

	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	// ブレンドステート
	blendDesc = pipelineDesc.BlendState.RenderTarget[0];
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
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout.data();
	pipelineDesc.InputLayout.NumElements = (UINT)inputLayout.size();
	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature;

	//// デプスステンシルステートの設定
	//pipelineDesc.DepthStencilState.DepthEnable = true; // 深度テスト
	//pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
	//pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
	//pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット

	dev = DXDevice::GetInstance();

	// パイプランステートの生成
	CreateState();
}

void DXPipelineState::ChangeSolid()
{
	// ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	CreateState();
}

void DXPipelineState::ChangeWire()
{
	// ワイヤーフレーム
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	CreateState();
}

void DXPipelineState::SetBlendAdd()
{
	// 加算合成
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // ソースの値を100%使う
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // デストの値を100%使う
	CreateState();
}

void DXPipelineState::SetBlendSub()
{
	// 減算合成
	blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT; // 減算(デスト - ソース)
	blendDesc.SrcBlend = D3D12_BLEND_ONE;   // ソースの値を100%使う
	blendDesc.DestBlend = D3D12_BLEND_ONE;  // デストの値を100%使う
	CreateState();
}

void DXPipelineState::SetBlendInversion()
{
	// 色反転
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR; // 1.0f - デストカラーの値
	blendDesc.DestBlend = D3D12_BLEND_ZERO;          // デストの値を  0%使う
	CreateState();
}

void DXPipelineState::SetBlendAlpha()
{
	// 半透明合成
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // ソースのアルファ値
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - ソースのアルファ値
	CreateState();
}

void DXPipelineState::CreateState()
{
	// パイプランステートの生成
	Result::Check(dev->Device()->
		CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState)));
}
