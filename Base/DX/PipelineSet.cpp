#include "PipelineSet.h"
#include "ShaderSet.h"
#include "YAssert.h"
#include <memory>

using DX::PipelineSet;

ID3D12Device* PipelineSet::pDevice_ = nullptr;
ID3D12GraphicsCommandList* PipelineSet::pCmdList_ = nullptr;

void PipelineSet::SpritePipelineSetDesc::Initialize(ID3DBlob* errorBlob_)
{
	// シェーダー読み込み
	DX::SpriteShaderSet shdrs;
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
	}

	// プリミティブ形状の設定
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // 三角形ストリップ
}

void PipelineSet::ModelPipelineSetDesc::Initialize(ID3DBlob* errorBlob_)
{
	// シェーダー読み込み
	DX::ModelShaderSet shdrs;
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
			"NORMAL",
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
		},
		{
			"TANGENT",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
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
		pplnDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング
	
		// デプスステンシルステートの設定
		pplnDesc_.DepthStencilState.DepthEnable = true; // 深度テスト
		pplnDesc_.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
		pplnDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
		pplnDesc_.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット
	}
	
	// プリミティブ形状の設定
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // 三角形リスト
}

void PipelineSet::StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList)
{
	assert(pDevice);
	assert(pCommandList);

	pDevice_ = pDevice;
	pCmdList_ = pCommandList;
}

void PipelineSet::Initialize(const Type& type, std::vector<D3D12_ROOT_PARAMETER>* rootParams)
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// ----- PipelineSetStatus ----- //

	std::unique_ptr<IPipelineSetDesc> state;

	if (type == Type::SpriteT) { state = std::make_unique<SpritePipelineSetDesc>(); }
	if (type == Type::ModelT) { state = std::make_unique<ModelPipelineSetDesc>(); }

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

	// 図形の形状設定
	state->pplnDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

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
