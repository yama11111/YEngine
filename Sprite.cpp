#include "Sprite.h"

MatProjection Sprite::mP = MatProjection();
TextureManager* Sprite::texManager = nullptr;

Sprite::Sprite(const Vec2& size) :
	size(size),
	vt(Vertices2D(
		{
			{{   0.0f, size.y, 0.0f }, { 0.0f, 1.0f }}, // 左下
			{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // 左上
			{{ size.x, size.y, 0.0f }, { 1.0f, 1.0f }}, // 右下
			{{ size.x,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // 右上
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
