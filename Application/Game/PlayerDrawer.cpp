#include "PlayerDrawer.h"

using YGame::PlayerDrawer;
using YGame::Model;

Model* PlayerDrawer::spModel_ = nullptr;

void PlayerDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	// モデル挿入
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eToon;
}

void PlayerDrawer::Update()
{
	BaseDrawer::Update();
}

void PlayerDrawer::Draw()
{
	BaseDrawer::Draw();
}

void PlayerDrawer::PlayAnimation(const uint16_t index, const uint16_t frame)
{

}

PlayerDrawer::PlayerDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

PlayerDrawer::PlayerDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void PlayerDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::CreateCube("player.png");
}
