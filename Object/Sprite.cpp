#include "Sprite.h"

using Object::Sprite;

Object::MatProjection Sprite::mP = MatProjection();
DX::GPUResource::TextureManager* Sprite::texManager = nullptr;

void Sprite::StaticInit()
{
	mP = MatProjection(MatProjection::OrthoGraphic);
	texManager = DX::GPUResource::TextureManager::GetInstance();
}

Sprite::Sprite(const Math::Vec2& size) :
	size(size),
	vt(DX::GPUResource::Vertices2D(
		{
			{{   0.0f, size.y, 0.0f }, { 0.0f, 1.0f }}, // ¶‰º
			{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // ¶ã
			{{ size.x, size.y, 0.0f }, { 1.0f, 1.0f }}, // ‰E‰º
			{{ size.x,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // ‰Eã
		})
	)
{
	vt.Initialize();
}

void Sprite::Draw(Transform& trfm, const UINT tex)
{
	trfm.cbT.mapTrfm->mat = trfm.mW.m * mP.m;
	vt.SetCommand();
	trfm.SetCommand();
	texManager->SetCommand(tex);
	vt.Draw();
}
