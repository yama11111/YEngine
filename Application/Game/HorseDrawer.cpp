#include "HorseDrawer.h"

using YGame::HorseDrawer;
using YGame::Model;

Model* HorseDrawer::spModel_ = nullptr;

void HorseDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル挿入
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eToon;
}

void HorseDrawer::Update()
{
	BaseDrawer::Update();
}

void HorseDrawer::Draw()
{
	BaseDrawer::Draw();
}

void HorseDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

HorseDrawer::HorseDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

HorseDrawer::HorseDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void HorseDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::LoadObj("horse", true);
}
