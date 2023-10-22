#include "SlimeDrawer.h"
#include "DrawObjectForModel.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "DebriParticle.h"
#include "Def.h"
#include <cmath>

#include "DamageEmitter.h"

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

SlimeDrawer* SlimeDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	SlimeDrawer* newDrawer = new SlimeDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SlimeDrawer::LoadResource()
{
	pModel = Model::LoadObj("slime", true);
}

void SlimeDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelToon");

	hitActor_.Initialize();
	slimeActor_.Initialize(0, { {} }, 0);
}

void SlimeDrawer::InitializeObjects()
{
	InsertObject("Body", DrawObjectForModel::Create({}, spVP_, pModel));
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
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// 自分の周囲 かつ 上方向
		for (size_t i = 0; i < Anime::Landing::kDirectionNum; i++)
		{
			// 角度 = 2π (360) / 向きの数 * index
			float rad = (2.0f * kPI / static_cast<float>(Anime::Landing::kDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.3f, 0.0f);

			DustParticle::Emit(Anime::Landing::kDustNum, pParent_->pos_, powerDirection, spVP_);
		}
	}
	// 被弾
	else if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eHit))
	{
		hitActor_.Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);

		DamageEmitter::Emit(pParent_->pos_, 100);
	}
	// 死亡
	else if (index & static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead))
	{
		DebriParticle::Emit(Anime::Dead::kDebriNum, pParent_->pos_, spVP_);
	}
}

void SlimeDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	cbColor_->data_.texColorRate = hitActor_.ColorValue();
}