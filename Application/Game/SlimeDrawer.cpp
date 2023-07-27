#include "SlimeDrawer.h"
#include "AnimationConfig.h"

using YGame::SlimeDrawer;
using YGame::Model;
using YMath::Vector3;

Model* SlimeDrawer::spModel_ = nullptr;

void SlimeDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";

	HitActor::Initialize();
	SlimeActor::Initialize();
}

void SlimeDrawer::Update()
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

void SlimeDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SlimeDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{
	// 立ち
	if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eIdle))
	{
		IdleTimer_.Initialize(frame);
		IdleTimer_.SetActive(true);

	}
	// ジャンプ
	if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eJump))
	{
		JumpTimer_.Initialize(frame);
		JumpTimer_.SetActive(true);

		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(-0.25f, +0.5f, -0.25f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);
	}
	// 着地
	if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eLanding))
	{
		LandingTimer_.Initialize(frame);
		LandingTimer_.SetActive(true);

		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.5f, -0.25f, +0.5f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);
	}
	// 被弾
	if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eHit))
	{
		HitTimer_.Initialize(frame);
		HitTimer_.SetActive(true);

		HitActor::Hit(
			PlayerAnimationConfig::Hit::kSwing,
			PlayerAnimationConfig::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// 死亡
	if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eDead))
	{
		DeadTimer_.Initialize(frame);
		DeadTimer_.SetActive(true);
	}

	// ビットフラグ変更
	animationBitFlag_ |= index;
}

SlimeDrawer::SlimeDrawer(const uint16_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

SlimeDrawer::SlimeDrawer(Transform* pParent, const uint16_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void SlimeDrawer::StaticInitialize()
{
	spModel_ = Model::LoadObj("slime", true);
}

void SlimeDrawer::TimerUpdate()
{
	IdleTimer_.Update();

	if (IdleTimer_.IsEnd())
	{
		IdleTimer_.Reset(true);

		//animationBitFlag_ &= ~static_cast<uint16_t>(SlimeDrawer::AnimationType::eIdle);
	}


	JumpTimer_.Update();

	if (JumpTimer_.IsEnd())
	{
		JumpTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(SlimeDrawer::AnimationType::eJump);
	}


	LandingTimer_.Update();

	if (LandingTimer_.IsEnd())
	{
		LandingTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(SlimeDrawer::AnimationType::eLanding);
	}

	HitTimer_.Update();

	if (HitTimer_.IsEnd())
	{
		HitTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(SlimeDrawer::AnimationType::eHit);
	}


	DeadTimer_.Update();

	if (DeadTimer_.IsEnd())
	{
		DeadTimer_.Initialize(0);

		animationBitFlag_ &= ~static_cast<uint16_t>(SlimeDrawer::AnimationType::eDead);
	}
}

void SlimeDrawer::AnimationUpdate()
{
	TimerUpdate();

}
