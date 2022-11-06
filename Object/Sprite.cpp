#include "Sprite.h"

using Object::Sprite;
using Math::MatProjection;

MatProjection Sprite::mp_ = MatProjection(MatProjection::OrthoGraphic);
DX::TextureManager* Sprite::pTexManager_ = nullptr;

void Sprite::StaticInitialize(DX::TextureManager* pTexManager)
{
	mp_ = MatProjection(MatProjection::OrthoGraphic);
	pTexManager_ = pTexManager;
}

Sprite::Sprite(const Math::Vec2& size) :
	size_(size)
{
	vt_.Initialize(
		{
			{{   0.0f, size.y, 0.0f }, { 0.0f, 1.0f }}, // ¶‰º
			{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // ¶ã
			{{ size.x, size.y, 0.0f }, { 1.0f, 1.0f }}, // ‰E‰º
			{{ size.x,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // ‰Eã
		}
	);
}

void Sprite::Draw(Transform& trfm, const UINT tex)
{
	trfm.SetDrawCommand(Math::Mat4::Identity(), mp_.m_);
	pTexManager_->SetDrawCommand(tex);
	vt_.Draw();
}
