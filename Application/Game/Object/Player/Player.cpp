#include "Player.h"
#include "PlayerDrawer.h"
#include "CharacterConfig.h"

#include "GameObjectManager.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"

#include "ScoreManager.h"
#include "WorldManager.h"
#include "Skydome.h"

#include "MathVector.h"
#include "MathUtil.h"

#include "Keys.h"
#include "Pad.h"

#include <cassert>
#include <imgui.h>

using YGame::Player;
using YGame::WorldManager;
using YGame::GameCamera;
using YMath::Vector2;
using YMath::Vector3;
using YMath::BitFrag;
using YInput::Keys;
using YInput::Pad;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
	GameCamera* pCamera = nullptr;

	const YMath::Vector3 kMaxWorldSize = { 2000.0f, 150.0f, 150.0f };
}

void Player::StaticInitialize(GameCamera* pGameCamera)
{
	assert(pGameCamera);

	pCamera = pGameCamera;
}

std::unique_ptr<Player> Player::Create(const Transform::Status& status, const WorldKey key)
{
	std::unique_ptr<Player> newObj = std::make_unique<Player>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Player::Initialize(const Transform::Status& status, const WorldKey key)
{
	BaseCharacter::Initialize("Player", key, status);

	ScoreManager::GetInstance()->SetMaxHP(PlayerConfig::kHP);
	ScoreManager::GetInstance()->SetHP(PlayerConfig::kHP);

	// アタリ判定
	{
		BitFrag attribute{};
		attribute.SetFragTrue(AttributeType::ePlayer);

		SetCollider(GameCollider::Create(attribute));

		SetIsSaveColl(true);

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::eBlock);

			collider_->PushBackCollider(
				std::make_unique<YMath::Box2DCollider>(
					&worldPos_, speed_.VelocityPtr(), PlayerConfig::kPhysicsRect, Vector3(), true, false),
				mask);
		}

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::eGate);
			mask.SetFragTrue(AttributeType::eGoal);

			collider_->PushBackCollider(
				std::make_unique<YMath::Box2DCollider>(
					&worldPos_, PlayerConfig::kPhysicsRect),
				mask);
		}

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::eEnemy);
			mask.SetFragTrue(AttributeType::eEnemyAttack);

			collider_->PushBackCollider(
				std::make_unique<YMath::Box2DCollider>(
					&worldPos_, speed_.VelocityPtr(), PlayerConfig::kCollRect, Vector3(), false, false),
				mask);
		}

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::eCoin);
			mask.SetFragTrue(AttributeType::eItem);

			collider_->PushBackCollider(
				std::make_unique<YMath::SphereCollider>(
					&worldPos_, PlayerConfig::kRadius),
				mask);
		}

		collider_->SetPriority(1);
	}
	
	// 描画
	{
		std::unique_ptr<PlayerDrawer> drawer = PlayerDrawer::Create({ nullptr, nullptr, "Game", 0 });
		drawer->SetParentPosMatPointer(&posMat_);
		drawer->SetWorldKey(worldKey_);
		SetDrawer(std::move(drawer));
		
		// 立ちアニメーション
		drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eIdle), true);
		drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eCircleShadow), true);
	}

	jumpCounter_ = 0;

	maxJumpCount_ = PlayerConfig::kMaxJumpCount;

	isJumpMoment_ = false;
	isLandingMoment_ = false;
	isLanding_ = false;
	isElderLanding_ = false;

	GameObjectManager::GetInstance()->SetBasePoint(worldPos_);
	
	baseTrfm_.Initialize({ -status.pos_, {}, {1.0f,1.0f,1.0f} });
	baseTrfm_.UpdateMatrix();
	pWorldMan->SetBaseMat(worldKey_, baseTrfm_.m);

	posMat_ = YMath::MatTranslation(worldPos_) * pWorldMan->BasePosMat(worldKey_);

	transform_->pos_ = {};
	transform_->UpdateMatrix();
}

void Player::UpdateControl()
{
	// 自動で前に進む
	moveDirection_.x = +1.0f;
	direction_ = Vector3(+1.0f, 0.0f, 0.0f);

	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A))
	{
		Jump();
	}

	if (Keys::GetInstance()->IsDown(DIK_V) ||
		Pad::GetInstance()->IsDown(YInput::PadButton::XIP_X))
	{
		Drop();
	}
}

void Player::UpdatePos()
{
	localPos_ += speed_.Velocity();

	worldPos_ = initPos_ + localPos_;
	
	GameObjectManager::GetInstance()->SetBasePoint(worldPos_);
	Skydome::SetPlayerPos(transform_->pos_);
	
	baseTrfm_.pos_ -= speed_.Velocity();
	baseTrfm_.UpdateMatrix();
	pWorldMan->SetBaseMat(WorldManager::GetInstance()->CurrentWorldKey(), baseTrfm_.m);
	
	pCamera->SetPlayerPos(worldPos_);

	posMat_ = YMath::MatTranslation(worldPos_) * pWorldMan->BasePosMat(worldKey_);
}

void Player::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Player::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	// 着地しているなら
	if (isLanding_)
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;

		// 瞬間
		if (isElderLanding_ == false)
		{
			// 着地アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eLanding), true);

			// 移動アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove), false);
		}
	}
	// 離陸した瞬間
	else if (isElderLanding_)
	{
		// 移動アニメーションをやめる
		drawer_->StopAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove));
	}
	
	isDrop_ = false;
	isJumpMoment_ = false;
	isLandingMoment_ = false;
	isElderLanding_ = isLanding_;

	pWorldMan->SetIsPlayerLanding(isLanding_);

	ScoreManager::GetInstance()->SetHP(status_.HP());
	
	SetWorldKey(WorldManager::GetInstance()->CurrentWorldKey());
}

YGame::ICollisionInfomation Player::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseCharacter::GetCollisionInfomation();

	result.attribute = AttributeType::ePlayer;
	result.radius = PlayerConfig::kRadius;

	return result;
}

void Player::SetWorldKey(const WorldKey worldKey)
{
	worldKey_ = worldKey;

	std::string key = WorldKeyStr(worldKey);

	SetUpdateKey(key);
	SetDrawKeys({ key });

	if (drawer_)
	{
		static_cast<BaseCharacterDrawer*>(drawer_.get())->SetWorldKey(worldKey);
	}
}

void Player::Jump(const bool isJumpCount)
{
	// ジャンプカウントするなら
	if (isJumpCount)
	{
		// ジャンプ回数 が 最大回数超えてたら 弾く
		if (jumpCounter_ >= maxJumpCount_) { return; }

		jumpCounter_++;

		isJumpMoment_ = true;
		isLanding_ = false;
	}

	moveDirection_.y = 0.0f;
	speed_.VelocityRef().y = PlayerConfig::kJumpSpeed;

	// ジャンプアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump), true);
	pCamera->PlayAnimation(GameCamera::AnimationType::eJump);
}

void Player::Drop()
{
	isDrop_ = true;

	moveDirection_.y = -1.0f;

	// 攻撃アニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eAttack), false);
	drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump), true);
	pCamera->PlayAnimation(GameCamera::AnimationType::eDrop);
}

void Player::OffScreenProcess()
{
	// 画面外なら死ぬ
	if (YMath::InRange(initPos_ + localPos_, -kMaxWorldSize, kMaxWorldSize) == false)
	{
		WorldManager::GetInstance()->GameOver();
	}
}

void Player::OnCollision(const ICollisionInfomation& info)
{
	// 敵
	if (info.attribute == AttributeType::eEnemy)
	{
		// 自分 が 敵 より上にいる なら
		if (worldPos_.y - (PlayerConfig::kRadius / 4.0f) >= info.pWorldPos->y + (info.radius / 4.0f))
		{
			pCamera->Shaking(1.0f, 0.2f, 100.0f);

			// ジャンプ
			Jump(false);
		}
		// 自分 が 敵 より下 なら
		else
		{
			// ダメージを受ける
			status_.Damage(info.pStatus->Attack(), true);

			if (status_.IsAlive() == false)
			{
				// 死亡アニメーション
				drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eDead), true);

				WorldManager::GetInstance()->GameOver();
			}

			pCamera->Shaking(2.0f, 0.2f, 100.0f);

			// 被弾アニメーション
			drawer_->PlayAnimation(static_cast<uint32_t>(PlayerDrawer::AnimationType::eHit), true);
		}
	}
	// ブロック
	else if (info.attribute == AttributeType::eBlock)
	{
		if (worldPos_.y <= info.pWorldPos->y) { return; }

		// 着地
		isLanding_ = true;

		if (isElderLanding_ == false)
		{
			isLandingMoment_ = true;
		}
		if (isDrop_ && isElderLanding_ == false)
		{
			pCamera->Shaking(0.2f, 0.05f, 100.0f);
		}
	}
	// ゲート
	else if (info.attribute == AttributeType::eGate)
	{
		if (status_.IsInvincible()) { return; }

		status_.ActivateInvincible();

		//speed_.SetMax(speed_.Max() * 1.2f);
		
		localPos_ = {};
		initPos_ = WorldManager::GetInstance()->Pass();
		baseTrfm_.pos_ = -initPos_;
		
		uint32_t anime = static_cast<uint32_t>(PlayerDrawer::AnimationType::eNormalColor);
		GameCamera::AnimationType camAnime = GameCamera::AnimationType::eNormal;
		
		if (WorldKey::eJourneyKey == WorldManager::GetInstance()->CurrentWorldKey())
		{
			anime = static_cast<uint32_t>(PlayerDrawer::AnimationType::eSingleColor);
			camAnime = GameCamera::AnimationType::ePass;
		}
		if (WorldKey::eFeverKey == WorldManager::GetInstance()->CurrentWorldKey())
		{
			ScoreManager::GetInstance()->AddSpeedLevel();
		}
		
		drawer_->PlayAnimation(anime);
		pCamera->PlayAnimation(camAnime);

	}
	// ゴール
	else if (info.attribute == AttributeType::eGoal)
	{
		WorldManager::GetInstance()->ClearStage();
	}
}

void Player::DrawDebugTextContent()
{
	BaseCharacter::DrawDebugTextContent();
}
