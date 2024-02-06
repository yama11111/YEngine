#include "Coin.h"
#include "CharacterConfig.h"
#include "ScoreManager.h"
#include "CoinDrawer.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"

using YGame::Coin;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<Coin> Coin::Create(
	const Transform::Status& status,
	const std::vector<std::string>& drawKeys)
{
	std::unique_ptr<Coin> newObj = std::make_unique<Coin>();

	newObj->Initialize(status);
	newObj->SetDrawKeys(drawKeys);

	return std::move(newObj);
}

void Coin::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Coin",
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

	SetDrawer(CoinDrawer::Create(nullptr, nullptr, 1));
	
	drawer_->PlayAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eIdle), true);
}

void Coin::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Coin::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	// 演出終了 → 消滅
	if (drawer_->IsEndTimer(static_cast<uint32_t>(CoinDrawer::AnimationType::eEarn)))
	{
		isExist_ = false;
	}
}

YGame::InfoOnCollision Coin::GetInfoOnCollision()
{
	InfoOnCollision result = BaseCharacter::GetInfoOnCollision();

	result.attribute = AttributeType::eCoin;
	result.radius = 0.0f;

	return result;
}

void Coin::OnCollision(const InfoOnCollision& info)
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