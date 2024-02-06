#include "SlimeDrawer.h"
#include "DrawObjectForModel.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "DebriParticle.h"
#include "ColorConfig.h"
#include "Def.h"
#include <cmath>

#include "CircleShadowManager.h"

#include "DamageParticle.h"
#include "WaveParticle.h"

using YGame::SlimeDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::SlimeAnimationConfig;

namespace 
{
	// モデルポインタ
	Model* pModel = nullptr;

	// アニメーション番号
	const uint32_t kIdleIndex	 = static_cast<uint32_t>(SlimeDrawer::AnimationType::eIdle);
	const uint32_t kLandingIndex = static_cast<uint32_t>(SlimeDrawer::AnimationType::eLanding);
	const uint32_t kHitIndex	 = static_cast<uint32_t>(SlimeDrawer::AnimationType::eHit);
	const uint32_t kDeadIndex	 = static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead);
}

std::unique_ptr<SlimeDrawer> SlimeDrawer::Create(
	Transform* pParent, YMath::Vector3* pParentWorldPos, const size_t drawPriority)
{
	std::unique_ptr<SlimeDrawer> newDrawer = std::make_unique<SlimeDrawer>();

	newDrawer->Initialize(pParent, pParentWorldPos, drawPriority);

	return std::move(newDrawer);
}

void SlimeDrawer::LoadResource()
{
	pModel = Model::LoadObj("slime", true);
}

void SlimeDrawer::Initialize(Transform* pParent, YMath::Vector3* pParentWorldPos, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, pParentWorldPos, drawPriority);


	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = YMath::GetColor(143, 13, 48, 255);
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Body", CircleShadowManager::GetInstance()->CBPtr(0));
	InsertConstBuffer("Body_O", cbOutline_.get());

	SetShaderTag("ModelToon");
	SetShaderTag("Body_O", "ModelOutline");

	hitActor_.Initialize();
	slimeActor_.Initialize(0, { {} }, 0);
}

void SlimeDrawer::InitializeObjects()
{
	InsertObject("Body", DrawObjectForModel::Create({}, spVP_, pModel));
	InsertObject("Body_O", DrawObjectForModel::Create({}, spVP_, pModel));
}

void SlimeDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex,	 AnimationTimer(Timer(SlimeAnimationConfig::kIdleFrame), true));
	InsertAnimationTimer(kLandingIndex,	 AnimationTimer(Timer(SlimeAnimationConfig::Landing::kFrame), false));
	InsertAnimationTimer(kHitIndex,		 AnimationTimer(Timer(SlimeAnimationConfig::Hit::kFrame), false));
	InsertAnimationTimer(kDeadIndex,	 AnimationTimer(Timer(SlimeAnimationConfig::Dead::kFrame), false));
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
		// ブヨブヨアニメ
		// 潰れる
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.5f, -0.25f, +0.5f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();

		// 土煙を発生
		// 自分の足元
		float height = 0.5f;
		Vector3 pos = *pParentWorldPos_ - Vector3(0.0f, height, 0.0f);

		// 自分の周囲 かつ 上方向
		for (size_t i = 0; i < Anime::Landing::kDirectionNum; i++)
		{
			// 角度 = 2π (360) / 向きの数 * index
			float rad = (2.0f * kPI / static_cast<float>(Anime::Landing::kDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.3f, 0.0f);

			DustParticle::Emit(Anime::Landing::kDustNum, *pParentWorldPos_, powerDirection, spVP_);
		}
	}
	// 被弾
	else if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eHit))
	{
		hitActor_.Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// 死亡
	else if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead))
	{
		DebriParticle::Emit(Anime::Dead::kDebriNum, *pParentWorldPos_, spVP_);
	}
}

void SlimeDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	cbColor_->data_.texColorRate = hitActor_.ColorValue();

	CircleShadowManager::GetInstance()->ActivateCircleShadow(0, pParent_->pos_ - Vector3(0, 1.0f, 0));
	CircleShadowManager::GetInstance()->ActivateCircleShadow(1, pParent_->pos_ - Vector3(0, 1.0f, 0));
}

void SlimeDrawer::PlayHitAnimation(const uint32_t damage, const bool isStepOn)
{
	PlayAnimation(static_cast<uint32_t>(AnimationType::eHit), true);

	DamageParticle::Emit(damage, *pParentWorldPos_, spVP_);

	if (isStepOn)
	{
		// ブヨブヨアニメ
		// 潰れる
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.5f, -0.25f, +0.5f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = animationTimers_[kHitIndex].timer.EndFrame();;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();

		Vector3 pos = *pParentWorldPos_;
		pos.y += pParent_->scale_.y;

		WaveParticle::Emit(30, pos, { kPI / 2.0f,0,0 }, 10.0f, ColorConfig::skYellow, spVP_);
	}
}