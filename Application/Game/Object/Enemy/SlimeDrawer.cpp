#include "SlimeDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

#include "WorldManager.h"
#include "CircleShadowManager.h"
#include "ColorConfig.h"

#include "DustParticle.h"
#include "DebriParticle.h"
#include "DamageParticle.h"
#include "WaveParticle.h"

#include "Def.h"
#include "MathVector.h"
#include <cmath>

using YGame::SlimeDrawer;
using YGame::Model;
using YGame::ViewProjectionManager;
using YMath::Vector3;
using YMath::Timer;
using AnimeTimer = YGame::BaseDrawer::AnimationTimer;
namespace Color = YGame::ColorConfig;

namespace 
{
	// モデルポインタ
	Model* pModel = nullptr;
	
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();

	// アニメーション番号
	const uint32_t kIdleIndex	 = static_cast<uint32_t>(SlimeDrawer::AnimationType::eIdle);
	const uint32_t kLandingIndex = static_cast<uint32_t>(SlimeDrawer::AnimationType::eLanding);
	const uint32_t kHitIndex	 = static_cast<uint32_t>(SlimeDrawer::AnimationType::eHit);
	const uint32_t kDeadIndex	 = static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead);
	const uint32_t kFeverIndex	 = static_cast<uint32_t>(SlimeDrawer::AnimationType::eFever);
	const uint32_t kCircleShadowIndex = static_cast<uint32_t>(SlimeDrawer::AnimationType::eCircleShadow);

	// アニメーションタイマー
	const AnimeTimer kIdleTimer		 = { Timer(60), true };
	const AnimeTimer kLandingTimer	 = { Timer(20), false };
	const AnimeTimer kHitTimer		 = { Timer(20), false };
	const AnimeTimer kDeadTimer		 = { Timer(20), false };
	const AnimeTimer kFeverTimer	 = { Timer(280), true };
	const AnimeTimer kCircleShadowTimer = { Timer(1), true };

	// アニメーション値
	const std::vector<Vector3> kLandingWobbleScaleValues =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(+0.5f, -0.25f, +0.5f),
		Vector3(0.0f, 0.0f, 0.0f),
	};

	const std::vector<Vector3> kHitWobbleScaleValues =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(+0.75f, -0.5f, +0.75f),
		Vector3(0.0f, 0.0f, 0.0f),
	};

	const float kExponent = 3.0f;

	const float kHeight = 0.5f;

	const float kHitSwing = 0.2f;
	const float kHitPlace = 100.0f;

	// 色
	const YMath::Vector4 kBodyColor = YMath::GetColor(245, 24, 83, 255);
	const YMath::Vector4 kOutlineColor = YMath::GetColor(143, 13, 48, 255);

	// パーティクル
	const size_t kLandingDirectionNum = 4;
	const size_t kLandingDustNum = 2;

	const size_t kDeadDebriNum = 16;
}

std::unique_ptr<SlimeDrawer> SlimeDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<SlimeDrawer> newDrawer = std::make_unique<SlimeDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void SlimeDrawer::LoadResource()
{
	pModel = Model::LoadObj("slime", true);
}

void SlimeDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	cbColor_->data_.baseColor = kBodyColor;

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = kOutlineColor;
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Body", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Body_O", cbOutline_.get());

	SetShaderTag("ModelToon");
	SetShaderTag("Body_O", "ModelOutline");

	std::vector<YMath::Vector4> rainbow(std::begin(Color::skRainbow), std::end(Color::skRainbow));
	rainbowEas_.Initialize(rainbow, 1.0f);

	hitActor_.Initialize();
	slimeActor_.Initialize(0, { {} }, 0);
}

void SlimeDrawer::InitializeObjects()
{
	InsertObject("Body", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Body_O", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void SlimeDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, kIdleTimer);
	InsertAnimationTimer(kLandingIndex, kLandingTimer);
	InsertAnimationTimer(kHitIndex, kHitTimer);
	InsertAnimationTimer(kDeadIndex, kDeadTimer);
	InsertAnimationTimer(kFeverIndex, kFeverTimer);
	InsertAnimationTimer(kCircleShadowIndex, kCircleShadowTimer);
}

void SlimeDrawer::GetReadyForAnimation(const uint32_t index)
{
	// 時間
	const uint32_t frame = animationTimers_[index].timer.EndFrame();

	// 立ち
	if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eIdle))
	{
	}
	// 着地
	else if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eLanding))
	{
		if (slimeActor_.IsAct() == false)
		{
			// ブヨブヨアニメ (潰れる)
			slimeActor_.Initialize(frame, kLandingWobbleScaleValues, kExponent);
			slimeActor_.Wobble();
		}

		// 自分の足元に土煙を発生
		Vector3 pos = *pParentWorldPos_ - Vector3(0.0f, kHeight, 0.0f);

		// 自分の周囲 かつ 上方向
		for (size_t i = 0; i < kLandingDirectionNum; i++)
		{
			// 角度 = 2π (360) / 向きの数 * index
			float rad = (2.0f * kPI / static_cast<float>(kLandingDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.3f, 0.0f);

			//DustParticle::Emit(kLandingDustNum, pos, powerDirection, pVPMan->ViewProjectionPtr(vpKey_));
		}
	}
	// 被弾
	else if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eHit))
	{
		// ブヨブヨアニメ (潰れる)
		slimeActor_.Initialize(frame, kHitWobbleScaleValues, kExponent);
		slimeActor_.Wobble();
		
		hitActor_.Hit(kHitSwing, kHitSwing / static_cast<float>(frame), kHitPlace);
	}
	// 死亡
	else if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead))
	{
		DebriParticle::Emit(kDeadDebriNum, *pParentWorldPos_, pVPMan->ViewProjectionPtr(vpKey_));
	}
}

void SlimeDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);
	animeStatus_.pos_.y += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut).y;

	if (IsActAnimation(kFeverIndex))
	{
		cbColor_->data_.baseColor = rainbowEas_.In(animationTimers_[kFeverIndex].timer.Ratio());
		cbOutline_->data_.color = Color::skYellow;
	}
	else
	{
		cbColor_->data_.baseColor = kBodyColor;
		cbOutline_->data_.color = kOutlineColor;
		
		cbColor_->data_.texColorRate = hitActor_.ColorValue();
	}

	if (IsActAnimation(kCircleShadowIndex))
	{
		CircleShadowManager::Key shadowKey1 = CircleShadowManager::Key::eWorld_0;
		CircleShadowManager::Key shadowKey2 = CircleShadowManager::Key::eWorld_1;

		CircleShadowManager::GetInstance()->ActivateCircleShadow(
			shadowKey1, YMath::VecTranslation(*pParentPosMat_) - Vector3(0, 1.0f, 0));
		CircleShadowManager::GetInstance()->ActivateCircleShadow(
			shadowKey2, YMath::VecTranslation(*pParentPosMat_) - Vector3(0, 1.0f, 0));
	}
}

void SlimeDrawer::PlayHitAnimation(const uint32_t damage)
{
	PlayAnimation(static_cast<uint32_t>(AnimationType::eHit), true);

	DamageParticle::Emit(damage, *pParentWorldPos_, pVPMan->ViewProjectionPtr(vpKey_));

	Vector3 pos = *pParentWorldPos_;
	pos.y += pParent_->scale_.y;
	WaveParticle::Emit(30, pos, { kPI / 2.0f,0,0 }, 10.0f, ColorConfig::skYellow, pVPMan->ViewProjectionPtr(vpKey_));
}