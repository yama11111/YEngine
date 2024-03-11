#include "PlayerDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

#include "WorldManager.h"
#include "CircleShadowManager.h"
#include "ColorConfig.h"

#include "DustParticle.h"
#include "DebriParticle.h"

#include "Def.h"
#include <cmath>

using YGame::PlayerDrawer;
using YGame::Model;
using YGame::ViewProjectionManager;
using YMath::Vector3;
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

	// アニメーションタイマー
	const AnimeTimer kIdleTimer		 = { Timer(60), true };
	const AnimeTimer kMoveTimer		 = { Timer( 8), true };
	const AnimeTimer kJumpTimer		 = { Timer(20), false };
	const AnimeTimer kLandingTimer	 = { Timer(20), false };
	const AnimeTimer kAttackTimer	 = { Timer(10), false };
	const AnimeTimer kHitTimer		 = { Timer( 4), false };
	const AnimeTimer kDeadTimer		 = { Timer(10), false };
	const AnimeTimer kCircleShadowTimer	 = { Timer( 1), true };

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

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skTurquoise[5];
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Body", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Leg_L", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Leg_R", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	
	InsertConstBuffer("Body_O", cbOutline_.get());
	InsertConstBuffer("Leg_L_O", cbOutline_.get());
	InsertConstBuffer("Leg_R_O", cbOutline_.get());

	SetShaderTag("ModelToon");
	
	SetShaderTag("Body_O", "ModelOutline");
	SetShaderTag("Leg_L_O", "ModelOutline");
	SetShaderTag("Leg_R_O", "ModelOutline");
	
	slimeActor_.Initialize(0, { {} }, 0);
	hitActor_.Initialize();
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
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// 正面と逆方向 かつ 上方向
		float rad = pParent_->rota_.y;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, +0.1f, 0.0f);

		DustParticle::Emit(kMoveDustNum, *pParentWorldPos_, powerDirection, pVPMan->ViewProjectionPtr(vpKey_));
	}
	// ジャンプ
	else if (index & static_cast<uint32_t>(AnimationType::eJump))
	{
		// ブヨブヨアニメ (伸びる)
		slimeActor_.Initialize(frame, kJumpWobbleScaleValues, kExponent);
		slimeActor_.Wobble();

		// 自分の足元に土煙を発生
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, kHeight, 0.0f);

		// 正面と逆方向 かつ 下方向
		float rad = pParent_->rota_.y;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, -0.5f, 0.0f);

		DustParticle::Emit(kJumpDustNum, *pParentWorldPos_, powerDirection, pVPMan->ViewProjectionPtr(vpKey_));
	}
	// 着地
	else if (index & static_cast<uint32_t>(AnimationType::eLanding))
	{
		// ブヨブヨアニメ (潰れる)
		slimeActor_.Initialize(frame, kLandingWobbleScaleValues, kExponent);
		slimeActor_.Wobble();

		// 自分の足元に土煙を発生
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, kHeight, 0.0f);

		// 自分の周囲 かつ 上方向
		for (size_t i = 0; i < kLandingDirectionNum; i++)
		{
			// 角度 = 2π (360) / 向きの数 * index
			float rad = (2.0f * kPI / static_cast<float>(kLandingDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.1f, 0.0f);

			DustParticle::Emit(kLandingDustNum, *pParentWorldPos_, powerDirection, pVPMan->ViewProjectionPtr(vpKey_));
		}
	}
	// 攻撃
	else if (index & static_cast<uint32_t>(AnimationType::eAttack))
	{
	}
	// 被弾
	else if (index & static_cast<uint32_t>(AnimationType::eHit))
	{
		hitActor_.Hit(kHitSwing, kHitSwing / static_cast<float>(frame), kHitPlace);
	}
	// 死亡
	else if (index & static_cast<uint32_t>(AnimationType::eDead))
	{
		DebriParticle::Emit(kDeadDebriNum, *pParentWorldPos_, pVPMan->ViewProjectionPtr(vpKey_));
	}
}

void PlayerDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	cbColor_->data_.texColorRate = hitActor_.ColorValue();

	CircleShadowManager::Key shadowKey1 = CircleShadowManager::Key::eWorld_0;
	CircleShadowManager::Key shadowKey2 = CircleShadowManager::Key::eWorld_1;

	CircleShadowManager::GetInstance()->ActivateCircleShadow(shadowKey1, pParent_->pos_ - Vector3(0, kHeight, 0));
	CircleShadowManager::GetInstance()->ActivateCircleShadow(shadowKey2, pParent_->pos_ - Vector3(0, kHeight, 0));
}