#include "Sprite2D.h"
#include <cassert>

#pragma region 名前空間

using YGame::Sprite2DObject;
using YGame::Sprite2DCommon;
using YGame::Sprite2D;
using YMath::Vector2;
using YMath::Matrix4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::TransformCB); // obj
static const UINT ColIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::ColorCB); // color
static const UINT TexIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::TexDT); // tex

#pragma endregion


#pragma region Sprite2DCBSet

Sprite2DObject* Sprite2DObject::Create(const Status& status)
{
	// インスタンスを返す
	return Create(status, nullptr);
}

Sprite2DObject* Sprite2DObject::Create(const Status& status, Color* pColor)
{
	// インスタンス生成 (動的)
	Sprite2DObject* instance = new Sprite2DObject();

	// 定数バッファ生成
	instance->cBuff_.Create();

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetColor(pColor);

	// インスタンスを返す
	return instance;
}

void Sprite2DObject::SetColor(Color* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = sDefColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}

void Sprite2DObject::SetDrawCommand()
{
	// 行列
	cBuff_.map_->matWorld_ = m_ * sProjection_;
	cBuff_.SetDrawCommand(TraIndex);

	// 色
	pColor_->SetDrawCommand(ColIndex);
}

#pragma endregion


#pragma region Sprite2DCBSet

Sprite2D* Sprite2D::Create(const Status& status, const TexStatus& texStatus, const bool div)
{
	// インスタンス
	Sprite2D* instance = new Sprite2D();
	
	// ----- Status ----- //

	// 反転設定
	float flipX = status.isFlipX_ ? -1.0f : 1.0f;
	float flipY = status.isFlipY_ ? -1.0f : 1.0f;

	// 左右上下のポイント設定 (0.0~1,0)
	float left   = (0.0f - status.anchor_.x_) * status.size_.x_ * flipX;
	float right  = (1.0f - status.anchor_.x_) * status.size_.x_ * flipX;
	float top    = (0.0f - status.anchor_.y_) * status.size_.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * status.size_.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャのサイズを取得
	float rscSizeX = static_cast<float>(spTexManager_->TextureBuffer(texStatus.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(spTexManager_->TextureBuffer(texStatus.index_)->GetDesc().Height);

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = div ? texStatus.leftTop_ : Vector2(0.0f, 0.0f);
	Vector2 texRB = div ? (texStatus.leftTop_ + texStatus.size_) : Vector2(rscSizeX, rscSizeY);

	// UV座標を計算
	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;
	

	// インスタンス生成 (動的)
	instance->vt_.Initialize(
		{
			{ {  left,bottom,0.0f },{  texLeft,texBottom } }, // 左下
			{ {  left,top,   0.0f },{  texLeft,texTop } },    // 左上
			{ { right,bottom,0.0f },{ texRight,texBottom } }, // 右下
			{ { right,top,   0.0f },{ texRight,texTop } },    // 右上
		});

	// いろいろ設定
	instance->size_    = status.size_; // 大きさ
	instance->anchor_  = status.anchor_; // アンカーポイント
	instance->isFlipX_ = status.isFlipX_; // X反転
	instance->isFlipY_ = status.isFlipY_; // Y反転

	instance->tex_		  = texStatus.index_; // テクスチャインデックス
	instance->texLeftTop_ = div ? texStatus.leftTop_ : Vector2(0.0f, 0.0f); // テクスチャの左上
	instance->texSize_    = div ? texStatus.size_ : Vector2(rscSizeX, rscSizeY); // テクスチャの大きさ

	// インスタンスを返す
	return instance;
}

void Sprite2D::Draw(Sprite2DObject* pObj)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// 定数バッファをシェーダーに送る
	pObj->SetDrawCommand();

	// テクスチャ
	spTexManager_->SetDrawCommand(TexIndex, tex_);

	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();
}

void Sprite2D::SetSize(const Vector2& size)
{
	if (size_ == size) { return; }
	SetAllStatus({ size, anchor_, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetAnchorPoint(const Vector2& anchor)
{
	if (anchor_ == anchor) { return; }
	SetAllStatus({ size_, anchor, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetFrip(const bool isFlipX, const bool isFlipY)
{
	if (isFlipX_ == isFlipX && isFlipY_ == isFlipY) { return; }
	SetAllStatus({ size_, anchor_, isFlipX, isFlipY }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite2D::SetTextureLeftTop(const Vector2& leftTop, const bool adjust)
{
	if (texLeftTop_ == leftTop) { return; }

	float adjX = adjust && (texLeftTop_.x_ < leftTop.x_) ? (leftTop.x_ - texLeftTop_.x_) : 0.0f;
	float adjY = adjust && (texLeftTop_.y_ < leftTop.y_) ? (leftTop.y_ - texLeftTop_.y_) : 0.0f;

	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, leftTop, texSize_ - Vector2(adjX, adjY) }, true);
}
void Sprite2D::SetTextureSize(const Vector2& texSize)
{
	if (texSize_ == texSize) { return; }
	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texSize }, true);
}
void Sprite2D::SetTextureRectangle(const Vector2& leftTop, const Vector2& texSize)
{
	if (texLeftTop_ == leftTop && texSize_ == texSize) { return; }
	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, leftTop, texSize }, true);
}
void Sprite2D::SetAllStatus(const Status& status, const TexStatus& texStatus, const bool div)
{
	std::vector<VData> v;

	// ----- Status ----- //
	
	// 反転設定
	float flipX = status.isFlipX_ ? -1.0f : 1.0f;
	float flipY = status.isFlipY_ ? -1.0f : 1.0f;

	// 左右上下のポイント設定 (0.0~1,0)
	float left = (0.0f - status.anchor_.x_) * status.size_.x_ * flipX;
	float right = (1.0f - status.anchor_.x_) * status.size_.x_ * flipX;
	float top = (0.0f - status.anchor_.y_) * status.size_.y_ * flipY;
	float bottom = (1.0f - status.anchor_.y_) * status.size_.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャのサイズを取得
	float rscSizeX = static_cast<float>(spTexManager_->TextureBuffer(texStatus.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(spTexManager_->TextureBuffer(texStatus.index_)->GetDesc().Height);

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = div ? texStatus.leftTop_ : Vector2(0.0f, 0.0f);
	Vector2 texRB = div ? (texStatus.leftTop_ + texStatus.size_) : Vector2(rscSizeX, rscSizeY);

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
	size_ = status.size_; // 大きさ
	anchor_ = status.anchor_; // アンカーポイント
	isFlipX_ = status.isFlipX_; // X反転
	isFlipY_ = status.isFlipY_; // Y反転

	tex_ = texStatus.index_; // テクスチャインデックス
	texLeftTop_ = div ? texStatus.leftTop_ : Vector2(0.0f, 0.0f); // テクスチャの左上
	texSize_ = div ? texStatus.size_ : Vector2(rscSizeX, rscSizeY); // テクスチャの大きさ
}

#pragma endregion