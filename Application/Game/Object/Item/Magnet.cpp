#include "Magnet.h"
#include "CharacterConfig.h"
#include "MagnetDrawer.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"

using YGame::Magnet;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<Magnet> Magnet::Create(const Transform::Status& status)
{
	std::unique_ptr<Magnet> newObj = std::make_unique<Magnet>();

	newObj->Initialize(status);

	return std::move(newObj);
}

void Magnet::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Magnet",
		status,
		{ 0.0f, 0.0f, +1.0f }, // 右向き
		{}, {}, false,
		1, 0, 0);

	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::eItem);
	
	SetCollider(GameCollider::Create(attribute));

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::ePlayer);

		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&transform_->pos_, MagnetConfig::kCollRadius),
			mask);
	}
	
	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eCoin);

		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&transform_->pos_, MagnetConfig::kSuctionRadius),
			mask);
	}

	SetDrawer(MagnetDrawer::Create(nullptr, 1));

	isAct_ = false;
	actTimer_.Initialize(480);

	drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eIdle));
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
		isAct_ = false;
		actTimer_.Reset();
		drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eDead));
	}

	if (pPlayerTrfm_ && actTimer_.IsAct())
	{
		transform_->pos_ = pPlayerTrfm_->pos_ + Vector3(0, 2, 0);
	}

	BaseCharacter::UpdateBeforeCollision();
}

void Magnet::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	if (drawer_->IsEndTimer(static_cast<uint32_t>(MagnetDrawer::AnimationType::eDead)))
	{
		isExist_ = false;
	}
}

YGame::InfoOnCollision Magnet::GetInfoOnCollision()
{
	InfoOnCollision result = BaseCharacter::GetInfoOnCollision();

	result.attribute = AttributeType::eItem;
	result.radius = 0.0f;

	return result;
}

void Magnet::OnCollision(const InfoOnCollision& info)
{
	if (info.attribute == AttributeType::ePlayer)
	{
		if (isAct_) { return; }
		
		isAct_ = true;
		actTimer_.Reset(true);
		pPlayerTrfm_ = info.pTrfm;
		
		drawer_->PlayAnimation(static_cast<uint32_t>(MagnetDrawer::AnimationType::eEarn));
		status_.SetInvincible(true);
	}
	else if (info.attribute == AttributeType::eCoin)
	{
		if (isAct_ == false) { return; }

		Vector3 direction = pPlayerTrfm_->pos_ - info.pTrfm->pos_;

		*info.pMoveDirection_ = direction.Normalized();
	}
}