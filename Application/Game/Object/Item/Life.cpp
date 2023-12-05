#include "Life.h"
#include "CharacterConfig.h"
#include "LifeDrawer.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"

using YGame::Life;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<Life> Life::Create(const Transform::Status& status)
{
	std::unique_ptr<Life> newObj = std::make_unique<Life>();

	newObj->Initialize(status);

	return std::move(newObj);
}

void Life::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Life",
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
		mask.SetFragTrue(AttributeType::ePet);

		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&transform_->pos_, speed_.VelocityPtr(), CoinConfig::kRadius, Vector3(), false, false), 
		mask);
	}

	SetDrawer(LifeDrawer::Create(nullptr, 1));

	//InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), CoinConfig::kRadius, 1));
	drawer_->PlayAnimation(static_cast<uint32_t>(LifeDrawer::AnimationType::eIdle), true);

	drawer_->SetParent(transform_.get());
}

void Life::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Life::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	// 演出終了 → 消滅
	if (drawer_->IsEndTimer(static_cast<uint32_t>(LifeDrawer::AnimationType::eEarn)) == false)
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

	if (info.attribute == AttributeType::ePlayer ||
		info.attribute == AttributeType::ePet)
	{
		info.pStatus->SetHP(info.pStatus->HP() + 1);
		static_cast<LifeDrawer*>(drawer_.get())->PlayRecoveryAnimation();
		
		status_.SetInvincible(true);
	}
}