#include "Sprite.h"

MatProjection Sprite::mP = MatProjection();
ConstBufferManager* Sprite::cbManager = nullptr;
TextureManager* Sprite::texManager = nullptr;

Sprite::Sprite(const Vec2& size) :
	vtIdx(VertexIndex(
		{
			{{   0.0f, size.y, 0.0f }, { 0.0f, 1.0f }}, // ����
			{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // ����
			{{ size.x, size.y, 0.0f }, { 1.0f, 1.0f }}, // �E��
			{{ size.x,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // �E��
		},
		{
			0, 1, 2, // �O�p�`1��
			2, 1, 3, // �O�p�`2��
		}
		))
{
	vtIdx.Init();
	cbManager->CreateCB(cbM);
	cbManager->CreateCB(cbT);
}

void Sprite::Draw(MatWorld& mW, const UINT tex)
{
	cbT.cMapTrfm->mat = mW.m * mP.m;
	vtIdx.SetCommand();
	cbManager->SetCommand(cbM);
	cbManager->SetCommand(cbT);
	texManager->SetCommand(tex);
	vtIdx.Draw();
}

void Sprite::StaticInit()
{
	mP = MatProjection(MatProjection::OrthoGraphic);
	cbManager = ConstBufferManager::GetInstance();
	texManager = TextureManager::GetInstance();
}
