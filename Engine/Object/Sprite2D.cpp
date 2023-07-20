#include "Sprite2D.h"
#include "MathVector.h"
#include <cassert>

#pragma region 名前空間

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Sprite2D;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Matrix4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eTransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eColorCB); // color
static const UINT TexConfigIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eTexConfigCB); // texConfig
static const UINT TexIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::eTexDT); // tex

#pragma endregion

#pragma region Static

vector<unique_ptr<Sprite2D>> Sprite2D::sSprites_{};
array<PipelineSet, Sprite2D::Pipeline::sShaderNum_> Sprite2D::Pipeline::sPipelineSets_{};
array<array<list<unique_ptr<Sprite2D::Pipeline::DrawSet>>,
	Sprite2D::Pipeline::sShaderNum_>, DrawLocationNum> Sprite2D::Pipeline::sDrawSets_;

#pragma endregion


#pragma region Sprite2D

Sprite2D* Sprite2D::Create(const Status& status, const TexStatus& texStatus)
{
	// スプライト生成
	unique_ptr<Sprite2D> newSprite = std::make_unique<Sprite2D>();


	// テクスチャのサイズを取得
	float rscSizeX = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Width);
	float rscSizeY = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Height);

	// ----- Status ----- //

	// 反転設定
	float flipX = status.isFlipX_ ? -1.0f : 1.0f;
	float flipY = status.isFlipY_ ? -1.0f : 1.0f;

	// サイズを設定 (画像に合わせるならそのまま)
	Vector2 size = status.isDiv_ ? Vector2(rscSizeX, rscSizeY) : status.size_;

	// 左右上下のポイント設定 (0.0~1,0)
	float left = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV座標を計算
	float texLeft = texLT.x_ / rscSizeX;
	float texRight = texRB.x_ / rscSizeX;
	float texTop = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;


	// インスタンス生成 (動的)
	newSprite->vt_.Initialize(
		{
			{ {  left,bottom,0.0f },{  texLeft,texBottom } }, // 左下
			{ {  left,top,   0.0f },{  texLeft,texTop } },    // 左上
			{ { right,bottom,0.0f },{ texRight,texBottom } }, // 右下
			{ { right,top,   0.0f },{ texRight,texTop } },    // 右上
		});

	// いろいろ設定
	newSprite->size_ = status.size_; // 大きさ
	newSprite->anchor_ = status.anchor_; // アンカーポイント
	newSprite->isFlipX_ = status.isFlipX_; // X反転
	newSprite->isFlipY_ = status.isFlipY_; // Y反転

	newSprite->pTex_ = texStatus.pTex_; // テクスチャインデックス
	newSprite->texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // テクスチャの左上
	newSprite->texSize_ = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // テクスチャの大きさ


	// ポインタを獲得
	Sprite2D* newSpritePtr = newSprite.get();

	// スプライトを保存
	sSprites_.push_back(std::move(newSprite));

	// スプライトポインタを返す
	return newSpritePtr;
}

void Sprite2D::AllClear()
{
	// スプライト2D全消去
	for (size_t i = 0; i < sSprites_.size(); i++)
	{
		sSprites_[i].reset(nullptr);
	}
	sSprites_.clear();
}

void Sprite2D::SetDrawCommand(Object* pObj, const DrawLocation& location, const ShaderType& shaderType)
{
	// 描画セット挿入
	Pipeline::StaticPushBackDrawSet(this, pObj, location, shaderType);
}

void Sprite2D::SetSize(const Vector2& size)
{
	if (size_ == size) { return; }
	SetAllStatus({ false, size, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetAnchorPoint(const Vector2& anchor)
{
	if (anchor_ == anchor) { return; }
	SetAllStatus({ false, size_, anchor, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetFrip(const bool isFlipX, const bool isFlipY)
{
	if (isFlipX_ == isFlipX && isFlipY_ == isFlipY) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX, isFlipY }, { pTex_, false, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetTextureLeftTop(const Vector2& leftTop, const bool adjust)
{
	if (texLeftTop_ == leftTop) { return; }

	float adjX = adjust && (texLeftTop_.x_ < leftTop.x_) ? (leftTop.x_ - texLeftTop_.x_) : 0.0f;
	float adjY = adjust && (texLeftTop_.y_ < leftTop.y_) ? (leftTop.y_ - texLeftTop_.y_) : 0.0f;

	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, leftTop, texSize_ - Vector2(adjX, adjY) });
}
void Sprite2D::SetTextureSize(const Vector2& texSize)
{
	if (texSize_ == texSize) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, texLeftTop_, texSize });
}
void Sprite2D::SetTextureRectangle(const Vector2& leftTop, const Vector2& texSize)
{
	if (texLeftTop_ == leftTop && texSize_ == texSize) { return; }
	SetAllStatus({ false, size_, anchor_, isFlipX_, isFlipY_ }, { pTex_, false, leftTop, texSize });
}
void Sprite2D::SetAllStatus(const Status& status, const TexStatus& texStatus)
{
	// 頂点データ
	std::vector<VData> v;

	// テクスチャのサイズを取得
	float rscSizeX = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Width);
	float rscSizeY = static_cast<float>(texStatus.pTex_->Buffer()->GetDesc().Height);

	// ----- Status ----- //

	// 反転設定
	float flipX = status.isFlipX_ ? -1.0f : 1.0f;
	float flipY = status.isFlipY_ ? -1.0f : 1.0f;

	// サイズを設定 (画像に合わせるならそのまま)
	Vector2 size = status.isDiv_ ? Vector2(rscSizeX, rscSizeY) : status.size_;

	// 左右上下のポイント設定 (0.0~1,0)
	float left = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV座標を計算
	float texLeft = texLT.x_ / rscSizeX;
	float texRight = texRB.x_ / rscSizeX;
	float texTop = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;


	// 頂点を再設定
	v.push_back({ {  left,bottom,0.0f },{  texLeft,texBottom } }); // 左下
	v.push_back({ {  left,top,   0.0f },{  texLeft,texTop } });	   // 左上
	v.push_back({ { right,bottom,0.0f },{ texRight,texBottom } }); // 右下
	v.push_back({ { right,top,   0.0f },{ texRight,texTop } });	   // 右上
	vt_.TransferMap(v);

	// いろいろ設定
	size_ = status.size_; // 大きさ
	anchor_ = status.anchor_; // アンカーポイント
	isFlipX_ = status.isFlipX_; // X反転
	isFlipY_ = status.isFlipY_; // Y反転

	pTex_ = texStatus.pTex_; // テクスチャインデックス
	texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // テクスチャの左上
	texSize_ = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // テクスチャの大きさ
}

void Sprite2D::SetIsVisible(const bool isVisible)
{
	isVisible_ = isVisible;
}

#pragma endregion


#pragma region Object

Sprite2D::Object* Sprite2D::Object::Create(
	const Status& status,
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
	instance->SetColor(pColor);
	instance->SetTexConfig(pTexConfig);

	// インスタンスを返す
	return instance;
}

void Sprite2D::Object::SetDrawCommand(
	const UINT transformRPIndex,
	const UINT colorRPIndex,
	const UINT texConfigRPIndex)
{
	// 行列
	cBuff_.map_->matWorld_ = m_ * Default::sProjection_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// 色
	pColor_->SetDrawCommand(colorRPIndex);

	// テクスチャ設定
	pTexConfig_->SetDrawCommand(texConfigRPIndex);
}

void Sprite2D::Object::SetColor(CBColor* pColor)
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

void Sprite2D::Object::SetTexConfig(CBTexConfig* pTexConfig)
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

Matrix4 Sprite2D::Object::Default::sProjection_ = Matrix4::Identity();
unique_ptr<YGame::CBColor> Sprite2D::Object::Default::sColor_ = nullptr;
unique_ptr<YGame::CBTexConfig> Sprite2D::Object::Default::sTexConfig_ = nullptr;

void Sprite2D::Object::Default::StaticInitialize()
{
	// プロジェクション行列を設定
	sProjection_ = YMath::MatOrthoGraphic();

	// 生成 + 初期化 (色)
	sColor_.reset(CBColor::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// 生成 + 初期化 (テクスチャ設定)
	sTexConfig_.reset(CBTexConfig::Create({ 1.0f,1.0f }, {}, false));
}

#pragma endregion


#pragma region Pipeline

void Sprite2D::Pipeline::ShaderSet::Load()
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	// Default
	{
		ID3DBlob* vs = nullptr;
		ID3DBlob* ps = nullptr;

		// 頂点シェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/Sprite2DVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
		// ピクセルシェーダの読み込みとコンパイル
		LoadShader(L"Resources/Shaders/Sprite2DPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

		defaultVSBlob_ = vs;
		defaultPSBlob_ = ps; 
	}
}

void Sprite2D::Pipeline::StaticInitialize()
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
		// UV座標	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
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
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

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
	D3D_PRIMITIVE_TOPOLOGY primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // 三角形ストリップ

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

void Sprite2D::Pipeline::StaticClearDrawSet(const DrawLocation& location)
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

void Sprite2D::Pipeline::StaticPushBackDrawSet(
	Sprite2D* pSprite2D, Sprite2D::Object* pObj, 
	const DrawLocation& location, const ShaderType& shaderType)
{
	// 描画セット生成
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// 初期化
	newDrawSet->pSprite2D_ = pSprite2D;
	newDrawSet->pObj_ = pObj;

	// インデックスに変換
	size_t locationIdx = static_cast<size_t>(location);

	// インデックスに変換
	size_t shaderIdx = static_cast<size_t>(shaderType);

	// 挿入
	sDrawSets_[locationIdx][shaderIdx].push_back(std::move(newDrawSet));
}

void Sprite2D::Pipeline::StaticDraw(const DrawLocation& location)
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

void Sprite2D::Pipeline::DrawSet::Draw()
{
	// 描画しないなら弾く
	if (pSprite2D_->isVisible_ == false) { return; }

	// 定数バッファをシェーダーに送る
	pObj_->SetDrawCommand(TraIndex, ColIndex, TexConfigIndex);

	// テクスチャ
	pSprite2D_->pTex_->SetDrawCommand(TexIndex);

	// 頂点バッファを送る + 描画コマンド
	pSprite2D_->vt_.Draw();
}

#pragma endregion