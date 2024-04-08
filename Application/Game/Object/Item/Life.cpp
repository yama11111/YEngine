#include "Life.h"
#include "LifeDrawer.h"

#include "WorldManager.h"
#include "CharacterConfig.h"

#include "SphereCollider.h"

using YGame::Life;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<Life> Life::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<Life> newObj = std::make_unique<Life>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Life::Initialize(const Transform::Status& status, const std::string& key)
{
	BaseCharacter::Initialize("Coin", key, status, WorldManager::GetInstance()->BasePosMatPointer());

	// アタリ判定
	{
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
	}

	// 描画
	{
		std::unique_ptr<LifeDrawer> drawer = LifeDrawer::Create({ nullptr, nullptr, key, 1 });
		drawer->SetParentPosMatPointer(&posMat_);
		SetDrawer(std::move(drawer));

		drawer_->PlayAnimation(static_cast<uint32_t>(LifeDrawer::AnimationType::eIdle), true);
	}
}

void Life::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Life::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	if (worldKey_ == WorldKeyStr(WorldManager::GetInstance()->CurrentWorldKey()))
	{
		drawer_->PlayAnimation(static_cast<uint32_t>(LifeDrawer::AnimationType::eCircleShadow), true);
	}
	else
	{
		drawer_->StopAnimation(static_cast<uint32_t>(LifeDrawer::AnimationType::eCircleShadow));
	}

	// 演出終了 → 消滅
	if (drawer_->IsEndTimer(static_cast<uint32_t>(LifeDrawer::AnimationType::eEarn)))
	{
		isExist_ = false;
	}
}

YGame::ICollisionInfomation Life::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseCharacter::GetCollisionInfomation();

	result.attribute = AttributeType::eItem;
	result.radius = 0.0f;

	return result;
}

void Life::OnCollision(const ICollisionInfomation& info)
{
	if (status_.IsInvincible()) { return; }

	if (info.attribute == AttributeType::ePlayer)
	{
		info.pStatus->SetHP(info.pStatus->HP() + 20);
		static_cast<LifeDrawer*>(drawer_.get())->PlayRecoveryAnimation();
		
		status_.SetInvincible(true);
	}
}