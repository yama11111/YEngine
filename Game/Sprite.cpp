#include "Sprite.h"
#include "CalcTransform.h"
#include <cassert>

using Game::Sprite;

Math::Mat4 Sprite::projection_ = Math::Mat4::Identity();
DX::PipelineSet Sprite::pplnSet_;
Game::TextureManager* Sprite::pTexManager_ = nullptr;

void Sprite::StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams)
{
	assert(pTexManager);
	pTexManager_ = pTexManager;
	projection_ = Math::MatOrthoGraphic();
	pplnSet_.Initialize(DX::PipelineSet::Type::SpriteT, rootParams);
}

void Sprite::StaticSetDrawCommand()
{
	pplnSet_.SetDrawCommand();
}

Sprite* Sprite::Create(const Status& state, const UINT tex)
{
	// インスタンス
	Sprite* instance = new Sprite();
	
	float flipX = state.isFlipX ? -1.0f : 1.0f;
	float flipY = state.isFlipY ? -1.0f : 1.0f;

	float left   = (0.0f - state.anchor.x_) * state.size.x_ * flipX;
	float right  = (1.0f - state.anchor.x_) * state.size.x_ * flipX;
	float top    = (0.0f - state.anchor.y_) * state.size.y_ * flipY;
	float bottom = (1.0f - state.anchor.y_) * state.size.y_ * flipY;

	instance->vt_.Initialize(
		{
			{ {  left,bottom,0.0f },{ 0.0f,1.0f } }, // 左下
			{ {  left,top,   0.0f },{ 0.0f,0.0f } }, // 左上
			{ { right,bottom,0.0f },{ 1.0f,1.0f } }, // 右下
			{ { right,top,   0.0f },{ 1.0f,0.0f } }, // 右上
		});

	instance->tex_ = tex;

	instance->size_    = state.size;
	instance->anchor_  = state.anchor;
	instance->isFlipX_ = state.isFlipX;
	instance->isFlipY_ = state.isFlipY;

	return instance;
}

void Sprite::SetSize(const Math::Vec2& size)
{
	if (size_ == size) { return; }
	SetStatus({ size, anchor_, isFlipX_, isFlipY_ });
}

void Sprite::SetAnchorPoint(const Math::Vec2& anchor)
{
	if (anchor_ == anchor) { return; }
	SetStatus({ size_, anchor, isFlipX_, isFlipY_ });
}

void Sprite::SetFrip(const bool isFlipX, const bool isFlipY)
{
	if (isFlipX_ == isFlipX && isFlipY_ == isFlipY) { return; }
	SetStatus({ size_, anchor_, isFlipX, isFlipY });
}

void Sprite::SetStatus(const Status& state)
{
	std::vector<DX::SpriteVData> v;

	float flipX = state.isFlipX ? -1.0f : 1.0f;
	float flipY = state.isFlipY ? -1.0f : 1.0f;

	float left   = (0.0f - state.anchor.x_) * state.size.x_ * flipX;
	float right  = (1.0f - state.anchor.x_) * state.size.x_ * flipX;
	float top    = (0.0f - state.anchor.y_) * state.size.y_ * flipY;
	float bottom = (1.0f - state.anchor.y_) * state.size.y_ * flipY;

	v.push_back({ {  left,bottom,0.0f },{ 0.0f,1.0f } });
	v.push_back({ {  left,top,   0.0f },{ 0.0f,0.0f } });
	v.push_back({ { right,bottom,0.0f },{ 1.0f,1.0f } });
	v.push_back({ { right,top,   0.0f },{ 1.0f,0.0f } });
	vt_.TransferMap(v);

	size_    = state.size;
	anchor_  = state.anchor;
	isFlipX_ = state.isFlipX;
	isFlipY_ = state.isFlipY;
}

void Sprite::Draw(Object& obj, const UINT tex)
{
	if (isInvisible_) { return; }
	obj.SetDrawCommand(Math::Mat4::Identity(), projection_);
	pTexManager_->SetDrawCommand(tex);
	vt_.Draw();
}

void Sprite::Draw(Object& obj)
{
	if (isInvisible_) { return; }
	obj.SetDrawCommand(Math::Mat4::Identity(), projection_);
	pTexManager_->SetDrawCommand(tex_);
	vt_.Draw();
}
