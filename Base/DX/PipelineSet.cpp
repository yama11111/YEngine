#include "PipelineSet.h"
#include "YAssert.h"
#include <memory>

using YDX::PipelineSet;

ID3D12Device* PipelineSet::pDevice_ = nullptr;
ID3D12GraphicsCommandList* PipelineSet::pCmdList_ = nullptr;

void PipelineSet::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	pDevice_ = pDevice;
	pCmdList_ = pCommandList;
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
	Result(pDevice_->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature_)));
}

void PipelineSet::CreatePipelineState(
	D3D12_GRAPHICS_PIPELINE_STATE_DESC& pipelineDesc, 
	const std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout)
{
	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	// ブレンドステート
	D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDesc.BlendState.RenderTarget[0];
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

	blendDesc.BlendEnable = true;                // ブレンドを有効にする
	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; // 加算
	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;   // ソースの値を100%使う
	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO; // デストの値を  0%使う

	// 半透明合成
	blendDesc.BlendOp = D3D12_BLEND_OP_ADD;			 // 加算
	blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;      // ソースのアルファ値
	blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; // 1.0f - ソースのアルファ値

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout.data(); // 頂点レイアウトの先頭アドレス
	pipelineDesc.InputLayout.NumElements = (UINT)inputLayout.size(); // 頂点レイアウト数

	// その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature_.Get();

	// パイプランステートの生成
	Result(pDevice_->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState_)));
}

void PipelineSet::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitive)
{
	// 未定義なら弾く
	assert(primitive != D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);

	// 代入
	primitive_ = primitive;
}

void PipelineSet::Initialize(InitStatus& status)
{
	// ルートシグネチャ生成
	CreateRootSignature(status.rootParams_, status.samplerDescs_);

	// パイプラインステート生成
	CreatePipelineState(status.pipelineDesc_, status.inputLayout_);

	// プリミティブ形状設定
	SetPrimitiveTopology(status.primitive_);
}

void PipelineSet::SetDrawCommand()
{
	// パイプラインステートの設定コマンド
	pCmdList_->SetPipelineState(pipelineState_.Get());

	// ルートシグネチャの設定コマンド
	pCmdList_->SetGraphicsRootSignature(rootSignature_.Get());

	// プリミティブ形状の設定コマンド
	pCmdList_->IASetPrimitiveTopology(primitive_);
}
