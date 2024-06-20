#include "Magnet.h"
#include "MagnetDrawer.h"

#include "WorldManager.h"
#include "CharacterConfig.h"

#include "SphereCollider.h"
#include "MathVector.h"

using YGame::Magnet;
using YGame::WorldManager;
using YMath::Vector3;
using YMath::BitFrag;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

std::unique_ptr<Magnet> Magnet::Create(const Transform::Status& status, const WorldKey key)
{
	std::unique_ptr<Magnet> newObj = std::make_unique<Magnet>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Magnet::Initialize(const Transform::Status& status, const WorldKey key)
{
	BaseCharacter::Initialize("Magnet", key, status);

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
					&worldPos_, MagnetConfig::kCollRadius),
				mask);
		}

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::eCoin);

			collider_->PushBackCollider(
				std::make_unique<YMath::SphereCollider>(
					&worldPos_, MagnetConfig::kSuctionRadius),
				mask);
		}
	}

	// 描画
	{
		std::unique_ptr<MagnetDrawer> drawer = MagnetDrawer::Create({ nullptr, nullptr, "Game", 1 });
		drawer->SetParentPosMatPointer(&posMat_);
		drawer->SetWorldKey(worldKey_);
		SetDrawer(std::move(drawer));
		
		drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eIdle));
	}

	isAct_ = false;
	actTimer_.Initialize(480);
}

void Magnet::UpdateBeforeCollision()
{
	if (drawer_->IsActAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eSuction)) == false &&
		drawer_->IsEndTimer(static_cast<uint32_t>(MagnetDrawer::AnimationType::eEarn)))
	{
		drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eSuction));
	}

	actTimer_.Update();
	if (actTimer_.IsEnd())
	{
		actTimer_.Reset();
		drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eDead));
	}

	BaseCharacter::UpdateBeforeCollision();
}

void Magnet::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();
	
	if (worldKey_ == WorldManager::GetInstance()->CurrentWorldKey())
	{
		drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eCircleShadow), true);
	}
	else
	{
		drawer_->StopAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eCircleShadow));
	}

	if (drawer_->IsEndTimer(static_cast<uint32_t>(MagnetDrawer::AnimationType::eDead)))
	{
		isExist_ = false;
	}
}

void Magnet::UpdatePos()
{
	if (pPlayerPos_ && actTimer_.IsAct())
	{
		worldPos_ = *pPlayerPos_ + Vector3(0, 2, 0);

		transform_->pos_ = worldPos_;

		posMat_ = YMath::MatTranslation(transform_->pos_) * pWorldMan->BasePosMat(WorldKeyEnum(updateKey_));
	}
	else
	{
		BaseCharacter::UpdatePos();
	}
}

YGame::ICollisionInfomation Magnet::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseCharacter::GetCollisionInfomation();

	result.attribute = AttributeType::eItem;
	result.radius = 0.0f;

	return result;
}

void Magnet::OnCollision(const ICollisionInfomation& info)
{
	if (info.attribute == AttributeType::ePlayer)
	{
		if (isAct_) { return; }
		
		isAct_ = true;
		actTimer_.Reset(true);
		pPlayerPos_ = info.pWorldPos;
		
		drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eEarn));
		status_.SetInvincible(true);
	}
	else if (info.attribute == AttributeType::eCoin)
	{
		if (isAct_ == false) { return; }

		Vector3 direction = *pPlayerPos_ - info.pTrfm->pos_;

		*info.pMoveDirection = direction.Normalized();
	}
}