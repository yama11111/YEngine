#include "Sprite2D.h"
#include <cassert>

#pragma region 名前空間

using std::unique_ptr;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Matrix4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::TransformCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite2D::Pipeline::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Sprite2D>> Sprite2D::sprites_{};
YDX::PipelineSet Sprite2D::Pipeline::sPipelineSet_{};

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
	float left   = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right  = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top    = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV座標を計算
	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
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
	newSprite->size_    = status.size_; // 大きさ
	newSprite->anchor_  = status.anchor_; // アンカーポイント
	newSprite->isFlipX_ = status.isFlipX_; // X反転
	newSprite->isFlipY_ = status.isFlipY_; // Y反転

	newSprite->pTex_	   = texStatus.pTex_; // テクスチャインデックス
	newSprite->texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // テクスチャの左上
	newSprite->texSize_	   = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // テクスチャの大きさ


	// ポインタを獲得
	Sprite2D* newSpritePtr = newSprite.get();

	// スプライトを保存
	sprites_.push_back(std::move(newSprite));

	// スプライトポインタを返す
	return newSpritePtr;
}

void Sprite2D::AllClear()
{
	// スプライト2D全消去
	for (size_t i = 0; i < sprites_.size(); i++)
	{
		sprites_[i].reset(nullptr);
	}
	sprites_.clear();
}

void Sprite2D::Draw(Sprite2DObject* pObj)
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
	float left	 = (0.0f - status.anchor_.x_) * size.x_ * flipX;
	float right	 = (1.0f - status.anchor_.x_) * size.x_ * flipX;
	float top	 = (0.0f - status.anchor_.y_) * size.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * size.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_;
	Vector2 texRB = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : (texStatus.leftTop_ + texStatus.size_);

	// UV座標を計算
	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;


	// 頂点を再設定
	v.push_back({ {  left,bottom,0.0f },{  texLeft,texBottom } }); // 左下
	v.push_back({ {  left,top,   0.0f },{  texLeft,texTop } });	   // 左上
	v.push_back({ { right,bottom,0.0f },{ texRight,texBottom } }); // 右下
	v.push_back({ { right,top,   0.0f },{ texRight,texTop } });	   // 右上
	vt_.TransferMap(v);

	// いろいろ設定
	size_	 = status.size_; // 大きさ
	anchor_	 = status.anchor_; // アンカーポイント
	isFlipX_ = status.isFlipX_; // X反転
	isFlipY_ = status.isFlipY_; // Y反転

	pTex_	    = texStatus.pTex_; // テクスチャインデックス
	texLeftTop_ = texStatus.isDiv_ ? Vector2(0.0f, 0.0f) : texStatus.leftTop_; // テクスチャの左上
	texSize_    = texStatus.isDiv_ ? Vector2(rscSizeX, rscSizeY) : texStatus.size_; // テクスチャの大きさ
}

#pragma endregion

#pragma region Pipeline

void Sprite2D::Pipeline::ShaderSet::Load()
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite2DVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite2DPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

	vsBlob_ = vs;
	psBlob_ = ps;
}

void Sprite2D::Pipeline::StaticInitialize()
{
	// パイプライン初期化用設定
	PipelineSet::InitStatus initStatus;


#pragma region シェーダー読み込み

	ShaderSet shdrs;
	shdrs.Load();

#pragma endregion


#pragma region 頂点レイアウトの設定

	initStatus.inputLayout_ =
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

	initStatus.samplerDescs_.push_back(samplerDesc);

#pragma endregion


#pragma region ルートパラメータの設定

	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// 定数バッファ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
		rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		initStatus.rootParams_.push_back(rootParam);
	}

	// デスクリプタレンジの設定
	initStatus.descriptorRange_.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	initStatus.descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	initStatus.descriptorRange_.BaseShaderRegister = 0; // テクスチャレジスタ0番
	initStatus.descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &initStatus.descriptorRange_;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	initStatus.rootParams_.push_back(rootParam);

#pragma endregion


#pragma region パイプライン設定

	// シェーダーの設定
	initStatus.pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.VS.BytecodeLength  = shdrs.vsBlob_.Get()->GetBufferSize();
	initStatus.pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.PS.BytecodeLength  = shdrs.psBlob_.Get()->GetBufferSize();

	// ラスタライザの設定
	initStatus.pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

	// デプスステンシルステートの設定
	initStatus.pipelineDesc_.DepthStencilState.DepthEnable = false; // 深度テストしない
	initStatus.pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き

	// 図形の形状設定
	initStatus.pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

#pragma endregion


#pragma region プリミティブ形状の設定

	initStatus.primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; // 三角形ストリップ

#pragma endregion


	// パイプライン初期化
	sPipelineSet_.Initialize(initStatus);

}

void Sprite2D::Pipeline::StaticSetDrawCommond()
{
	// パイプラインをセット
	sPipelineSet_.SetDrawCommand();
}

#pragma endregion