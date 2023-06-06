#include "Sprite3D.h"
#include "MathVector.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Sprite3D;
using YDX::PipelineSet;
using YMath::Vector3;
using YMath::Matrix4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(Sprite3D::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(Sprite3D::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT TexConfigIndex = static_cast<UINT>(Sprite3D::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT TexIndex = static_cast<UINT>(Sprite3D::Pipeline::RootParameterIndex::eTexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Sprite3D>> Sprite3D::sSprites_{};
array<PipelineSet, Sprite3D::Pipeline::sShaderNum_> Sprite3D::Pipeline::sPipelineSets_{};
array<array<list<unique_ptr<Sprite3D::Pipeline::DrawSet>>, 
	Sprite3D::Pipeline::sShaderNum_>, DrawLocationNum> Sprite3D::Pipeline::sDrawSets_;
YDX::Vertices<Sprite3D::VData> Sprite3D::vt_{};
bool Sprite3D::isInitVertices_ = false;

#pragma endregion


#pragma region Sprite3D

Sprite3D* Sprite3D::Create(Texture* pTex)
{
	// 初期化
	if (isInitVertices_ == false) 
	{
		vt_.Initialize({ {} }); 
		isInitVertices_ = true;
	}
	
	// スプライト生成
	unique_ptr<Sprite3D> newSprite = std::make_unique<Sprite3D>();

	// テクスチャ番号
	newSprite->pTex_ = pTex;

	// 描画する
	newSprite->isVisible_ = true;


	// ポインタを獲得
	Sprite3D* newSpritePtr = newSprite.get();

	// スプライトを保存
	sSprites_.push_back(std::move(newSprite));

	// スプライトポインタを返す
	return newSpritePtr;
}

void Sprite3D::AllClear()
{
	// スプライト3D全消去
	for (size_t i = 0; i < sSprites_.size(); i++)
	{
		sSprites_[i].reset(nullptr);
	}
	sSprites_.clear();
}

void Sprite3D::SetDrawCommand(Sprite3D::Object* pObj, const DrawLocation& location, const ShaderType& shaderType)
{
	// 描画セット挿入
	Pipeline::StaticPushBackDrawSet(this, pObj, location, shaderType);
}

void Sprite3D::SetIsVisible(const bool isVisible)
{
	isVisible_ = isVisible;
}

#pragma endregion


#pragma region Object

Sprite3D::Object* Sprite3D::Object::Create(
	const Status& status, 
	bool isXAxisBillboard, bool isYAxisBillboard,
	ViewProjection* pVP, 
	CBColor* pColor,
	CBTexConfig* pTexConfig,
	const bool isMutable)
{
	// インスタンス生成 (動的)
	Object* instance = new Object();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);
	instance->SetTexConfig(pTexConfig);

	// インスタンスを返す
	return instance;
}

void Sprite3D::Object::SetDrawCommand(
	const UINT transformRPIndex,
	const UINT colorRPIndex,
	const UINT texConfigRPIndex)
{
	// シェーダーに定数バッファ(行列)を送る
	cBuff_.map_->matWorld_ = m_ * pVP_->view_ * pVP_->pro_;
	cBuff_.map_->matBill_ = 
		YMath::BillboardMatrix(isXAxisBillboard_, isYAxisBillboard_, pVP_->eye_, pVP_->target_, pVP_->eye_);
	cBuff_.SetDrawCommand(transformRPIndex);

	// 色
	pColor_->SetDrawCommand(colorRPIndex);

	// テクスチャ設定
	pTexConfig_->SetDrawCommand(texConfigRPIndex);
}

void Sprite3D::Object::SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard)
{
	isXAxisBillboard_ = isXAxisBillboard;
	isYAxisBillboard_ = isYAxisBillboard;
}

void Sprite3D::Object::SetViewProjection(ViewProjection* pVP)
{
	// nullなら
	if (pVP == nullptr)
	{
		// デフォルト代入
		pVP_ = Default::sVP_.get();
		return;
	}

	// 代入
	pVP_ = pVP;
}

void Sprite3D::Object::SetColor(CBColor* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = Default::sColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}

void Sprite3D::Object::SetTexConfig(CBTexConfig* pTexConfig)
{
	// nullなら
	if (pTexConfig == nullptr)
	{
		// デフォルト代入
		pTexConfig_ = Default::sTexConfig_.get();
		return;
	}

	// 代入
	pTexConfig_ = pTexConfig;
}

unique_ptr<YGame::ViewProjection> Sprite3D::Object::Default::sVP_ = nullptr;
unique_ptr<YGame::CBColor> Sprite3D::Object::Default::sColor_ = nullptr;
unique_ptr<YGame::CBTexConfig> Sprite3D::Object::Default::sTexConfig_ = nullptr;

void Sprite3D::Object::Default::StaticInitialize()
{
	// 生成
	sVP_.reset(new YGame::ViewProjection());
	sVP_->Initialize();

	// 生成 + 初期化 (色)
	sColor_.reset(CBColor::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// 生成 + 初期化 (テクスチャ設定)
	sTexConfig_.reset(CBTexConfig::Create({ 1.0f,1.0f}, {}, false));
}

#pragma endregion


#pragma region Pipeline

void Sprite3D::Pipeline::ShaderSet::Load()
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// Default
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* gs = nullptr;
		ID3DBlob* ps = nullptr;

		// 頂点シェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/Sprite3DVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// ジオメトリシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/Sprite3DGS.hlsl", "main", "gs_5_0", gs, errorBlob.Get());
		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/Sprite3DPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		defaultVSBlob_ = vs;
		defaultGSBlob_ = gs;
		defaultPSBlob_ = ps; 
	}
}

void Sprite3D::Pipeline::StaticInitialize()
{

#pragma region シェーダー読み込み

	// シェーダー
	ShaderSet shdrs;

	// 読み込み
	shdrs.Load();

#pragma endregion


#pragma region 頂点レイアウトの設定

	// 頂点レイアウト
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout =
	{
		// 頂点座標	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

#pragma endregion


#pragma region テクスチャサンプラーの設定

	// テクスチャサンプラー配列
	std::vector<D3D12_STATIC_SAMPLER_DESC> samplerDescs;

	// テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横折り返し   (タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 縦折り返し   (タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 奥行折り返し (タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミニマップ最大値
	samplerDesc.MinLOD = 0.0f;              // ミニマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーからのみ使用可能

	// テクスチャサンプラー配列に挿入
	samplerDescs.push_back(samplerDesc);

#pragma endregion


#pragma region ルートパラメータの設定

	// ルートパラメータ
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	// 定数バッファの数
	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::eTexDT);

	// 定数バッファの数だけ
	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// 定数バッファ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
		rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		// 配列に挿入
		rootParams.push_back(rootParam);
	}

	// デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &descriptorRange;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	// 配列に挿入
	rootParams.push_back(rootParam);

#pragma endregion


#pragma region パイプライン設定

	// パイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// シェーダーの設定
	pipelineDesc.VS.pShaderBytecode	 = shdrs.defaultVSBlob_.Get()->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength	 = shdrs.defaultVSBlob_.Get()->GetBufferSize();
	pipelineDesc.GS.pShaderBytecode	 = shdrs.defaultGSBlob_.Get()->GetBufferPointer();
	pipelineDesc.GS.BytecodeLength	 = shdrs.defaultGSBlob_.Get()->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode	 = shdrs.defaultPSBlob_.Get()->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength	 = shdrs.defaultPSBlob_.Get()->GetBufferSize();

	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

	// デプスステンシルステートの設定
	pipelineDesc.DepthStencilState.DepthEnable = false; // 深度テストしない
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き

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

	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	// 画像の透過適用
	//pipelineDesc.BlendState.AlphaToCoverageEnable = true;

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout.data(); // 頂点レイアウトの先頭アドレス
	pipelineDesc.InputLayout.NumElements = (UINT)inputLayout.size(); // 頂点レイアウト数

	// その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

#pragma endregion


#pragma region プリミティブ形状の設定

	// プリミティブ形状
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; // ポイントリスト

#pragma endregion


	//// パイプラインの数だけ
	//for (size_t i = 0; i < sPipelineSets_.size(); i++)
	//{
	//	// パイプライン初期化
	//	sPipelineSets_[i].Initialize(samplerDescs, rootParams, pipelineDesc, primitive);
	//}

	sPipelineSets_[0].Initialize(samplerDescs, rootParams, pipelineDesc, primitive);

	// 描画場所の数だけ
	for (size_t i = 0; i < sDrawSets_.size(); i++)
	{
		// 変換
		DrawLocation location = static_cast<DrawLocation>(i);

		// クリア
		StaticClearDrawSet(location);
	}
}

void Sprite3D::Pipeline::StaticClearDrawSet(const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// あるなら
		if (sDrawSets_[index][i].empty() == false)
		{
			// クリア
			sDrawSets_[index][i].clear();
		}
	}
}

void Sprite3D::Pipeline::StaticPushBackDrawSet(
	Sprite3D* pSprite3D, Sprite3D::Object* pObj, 
	const DrawLocation& location, const ShaderType& shaderType)
{
	// 描画セット生成
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// 初期化
	newDrawSet->pSprite3D_ = pSprite3D;
	newDrawSet->pObj_ = pObj;

	// インデックスに変換
	size_t locationIdx = static_cast<size_t>(location);

	// インデックスに変換
	size_t shaderIdx = static_cast<size_t>(shaderType);

	// 挿入
	sDrawSets_[locationIdx][shaderIdx].push_back(std::move(newDrawSet));
}

void Sprite3D::Pipeline::StaticDraw(const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// パイプラインをセット
		sPipelineSets_[i].SetDrawCommand();

		// モデル描画
		for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_[index][i])
		{
			// 描画
			drawSet->Draw();
		}
	}
}

void Sprite3D::Pipeline::DrawSet::Draw()
{
	// 描画しないなら弾く
	if (pSprite3D_->isVisible_ == false) { return; }

	// 定数バッファをシェーダーに送る
	pObj_->SetDrawCommand(TraIndex, ColIndex, TexConfigIndex);

	// テクスチャ
	pSprite3D_->pTex_->SetDrawCommand(TexIndex);

	// 頂点バッファを送る + 描画コマンド
	pSprite3D_->vt_.Draw();
}

#pragma endregion