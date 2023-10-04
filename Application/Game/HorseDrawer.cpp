#include "HorseDrawer.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "Def.h"
#include <cmath>

using YGame::HorseDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::HorseAnimationConfig;

Model* HorseDrawer::spModel_ = nullptr;

HorseDrawer* HorseDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	HorseDrawer* newDrawer = new HorseDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void HorseDrawer::LoadResource()
{
	// モデル設定
	spModel_ = Model::LoadObj("horse", true);
}

void HorseDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";

	hitActor_.Initialize();
	slimeActor_.Initialize(0, { {} }, 0);
}

void HorseDrawer::InsertAnimationTimers()
{
	// アニメーションの数だけタイマー作成
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eIdle), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eMove), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eJump), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eLanding), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eAttack), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eHit), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eDead), AnimationTimer() });
}

void HorseDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
	// 立ち
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eIdle))
	{
	}
	// 移動
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eMove))
	{
		// 土煙を発生
		// 自分の足元
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// 正面と逆方向 かつ 上方向
		float rad = pParent_->rota_.y_;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, +0.3f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// ジャンプ
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eJump))
	{
		// ブヨブヨアニメ
		// 伸びる
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(-0.25f, +0.5f, -0.25f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();

		// 土煙を発生
		// 自分の足元
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// 正面と逆方向 かつ 下方向
		float rad = pParent_->rota_.y_;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, -1.0f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// 着地
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding))
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
			float rad = (2.0f * PI / static_cast<float>(Anime::Landing::kDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.3f, 0.0f);

			DustParticle::Emit(Anime::Landing::kDustNum, pParent_->pos_, powerDirection, spVP_);
		}
	}
	// 攻撃
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eAttack))
	{
	}
	// 被弾
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eHit))
	{
		hitActor_.Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// 死亡
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eDead))
	{
	}
}

void HorseDrawer::UpdateAnimation()
{
	hitActor_.Update();

	slimeActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	cbColor_->data_.texColorRate = hitActor_.ColorValue();
}