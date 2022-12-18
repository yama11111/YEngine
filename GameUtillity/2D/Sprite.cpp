#include "Sprite.h"
#include "CalcTransform.h"
#include <cassert>

using Game::Sprite;
using YMath::Vec2;
using YMath::Mat4;

Mat4 Sprite::projection_ = Mat4::Identity();
YDX::PipelineSet Sprite::pplnSet_;
Game::TextureManager* Sprite::pTexManager_ = nullptr;

void Sprite::StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams)
{
	assert(pTexManager);
	pTexManager_ = pTexManager;
	projection_ = YMath::MatOrthoGraphic();
	pplnSet_.Initialize(YDX::PipelineSet::Type::SpriteT, rootParams);
}

void Sprite::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}

Sprite* Sprite::Create(const Status& state, const TexStatus& texState, const bool div)
{
	// インスタンス
	Sprite* instance = new Sprite();
	
	// ----- Status ----- //

	float flipX = state.isFlipX_ ? -1.0f : 1.0f;
	float flipY = state.isFlipY_ ? -1.0f : 1.0f;

	float left   = (0.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float right  = (1.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float top    = (0.0f - state.anchor_.y_) * state.size_.y_ * flipY;
	float bottom = (1.0f - state.anchor_.y_) * state.size_.y_ * flipY;

	// ----- TexStatus ----- //

	float rscSizeX = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Height);

	Vec2 texLT = div ? texState.leftTop_ : Vec2(0.0f, 0.0f);
	Vec2 texRB = div ? (texState.leftTop_ + texState.size_) : Vec2(rscSizeX, rscSizeY);

	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;

	instance->vt_.Initialize(
		{
			{ {  left,bottom,0.0f },{  texLeft,texBottom } }, // 左下
			{ {  left,top,   0.0f },{  texLeft,texTop } },    // 左上
			{ { right,bottom,0.0f },{ texRight,texBottom } }, // 右下
			{ { right,top,   0.0f },{ texRight,texTop } },    // 右上
		});

	instance->size_    = state.size_;
	instance->anchor_  = state.anchor_;
	instance->isFlipX_ = state.isFlipX_;
	instance->isFlipY_ = state.isFlipY_;

	instance->tex_		  = texState.index_;
	instance->texLeftTop_ = div ? texState.leftTop_ : Vec2(0.0f, 0.0f);
	instance->texSize_    = div ? texState.size_ : Vec2(rscSizeX, rscSizeY);

	return instance;
}

void Sprite::SetSize(const Vec2& size)
{
	if (size_ == size) { return; }
	SetAllStatus({ size, anchor_, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite::SetAnchorPoint(const Vec2& anchor)
{
	if (anchor_ == anchor) { return; }
	SetAllStatus({ size_, anchor, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite::SetFrip(const bool isFlipX, const bool isFlipY)
{
	if (isFlipX_ == isFlipX && isFlipY_ == isFlipY) { return; }
	SetAllStatus({ size_, anchor_, isFlipX, isFlipY }, { tex_, texLeftTop_, texLeftTop_ });
}
void Sprite::SetTextureLeftTop(const Vec2& leftTop, const bool adjust)
{
	if (texLeftTop_ == leftTop) { return; }

	float adjX = adjust && (texLeftTop_.x_ < leftTop.x_) ? (leftTop.x_ - texLeftTop_.x_) : 0.0f;
	float adjY = adjust && (texLeftTop_.y_ < leftTop.y_) ? (leftTop.y_ - texLeftTop_.y_) : 0.0f;

	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, leftTop, texSize_ - Vec2(adjX, adjY) }, true);
}
void Sprite::SetTextureSize(const Vec2& texSize)
{
	if (texSize_ == texSize) { return; }
	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, texLeftTop_, texSize }, true);
}
void Sprite::SetTextureRectangle(const Vec2& leftTop, const Vec2& texSize)
{
	if (texLeftTop_ == leftTop && texSize_ == texSize) { return; }
	SetAllStatus({ size_, anchor_, isFlipX_, isFlipY_ }, { tex_, leftTop, texSize }, true);
}
void Sprite::SetAllStatus(const Status& state, const TexStatus& texState, const bool div)
{
	std::vector<YDX::SpriteVData> v;

	// ----- Status ----- //

	float flipX = state.isFlipX_ ? -1.0f : 1.0f;
	float flipY = state.isFlipY_ ? -1.0f : 1.0f;

	float left   = (0.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float right  = (1.0f - state.anchor_.x_) * state.size_.x_ * flipX;
	float top    = (0.0f - state.anchor_.y_) * state.size_.y_ * flipY;
	float bottom = (1.0f - state.anchor_.y_) * state.size_.y_ * flipY;

	// ----- TexStatus ----- //

	float rscSizeX = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Width);
	float rscSizeY = static_cast<float>(pTexManager_->TextureBuffer(texState.index_)->GetDesc().Height);

	Vec2 texLT = div ? texState.leftTop_ : Vec2(0.0f, 0.0f);
	Vec2 texRB = div ? (texState.leftTop_ + texState.size_) : Vec2(rscSizeX, rscSizeY);

	float texLeft   = texLT.x_ / rscSizeX;
	float texRight  = texRB.x_ / rscSizeX;
	float texTop    = texLT.y_ / rscSizeY;
	float texBottom = texRB.y_ / rscSizeY;

	v.push_back({ {  left,bottom,0.0f },{  texLeft,texBottom } }); // 左下
	v.push_back({ {  left,top,   0.0f },{  texLeft,texTop } });	   // 左上
	v.push_back({ { right,bottom,0.0f },{ texRight,texBottom } }); // 右下
	v.push_back({ { right,top,   0.0f },{ texRight,texTop } });	   // 右上
	vt_.TransferMap(v);

	size_    = state.size_;
	anchor_  = state.anchor_;
	isFlipX_ = state.isFlipX_;
	isFlipY_ = state.isFlipY_;

	tex_	    = texState.index_;
	texLeftTop_ = div ? texState.leftTop_ : Vec2(0.0f, 0.0f);
	texSize_    = div ? texState.size_ : Vec2(rscSizeX, rscSizeY);
}

void Sprite::Draw(Object& obj, const UINT tex)
{
	if (isInvisible_) { return; }
	obj.SetDrawCommand(Mat4::Identity(), projection_);
	pTexManager_->SetDrawCommand(tex);
	vt_.Draw();
}

void Sprite::Draw(Object& obj)
{
	if (isInvisible_) { return; }
	obj.SetDrawCommand(Mat4::Identity(), projection_);
	pTexManager_->SetDrawCommand(tex_);
	vt_.Draw();
}
