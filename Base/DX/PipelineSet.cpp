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

void PipelineSet::Initialize(IStatus* state, std::vector<D3D12_ROOT_PARAMETER>* rootParams)
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// ----- PipelineSetStatus ----- //

	state->Initialize(errorBlob.Get());

	// ----- RootSignature ----- //

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rsDesc{};
	rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rsDesc.pParameters = rootParams->data(); // ルートパラメータの先頭アドレス
	rsDesc.NumParameters = (UINT)rootParams->size();// ルートパラメータ数
	rsDesc.pStaticSamplers = state->sampleDesc_.data(); // テクスチャサンプラーの先頭アドレス
	rsDesc.NumStaticSamplers = (UINT)state->sampleDesc_.size(); // テクスチャサンプラー数

	// ルートシグネチャのシリアライズ
	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr; // ルートシグネチャオブジェクト
	Result(D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob));

	// ルートシグネチャの生成
	Result(pDevice_->CreateRootSignature(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature_)));

	// ----- PipelineState ----- //

	// サンプルマスクの設定
	state->pplnDesc_.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	state->pplnDesc_.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	state->pplnDesc_.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	// ブレンドステート
	D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = state->pplnDesc_.BlendState.RenderTarget[0];
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
	state->pplnDesc_.InputLayout.pInputElementDescs = state->inputLayout_.data(); // 頂点レイアウトの先頭アドレス
	state->pplnDesc_.InputLayout.NumElements = (UINT)state->inputLayout_.size(); // 頂点レイアウト数

	// その他の設定
	state->pplnDesc_.NumRenderTargets = 1; // 描画対象は1つ
	state->pplnDesc_.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	state->pplnDesc_.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// パイプラインにルートシグネチャをセット
	state->pplnDesc_.pRootSignature = rootSignature_.Get();

	// パイプランステートの生成
	Result(pDevice_->CreateGraphicsPipelineState(&state->pplnDesc_, IID_PPV_ARGS(&pplnState_)));

	primitive_ = state->primitive_;
}

void PipelineSet::SetDrawCommand()
{
	// パイプラインステートの設定コマンド
	pCmdList_->SetPipelineState(pplnState_.Get());

	// ルートシグネチャの設定コマンド
	pCmdList_->SetGraphicsRootSignature(rootSignature_.Get());

	// プリミティブ形状の設定コマンド
	pCmdList_->IASetPrimitiveTopology(primitive_);
}
