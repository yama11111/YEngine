#include "Sprite.h"

MatProjection Sprite::mP = MatProjection();
TextureManager* Sprite::texManager = nullptr;

Sprite::Sprite(const Vec2& size) :
	size(size),
	vt(Vertices2D(
		{
			{{   0.0f, size.y, 0.0f }, { 0.0f, 1.0f }}, // ¶‰º
			{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // ¶ã
			{{ size.x, size.y, 0.0f }, { 1.0f, 1.0f }}, // ‰E‰º
			{{ size.x,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // ‰Eã
		})
	)
{
	vt.Init();
}

void Sprite::Draw(Object2D& obj, const UINT tex)
{
	obj.cbT.cMapTrfm->mat = obj.mW.m * mP.m;
	vt.SetCommand();
	obj.SetCommand();
	texManager->SetCommand(tex);
	vt.Draw();
}

void Sprite::StaticInit()
{
	mP = MatProjection(MatProjection::OrthoGraphic);
	texManager = TextureManager::GetInstance();
}
