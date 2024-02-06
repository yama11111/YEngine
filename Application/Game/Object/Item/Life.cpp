#include "Life.h"
#include "CharacterConfig.h"
#include "LifeDrawer.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"

using YGame::Life;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<Life> Life::Create(
	const Transform::Status& status,
	const std::vector<std::string>& drawKeys)
{
	std::unique_ptr<Life> newObj = std::make_unique<Life>();

	newObj->Initialize(status);
	newObj->SetDrawKeys(drawKeys);

	return std::move(newObj);
}

void Life::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Coin",
		status,
		{ 0.0f, 0.0f, +1.0f }, // 右向き
		CoinConfig::kAcceleration, CoinConfig::kMaxSpeed, false,
		1, 0, 0);

	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::eItem);

	SetCollider(GameCollider::Create(attribute));

	SetIsSaveColl(true);

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::ePlayer);

		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&worldPos_, CoinConfig::kRadius),
			mask);
	}

	SetDrawer(LifeDrawer::Create(nullptr, nullptr, 1));

	drawer_->PlayAnimation(static_cast<uint32_t>(LifeDrawer::AnimationType::eIdle), true);
}

void Life::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Life::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	// 演出終了 → 消滅
	if (drawer_->IsEndTimer(static_cast<uint32_t>(LifeDrawer::AnimationType::eEarn)))
	{
		isExist_ = false;
	}
}

YGame::InfoOnCollision Life::GetInfoOnCollision()
{
	InfoOnCollision result = BaseCharacter::GetInfoOnCollision();

	result.attribute = AttributeType::eItem;
	result.radius = 0.0f;

	return result;
}

void Life::OnCollision(const InfoOnCollision& info)
{
	if (status_.IsInvincible()) { return; }

	if (info.attribute == AttributeType::ePlayer)
	{
		info.pStatus->SetHP(info.pStatus->HP() + 20);
		static_cast<LifeDrawer*>(drawer_.get())->PlayRecoveryAnimation();
		
		status_.SetInvincible(true);
	}
}