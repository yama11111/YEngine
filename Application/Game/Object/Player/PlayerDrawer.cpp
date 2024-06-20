#include "PlayerDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

#include "WorldManager.h"
#include "CircleShadowManager.h"
#include "ColorConfig.h"

#include "DustParticle.h"
#include "DebriParticle.h"
#include "AfterimageParticle.h"

#include "Def.h"
#include "MathVector.h"
#include <cmath>

using YGame::PlayerDrawer;
using YGame::Model;
using YGame::ViewProjectionManager;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Timer;
using AnimeTimer = YGame::BaseDrawer::AnimationTimer;

namespace
{
	// モデルポインタ
	std::array<Model*, 3> pModels{};
	
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
	
	// アニメーション番号
	const uint32_t kIdleIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eIdle);
	const uint32_t kMoveIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove);
	const uint32_t kJumpIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump);
	const uint32_t kLandingIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eLanding);
	const uint32_t kAttackIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eAttack);
	const uint32_t kHitIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eHit);
	const uint32_t kDeadIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eDead);
	const uint32_t kCircleShadowIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eCircleShadow);
	const uint32_t kNormalColorIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eNormalColor);
	const uint32_t kSingleColorIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eSingleColor);

	// アニメーションタイマー
	const AnimeTimer kIdleTimer		 = { Timer(60), true };
	const AnimeTimer kMoveTimer		 = { Timer( 8), true };
	const AnimeTimer kJumpTimer		 = { Timer(20), false };
	const AnimeTimer kLandingTimer	 = { Timer(20), false };
	const AnimeTimer kAttackTimer	 = { Timer(1), false };
	const AnimeTimer kHitTimer		 = { Timer( 4), false };
	const AnimeTimer kDeadTimer		 = { Timer(10), false };
	const AnimeTimer kCircleShadowTimer	 = { Timer( 1), true };
	const AnimeTimer kNormalColorTimer	 = { Timer( 1), false };
	const AnimeTimer kSingleColorTimer	 = { Timer( 1), false };

	// アニメーション値
	const std::vector<Vector3> kJumpWobbleScaleValues =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(-0.5f, +1.0f, -0.5f),
		Vector3(0.0f, 0.0f, 0.0f),
	};

	const std::vector<Vector3> kLandingWobbleScaleValues =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(+0.5f, -0.25f, +0.5f),
		Vector3(0.0f, 0.0f, 0.0f),
	};

	const float kExponent = 3.0f;

	const float kHeight = 0.5f;

	const float kHitSwing = 0.2f;
	const float kHitPlace = 100.0f;

	// パーティクル
	const size_t kMoveDustNum = 4;
	const size_t kJumpDustNum = 4;
	
	const size_t kLandingDirectionNum = 8;
	const size_t kLandingDustNum = 2;

	const size_t kDeadDebriNum = 16;
}

std::unique_ptr<PlayerDrawer> PlayerDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<PlayerDrawer> newDrawer = std::make_unique<PlayerDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void PlayerDrawer::LoadResource()
{
	// モデル設定
	pModels[1] = Model::LoadObj("player/body", true);
	pModels[0] = Model::LoadObj("player/leg_L", true);
	pModels[2] = Model::LoadObj("player/leg_R", true);
}

void PlayerDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	cbColor_->data_.texColorRate = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skTurquoise[5];
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Body", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Leg_L", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Leg_R", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	
	SetShaderTag("ModelToon");

	SetShaderTag("Body_O", "ModelOutline");
	SetShaderTag("Leg_L_O", "ModelOutline");
	SetShaderTag("Leg_R_O", "ModelOutline");

	InsertConstBuffer("Body_O", cbOutline_.get());
	InsertConstBuffer("Leg_L_O", cbOutline_.get());
	InsertConstBuffer("Leg_R_O", cbOutline_.get());
	
	slimeActor_.Initialize(0, { {} }, 0);
	hitActor_.Initialize();

	isSeeThrough_ = false;
}

void PlayerDrawer::InitializeObjects()
{
	InsertObject("Body",	 DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModels[0]));
	InsertObject("Leg_L",	 DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModels[1]));
	InsertObject("Leg_R",	 DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModels[2]));

	InsertObject("Body_O",	 DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModels[0]));
	InsertObject("Leg_L_O",	 DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModels[1]));
	InsertObject("Leg_R_O",	 DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModels[2]));
}

void PlayerDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, kIdleTimer);
	InsertAnimationTimer(kMoveIndex, kMoveTimer);
	InsertAnimationTimer(kJumpIndex, kJumpTimer);
	InsertAnimationTimer(kLandingIndex, kLandingTimer);
	InsertAnimationTimer(kAttackIndex, kAttackTimer);
	InsertAnimationTimer(kHitIndex, kHitTimer);
	InsertAnimationTimer(kDeadIndex, kDeadTimer);
	InsertAnimationTimer(kCircleShadowIndex, kCircleShadowTimer);
	InsertAnimationTimer(kNormalColorIndex, kNormalColorTimer);
	InsertAnimationTimer(kSingleColorIndex, kSingleColorTimer);
}

void PlayerDrawer::GetReadyForAnimation(const uint32_t index)
{
	// 時間
	const uint32_t frame = animationTimers_[index].timer.EndFrame();

	// 立ち
	if (index & static_cast<uint32_t>(AnimationType::eIdle))
	{
	}
	// 移動
	else if (index & static_cast<uint32_t>(AnimationType::eMove))
	{
		// 土煙を発生
		// 自分の足元
		float height = 0.5f;
		Vector3 pos = *pParentWorldPos_ - Vector3(0.0f, height, 0.0f);

		// 正面と逆方向 かつ 上方向
		float rad = pParent_->rota_.y;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, +0.1f, 0.0f);

		DustParticle::Emit(worldKey_, kMoveDustNum, pos, powerDirection, pVPMan->ViewProjectionPtr(vpKey_));
	}
	// ジャンプ
	else if (index & static_cast<uint32_t>(AnimationType::eJump))
	{
		// ブヨブヨアニメ (伸びる)
		slimeActor_.Initialize(frame, kJumpWobbleScaleValues, kExponent);
		slimeActor_.Wobble();

		// 自分の足元に土煙を発生
		Vector3 pos = *pParentWorldPos_ - Vector3(0.0f, kHeight, 0.0f);

		// 正面と逆方向 かつ 下方向
		float rad = pParent_->rota_.y;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, -0.5f, 0.0f);

		DustParticle::Emit(worldKey_, kJumpDustNum, pos, powerDirection, pVPMan->ViewProjectionPtr(vpKey_));
	}
	// 着地
	else if (index & static_cast<uint32_t>(AnimationType::eLanding))
	{
		// ブヨブヨアニメ (潰れる)
		slimeActor_.Initialize(frame, kLandingWobbleScaleValues, kExponent);
		slimeActor_.Wobble();

		// 自分の足元に土煙を発生
		Vector3 pos = *pParentWorldPos_ - Vector3(0.0f, kHeight, 0.0f);

		// 自分の周囲 かつ 上方向
		for (size_t i = 0; i < kLandingDirectionNum; i++)
		{
			// 角度 = 2π (360) / 向きの数 * index
			float rad = (2.0f * kPI / static_cast<float>(kLandingDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.1f, 0.0f);

			DustParticle::Emit(worldKey_, kLandingDustNum, pos, powerDirection, pVPMan->ViewProjectionPtr(vpKey_));
		}
	}
	// 攻撃
	else if (index & static_cast<uint32_t>(AnimationType::eAttack))
	{
		isAttack_ = true;
	}
	// 被弾
	else if (index & static_cast<uint32_t>(AnimationType::eHit))
	{
		hitActor_.Hit(kHitSwing, kHitSwing / static_cast<float>(frame), kHitPlace);
	}
	// 死亡
	else if (index & static_cast<uint32_t>(AnimationType::eDead))
	{
		DebriParticle::Emit(worldKey_, kDeadDebriNum, *pParentWorldPos_, pVPMan->ViewProjectionPtr(vpKey_));
	}
	// 原色
	else if (index & static_cast<uint32_t>(AnimationType::eNormalColor))
	{
		SetShaderTag("ModelToon");

		SetShaderTag("Body_O", "ModelOutline");
		SetShaderTag("Leg_L_O", "ModelOutline");
		SetShaderTag("Leg_R_O", "ModelOutline");

		cbColor_->data_.baseColor = { 1.0f,1.0f,1.0f,1.0f };
		cbOutline_->data_.color = ColorConfig::skTurquoise[5];
	}
	// 単色
	else if (index & static_cast<uint32_t>(AnimationType::eSingleColor))
	{
		SetShaderTag("ModelSingleColorFront");

		SetShaderTag("Body_O", "ModelOutline");
		SetShaderTag("Leg_L_O", "ModelOutline");
		SetShaderTag("Leg_R_O", "ModelOutline");

		cbColor_->data_.baseColor = ColorConfig::skTurquoise[0];
		cbOutline_->data_.color = ColorConfig::skTurquoise[2];
	}
}

void PlayerDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	cbColor_->data_.texColorRate = hitActor_.ColorValue();

	if (isAttack_)
	{
		if (animationTimers_[kAttackIndex].timer.IsEnd())
		{
			Transform trfm;
			trfm.Initialize({ *pParentWorldPos_, transform_.rota_, transform_.scale_ });

			AfterimageParticle::Emit(worldKey_, trfm, YGame::ColorConfig::skTurquoise[1],
				pModels[0], pVPMan->ViewProjectionPtr(vpKey_));
			AfterimageParticle::Emit(worldKey_, trfm, YGame::ColorConfig::skTurquoise[1],
				pModels[1], pVPMan->ViewProjectionPtr(vpKey_));
			AfterimageParticle::Emit(worldKey_, trfm, YGame::ColorConfig::skTurquoise[1],
				pModels[2], pVPMan->ViewProjectionPtr(vpKey_));

			animationTimers_[kAttackIndex].timer.Reset(true);
		}
	}
	isAttack_ = false;

	CircleShadowManager::Key shadowKey1 = CircleShadowManager::Key::eWorld_0;
	CircleShadowManager::Key shadowKey2 = CircleShadowManager::Key::eWorld_1;

	CircleShadowManager::GetInstance()->ActivateCircleShadow(
		shadowKey1, YMath::VecTranslation(*pParentPosMat_) - Vector3(0, kHeight * 2.0f, 0));
	CircleShadowManager::GetInstance()->ActivateCircleShadow(
		shadowKey2, YMath::VecTranslation(*pParentPosMat_) - Vector3(0, kHeight * 2.0f, 0));
}