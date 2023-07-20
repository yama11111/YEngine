#include "HorseDrawer.h"
#include "AnimationConfig.h"

using YGame::HorseDrawer;
using YGame::Model;
using YMath::Vector3;

Model* HorseDrawer::spModel_ = nullptr;

void HorseDrawer::Initialize(Transform* pParent, const uint32_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetGraphic(spModel_);

	shaderKey_ = "ModelToon";

	HitActor::Initialize();
	SlimeActor::Initialize();
}

void HorseDrawer::Update()
{
	animeStatus_ = {};

	AnimationUpdate();

	HitActor::Update();

	SlimeActor::Update();

	animeStatus_.pos_ += HitActor::ShakePosValue();

	animeStatus_.scale_ += SlimeActor::WobbleScaleValue();

	// オブジェクトに適応
	BaseDrawer::Update();

	cbColor_->data_.texColorRate = HitActor::ColorValue();

	VisibleUpdate();
}

void HorseDrawer::Draw()
{
	BaseDrawer::Draw();
}

void HorseDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{
	// 立ち
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eIdle))
	{
		IdleTimer_.Initialize(frame);
		IdleTimer_.SetActive(true);

	}
	// ジャンプ
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eJump))
	{
		JumpTimer_.Initialize(frame);
		JumpTimer_.SetActive(true);

		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(-0.25f, +0.25f, -0.25f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);
	}
	// 着地
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding))
	{
		LandingTimer_.Initialize(frame);
		LandingTimer_.SetActive(true);

		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.25f, -0.25f, +0.25f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);
	}
	// 攻撃
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eAttack))
	{
		AttackTimer_.Initialize(frame);
		AttackTimer_.SetActive(true);
	}
	// 被弾
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eHit))
	{
		HitTimer_.Initialize(frame);
		HitTimer_.SetActive(true);

		HitActor::Hit(
			HorseAnimationConfig::Hit::kSwing,
			HorseAnimationConfig::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// 死亡
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eDead))
	{
		DeadTimer_.Initialize(frame);
		DeadTimer_.SetActive(true);
	}

	// ビットフラグ変更
	animationBitFlag_ |= index;
}

HorseDrawer::HorseDrawer(const uint32_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

HorseDrawer::HorseDrawer(Transform* pParent, const uint32_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void HorseDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::LoadObj("horse", true);
}

void HorseDrawer::TimerUpdate()
{
	IdleTimer_.Update();

	if (IdleTimer_.IsEnd())
	{
		IdleTimer_.Reset(true);

		//animationBitFlag_ &= ~static_cast<uint16_t>(HorseDrawer::AnimationType::eIdle);
	}


	JumpTimer_.Update();

	if (JumpTimer_.IsEnd())
	{
		JumpTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(HorseDrawer::AnimationType::eJump);
	}


	LandingTimer_.Update();

	if (LandingTimer_.IsEnd())
	{
		LandingTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding);
	}


	AttackTimer_.Update();

	if (AttackTimer_.IsEnd())
	{
		AttackTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(HorseDrawer::AnimationType::eAttack);
	}


	HitTimer_.Update();

	if (HitTimer_.IsEnd())
	{
		HitTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(HorseDrawer::AnimationType::eHit);
	}


	DeadTimer_.Update();

	if (DeadTimer_.IsEnd())
	{
		DeadTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(HorseDrawer::AnimationType::eDead);
	}
}

void HorseDrawer::AnimationUpdate()
{
	TimerUpdate();

}
