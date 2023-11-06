#include "HorseDrawer.h"
#include "DrawObjectForModel.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "ColorConfig.h"
#include "Def.h"
#include <cmath>

using YGame::HorseDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::HorseAnimationConfig;

namespace 
{
	// モデルポインタ
	Model* pModel = nullptr;

	// アニメーション番号
	const uint32_t kIdleIndex	 = static_cast<uint32_t>(HorseDrawer::AnimationType::eIdle);
	const uint32_t kMoveIndex	 = static_cast<uint32_t>(HorseDrawer::AnimationType::eMove);
	const uint32_t kJumpIndex	 = static_cast<uint32_t>(HorseDrawer::AnimationType::eJump);
	const uint32_t kLandingIndex = static_cast<uint32_t>(HorseDrawer::AnimationType::eLanding);
	const uint32_t kAttackIndex	 = static_cast<uint32_t>(HorseDrawer::AnimationType::eAttack);
	const uint32_t kHitIndex	 = static_cast<uint32_t>(HorseDrawer::AnimationType::eHit);
	const uint32_t kDeadIndex	 = static_cast<uint32_t>(HorseDrawer::AnimationType::eDead);
}

HorseDrawer* HorseDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	HorseDrawer* newDrawer = new HorseDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void HorseDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::LoadObj("horse", true);
}

void HorseDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skTurquoise[5];
	cbOutline_->data_.range = 0.2f;
	
	InsertConstBuffer("Body_O", cbOutline_.get());

	SetShaderTag("ModelToon");
	SetShaderTag("Body_O", "ModelOutline");

	hitActor_.Initialize();
	slimeActor_.Initialize(0, { {} }, 0);
}

void HorseDrawer::InitializeObjects()
{
	InsertObject("Body", DrawObjectForModel::Create({}, spVP_, pModel));
	InsertObject("Body_O", DrawObjectForModel::Create({}, spVP_, pModel));
}

void HorseDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex,	 AnimationTimer(Timer(HorseAnimationConfig::kIdleFrame), true));
	InsertAnimationTimer(kMoveIndex,	 AnimationTimer(Timer(HorseAnimationConfig::Move::kFrame), true));
	InsertAnimationTimer(kJumpIndex,	 AnimationTimer(Timer(HorseAnimationConfig::Jump::kFrame), false));
	InsertAnimationTimer(kLandingIndex,	 AnimationTimer(Timer(HorseAnimationConfig::Landing::kFrame), false));
	InsertAnimationTimer(kAttackIndex,	 AnimationTimer(Timer(HorseAnimationConfig::kAttackFrame), false));
	InsertAnimationTimer(kHitIndex,		 AnimationTimer(Timer(HorseAnimationConfig::Hit::kFrame), false));
	InsertAnimationTimer(kDeadIndex,	 AnimationTimer(Timer(HorseAnimationConfig::Dead::kFrame), false));
}

void HorseDrawer::GetReadyForAnimation(const uint32_t index)
{
	// 時間
	const uint32_t frame = animationTimers_[index].timer.EndFrame();

	// 立ち
	if (index & static_cast<uint32_t>(HorseDrawer::AnimationType::eIdle))
	{
	}
	// 移動
	else if (index & static_cast<uint32_t>(HorseDrawer::AnimationType::eMove))
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
	else if (index & static_cast<uint32_t>(HorseDrawer::AnimationType::eJump))
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
	else if (index & static_cast<uint32_t>(HorseDrawer::AnimationType::eLanding))
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
	// 攻撃
	else if (index & static_cast<uint32_t>(HorseDrawer::AnimationType::eAttack))
	{
	}
	// 被弾
	else if (index & static_cast<uint32_t>(HorseDrawer::AnimationType::eHit))
	{
		hitActor_.Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// 死亡
	else if (index & static_cast<uint32_t>(HorseDrawer::AnimationType::eDead))
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