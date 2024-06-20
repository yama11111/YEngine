#include "Skydome.h"
#include "SkydomeDrawer.h"

#include "WorldManager.h"

using YGame::Skydome;
using YMath::Vector3;
using YMath::BitFrag;

namespace
{
	// プレイヤー位置
	YMath::Vector3 playerPos = {};
}

std::unique_ptr<Skydome> Skydome::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<Skydome> newObj = std::make_unique<Skydome>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Skydome::Initialize(const Transform::Status& status, const std::string& key)
{
	GameObject::Initialize("Skydome", status);

	SetUpdateKey(key);
	SetDrawKeys({ key });

	SkydomeDrawer::Type type = SkydomeDrawer::Type::eWhite;
	if (key == WorldKeyStr(WorldKey::eFeverKey))
	{
		type = SkydomeDrawer::Type::ePurple;
	}
	else if (key == WorldKeyStr(WorldKey::eJourneyKey))
	{
		type = SkydomeDrawer::Type::eGreen;
	}

	SetDrawer(SkydomeDrawer::Create({ nullptr, nullptr, "Game", 2 }, type));
}

void Skydome::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Skydome::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}

void Skydome::SetPlayerPos(const Vector3& pos)
{
	playerPos = pos;
}