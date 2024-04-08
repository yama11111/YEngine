#include "Slime.h"
#include "SlimeDrawer.h"
#include "CharacterConfig.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "ScoreManager.h"
#include "WorldManager.h"

#include "Def.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector2;
using YMath::Vector3;
using YMath::BitFrag;

namespace 
{
	const uint32_t kBlowTime = 2;
}

std::unique_ptr<Slime> Slime::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<Slime> newObj = std::make_unique<Slime>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Slime::Initialize(const Transform::Status& status, const std::string& key)
{
	// ゲームキャラクター初期化
	BaseCharacter::Initialize("Slime", key, status, WorldManager::GetInstance()->BasePosMatPointer());

	// アタリ判定
	{
		BitFrag attribute{};
		attribute.SetFragTrue(AttributeType::eEnemy);

		SetCollider(GameCollider::Create(attribute));

		SetIsSaveColl(true);

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::eBlock);

			collider_->PushBackCollider(
				std::make_unique<YMath::Box2DCollider>(
					&worldPos_, speed_.VelocityPtr(), SlimeConfig::kRectSize, Vector3(), true, false),
				mask);
		}

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::ePlayer);
			mask.SetFragTrue(AttributeType::ePlayerAttack);

			collider_->PushBackCollider(
				std::make_unique<YMath::Box2DCollider>(
					&worldPos_, speed_.VelocityPtr(), SlimeConfig::kRectSize, Vector3(), false, false),
				mask);
		}

		collider_->SetPriority(1);
	}
	
	// 描画
	{
		std::unique_ptr<SlimeDrawer> drawer = SlimeDrawer::Create({ nullptr, nullptr, key, 1 });
		drawer->SetParentPosMatPointer(&posMat_);
		SetDrawer(std::move(drawer));

		// 立ちアニメーション
		drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eIdle), true);

		if (key == WorldKeyStr(WorldKey::eFeverKey))
		{
			drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eFever), true);
		}
	}

	blowTim_.Initialize(kBlowTime);
}

void Slime::UpdateBeforeCollision()
{
	IEnemy::UpdateBeforeCollision();
}

void Slime::UpdateAfterCollision()
{	
	IEnemy::UpdateAfterCollision();
	
	// 着地しているなら
	if (isLanding_)
	{
		// 瞬間
		if (isElderLanding_ == false)
		{
			// 着地アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eLanding), true);

		}
	}
	
	isElderLanding_ = isLanding_;

	if (worldKey_ == WorldKeyStr(WorldManager::GetInstance()->CurrentWorldKey()))
	{
		drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eCircleShadow), true);
	}
	else
	{
		drawer_->StopAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eCircleShadow));
	}

	// 演出終了 → 消滅
	if (drawer_->IsEndTimer(static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead)))
	{
		isExist_ = false;
	}
}

YGame::ICollisionInfomation Slime::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseCharacter::GetCollisionInfomation();

	result.attribute = AttributeType::eEnemy;
	result.radius = SlimeConfig::kRadius;

	return result;
}

void Slime::Hit(const uint32_t damage)
{
	// 被弾アニメーション
	static_cast<SlimeDrawer*>(drawer_.get())->PlayHitAnimation(damage);

	if (status_.IsAlive() == false)
	{
		// 死亡アニメーション
		drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead), true);
		ScoreManager::GetInstance()->AddScore(1000);
	}
}
