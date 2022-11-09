#include "Sprite.h"
#include "Calc.h"

using Object::Sprite;

Math::Mat4 Sprite::projection_ = Math::Mat4::Identity();
DX::TextureManager* Sprite::pTexManager_ = nullptr;

void Sprite::StaticInitialize(DX::TextureManager* pTexManager)
{
	projection_ = Math::MatOrthoGraphic();
	pTexManager_ = pTexManager;
}

Sprite::Sprite(const Math::Vec2& size) :
	size_(size)
{
	vt_.Initialize(
		{
			{{   0.0f, size.y_, 0.0f }, { 0.0f, 1.0f }}, // ¶‰º
			{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // ¶ã
			{{ size.x_, size.y_, 0.0f }, { 1.0f, 1.0f }}, // ‰E‰º
			{{ size.x_,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // ‰Eã
		}
	);
}

void Sprite::Draw(Transform& trfm, const UINT tex)
{
	trfm.SetDrawCommand(Math::Mat4::Identity(), projection_);
	pTexManager_->SetDrawCommand(tex);
	vt_.Draw();
}
