#include "Sprite.h"
#include "Calc.h"
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

Sprite::Sprite(const Math::Vec2& size) :
	size_(size)
{
	vt_.Initialize(
		{
			{{   0.0f, size.y_, 0.0f }, { 0.0f, 1.0f }}, // ¶‰º
			{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // ¶ã
			{{ size.x_, size.y_, 0.0f }, { 1.0f, 1.0f }}, // ‰E‰º
			{{ size.x_,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // ‰Eã
		},
		false
	);
}

void Sprite::Draw(Transform& trfm, const UINT tex)
{
	trfm.SetDrawCommand(Math::Mat4::Identity(), projection_);
	pTexManager_->SetDrawCommand(tex);
	vt_.Draw();
}
