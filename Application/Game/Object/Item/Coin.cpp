#include "Coin.h"
#include "CoinDrawer.h"

#include "ScoreManager.h"
#include "WorldManager.h"
#include "SphereCollider.h"

#include "CharacterConfig.h"

using YGame::Coin;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<Coin> Coin::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<Coin> newObj = std::make_unique<Coin>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Coin::Initialize(const Transform::Status& status, const std::string& key)
{
	BaseCharacter::Initialize(
		"Coin", key,
		status,
		{ 0.0f, 0.0f, +1.0f }, // 右向き
		CoinConfig::kAcceleration, CoinConfig::kMaxSpeed, false, 
		1, 0, 0);

	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::eCoin);

	SetCollider(GameCollider::Create(attribute));
	
	SetIsSaveColl(true);

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::ePlayer);
		mask.SetFragTrue(AttributeType::eItem);

		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&worldPos_, CoinConfig::kRadius),
			mask);
	}

	SetDrawer(CoinDrawer::Create({ nullptr, nullptr, key, 1}));
	
	drawer_->PlayAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eIdle), true);
}

void Coin::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Coin::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	if (worldKey_ == WorldKeyStr(WorldManager::GetInstance()->CurrentWorldKey()))
	{
		drawer_->PlayAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eCircleShadow), true);
	}
	else
	{
		drawer_->StopAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eCircleShadow));
	}

	// 演出終了 → 消滅
	if (drawer_->IsEndTimer(static_cast<uint32_t>(CoinDrawer::AnimationType::eEarn)))
	{
		isExist_ = false;
	}
}

YGame::ICollisionInfomation Coin::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseCharacter::GetCollisionInfomation();

	result.attribute = AttributeType::eCoin;
	result.radius = 0.0f;

	return result;
}

void Coin::OnCollision(const ICollisionInfomation& info)
{
	if (status_.IsInvincible()) { return; }
	
	if (info.attribute == AttributeType::ePlayer)
	{
		ScoreManager::GetInstance()->AddScore(100);
		ScoreManager::GetInstance()->AddCoin(1);
		
  		drawer_->PlayAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eEarn), true);
		status_.SetInvincible(true);
	}
	else if (info.attribute == AttributeType::eItem)
	{

	}
}