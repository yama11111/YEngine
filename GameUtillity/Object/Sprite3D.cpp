#include "Sprite3D.h"
#include <cassert>

#pragma region 名前空間

using std::unique_ptr;
using YGame::Sprite3DObject;
using YGame::Sprite3D;
using YDX::PipelineSet;
using YMath::Vector3;
using YMath::Matrix4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(Sprite3D::Common::RootParameterIndex::TransformCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite3D::Common::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite3D::Common::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Sprite3D>> Sprite3D::sprites_{};
Sprite3D::Common Sprite3D::common_{};
YDX::PipelineSet Sprite3D::Common::sPipelineSet_{};

#pragma endregion

#pragma region Sprite3D

Sprite3D* Sprite3D::Create(Texture* pTex)
{
	// スプライト生成
	unique_ptr<Sprite3D> newSprite = std::make_unique<Sprite3D>();

	
	// 初期化
	newSprite->vt_.Initialize({ {} });

	// テクスチャ番号
	newSprite->pTex_ = pTex;

	// 描画する
	newSprite->isInvisible_  = false;
	

	// ポインタを獲得
	Sprite3D* newSpritePtr = newSprite.get();

	// スプライトを保存
	sprites_.push_back(std::move(newSprite));

	// スプライトポインタを返す
	return newSpritePtr;
}

void Sprite3D::AllClear()
{
	// スプライト3D全消去
	for (size_t i = 0; i < sprites_.size(); i++)
	{
		sprites_[i].reset(nullptr);
	}
	sprites_.clear();
}

void Sprite3D::Draw(Sprite3DObject* pObj)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// 定数バッファをシェーダーに送る
	pObj->SetDrawCommand(TraIndex, ColIndex);

	// テクスチャ
	pTex_->SetDrawCommand(TexIndex);

	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();
}

#pragma endregion

#pragma region Common

void Sprite3D::Common::StaticInitialize()
{
	// パイプライン初期化
	std::unique_ptr<PipelineSet::IStatus> pplnState = std::make_unique<PipelineSetStatus>();
	sPipelineSet_.Initialize(pplnState.get());
}


void Sprite3D::Common::ShaderSet::Load(ID3DBlob* errorBlob)
{
	ID3DBlob* vs = nullptr;
	ID3DBlob* gs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite3DVS.hlsl", "main", "vs_5_0", vs, errorBlob);
	// ジオメトリシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite3DGS.hlsl", "main", "gs_5_0", gs, errorBlob);
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite3DPS.hlsl", "main", "ps_5_0", ps, errorBlob);

	vsBlob_ = vs;
	gsBlob_ = gs;
	psBlob_ = ps;
}

void Sprite3D::Common::PipelineSetStatus::Initialize(ID3DBlob* errorBlob_)
{
	// シェーダー読み込み
	ShaderSet shdrs;
	shdrs.Load(errorBlob_);

	// 頂点レイアウトの設定
	inputLayout_ =
	{
		// 頂点座標	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
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

	// ルートパラメータの設定
	{
		size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

		for (size_t i = 0; i < rpIdxCBNum; i++)
		{
			// 定数バッファ
			D3D12_ROOT_PARAMETER rootParam{};
			rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
			rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
			rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
			rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

			rootParams_.push_back(rootParam);
		}

		// デスクリプタレンジの設定
		descriptorRange_.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
		descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRange_.BaseShaderRegister = 0; // テクスチャレジスタ0番
		descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// テクスチャレジスタ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange_;
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		rootParams_.push_back(rootParam);
	}

	// パイプライン設定
	{
		// シェーダーの設定
		pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
		pipelineDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
		pipelineDesc_.GS.pShaderBytecode = shdrs.gsBlob_.Get()->GetBufferPointer();
		pipelineDesc_.GS.BytecodeLength = shdrs.gsBlob_.Get()->GetBufferSize();
		pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
		pipelineDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

		// ラスタライザの設定
		pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

		// デプスステンシルステートの設定
		pipelineDesc_.DepthStencilState.DepthEnable = false; // 深度テストしない
		pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き

		// 図形の形状設定
		pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

		// 画像の透過適用
		//pipelineDesc_.BlendState.AlphaToCoverageEnable = true;
	}

	// プリミティブ形状の設定
	primitive_ = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; // ポイントリスト
}

void Sprite3D::Common::StaticSetPipeline()
{
	// パイプラインをセット
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion