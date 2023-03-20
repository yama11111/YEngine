#include "Sprite2D.h"

#pragma region 名前空間

using YGame::Sprite2DCommon;
using YGame::Sprite2D;
using YGame::ObjectSprite2D;
using YMath::Vector2;
using YMath::Matrix4;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT ObjIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::ObjCB); // obj
static const UINT ColIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::ColorCB); // color
static const UINT TexIndex	 = static_cast<UINT>(Sprite2DCommon::RootParameterIndex::TexDT); // tex

#pragma endregion

ObjectSprite2D* ObjectSprite2D::Create(const Status& state)
{
	// インスタンス生成 (動的)
	ObjectSprite2D* instance = new ObjectSprite2D();
	
	// 定数バッファ生成
	instance->cBuff_.Create();
	// 初期化
	instance->Initialize(state);

	// インスタンスを返す
	return instance;
}

void Sprite2D::Draw(ObjectSprite2D* pObj, Color* pColor, const UINT tex)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// ----- シェーダーに定数バッファを送る ----- //
	
	// 行列
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * projection_;
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// 色
	pColor->SetDrawCommand(ColIndex);

	// テクスチャ
	pTexManager_->SetDrawCommand(TexIndex, tex);
	
	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();
}
void Sprite2D::Draw(ObjectSprite2D* pObj, const UINT tex)
{
	// デフォルトの色を渡して描画
	Draw(pObj, defColor_.get(), tex);
}
void Sprite2D::Draw(ObjectSprite2D* pObj, Color* pColor)
{
	// 描画しないなら弾く
	if (isInvisible_) { return; }

	// ----- シェーダーに定数バッファを送る ----- //

	// 行列
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * projection_;
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// 色
	pColor->SetDrawCommand(ColIndex);

	// テクスチャ
	pTexManager_->SetDrawCommand(TexIndex, tex_);
	
	// 頂点バッファを送る + 描画コマンド
	vt_.Draw();
}
void Sprite2D::Draw(ObjectSprite2D* pObj)
{
	// デフォルトの色を渡して描画
	Draw(pObj, defColor_.get());
}

Sprite2D* Sprite2D::Create(const Status& state, const TexStatus& texState, const bool div)
{
	// インスタンス
	Sprite2D* instance = new Sprite2D();
	
	// ----- Status ----- //

	// 反転設定
	float flipX = state.isFlipX_ ? -1.0f : 1.0f;
	float flipY = state.isFlipY_ ? -1.0f : 1.0f;

	// 左右上下のポイント設定 (0.0~1,0)
	float left   = (0.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float right  = (1.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float top    = (0.0f - state.anchor_.y_) * state.size_.y_ * flipY;
	float bottom = (1.0f - state.anchor_.y_) * state.size_.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャのサイズを取得
	float rscSizeX = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Height);

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = div ? texState.leftTop_ : Vector2(0.0f, 0.0f);
	Vector2 texRB = div ? (texState.leftTop_ + texState.size_) : Vector2(rscSizeX, rscSizeY);

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
	instance->size_    = state.size_; // 大きさ
	instance->anchor_  = state.anchor_; // アンカーポイント
	instance->isFlipX_ = state.isFlipX_; // X反転
	instance->isFlipY_ = state.isFlipY_; // Y反転

	instance->tex_		  = texState.index_; // テクスチャインデックス
	instance->texLeftTop_ = div ? texState.leftTop_ : Vector2(0.0f, 0.0f); // テクスチャの左上
	instance->texSize_    = div ? texState.size_ : Vector2(rscSizeX, rscSizeY); // テクスチャの大きさ

	instance->defColor_.reset(Color::Create()); // 色 (そのまま)

	// インスタンスを返す
	return instance;
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
void Sprite2D::SetAllStatus(const Status& state, const TexStatus& texState, const bool div)
{
	std::vector<VData> v;

	// ----- Status ----- //
	
	// 反転設定
	float flipX = state.isFlipX_ ? -1.0f : 1.0f;
	float flipY = state.isFlipY_ ? -1.0f : 1.0f;

	// 左右上下のポイント設定 (0.0~1,0)
	float left = (0.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float right = (1.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float top = (0.0f - state.anchor_.y_) * state.size_.y_ * flipY;
	float bottom = (1.0f - state.anchor_.y_) * state.size_.y_ * flipY;

	// ----- TexStatus ----- //

	// テクスチャのサイズを取得
	float rscSizeX = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Height);

	// テクスチャの左上と右下を設定 (画像に合わせるならそのまま)
	Vector2 texLT = div ? texState.leftTop_ : Vector2(0.0f, 0.0f);
	Vector2 texRB = div ? (texState.leftTop_ + texState.size_) : Vector2(rscSizeX, rscSizeY);

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
	size_ = state.size_; // 大きさ
	anchor_ = state.anchor_; // アンカーポイント
	isFlipX_ = state.isFlipX_; // X反転
	isFlipY_ = state.isFlipY_; // Y反転

	tex_ = texState.index_; // テクスチャインデックス
	texLeftTop_ = div ? texState.leftTop_ : Vector2(0.0f, 0.0f); // テクスチャの左上
	texSize_ = div ? texState.size_ : Vector2(rscSizeX, rscSizeY); // テクスチャの大きさ
}
