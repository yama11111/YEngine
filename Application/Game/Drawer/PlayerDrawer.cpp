#include "PlayerDrawer.h"
#include "DrawObjectForModel.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "DebriParticle.h"
#include "ColorConfig.h"
#include "Def.h"
#include <cmath>

using YGame::PlayerDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::PlayerAnimationConfig;

namespace
{
	// モデルポインタ
	std::array<Model*, 3> pModels{};
	
	// アニメーション番号
	const uint32_t kIdleIndex	 = static_cast<uint32_t>(PlayerDrawer::AnimationType::eIdle);
	const uint32_t kMoveIndex	 = static_cast<uint32_t>(PlayerDrawer::AnimationType::eMove);
	const uint32_t kJumpIndex	 = static_cast<uint32_t>(PlayerDrawer::AnimationType::eJump);
	const uint32_t kLandingIndex = static_cast<uint32_t>(PlayerDrawer::AnimationType::eLanding);
	const uint32_t kAttackIndex	 = static_cast<uint32_t>(PlayerDrawer::AnimationType::eAttack);
	const uint32_t kHitIndex	 = static_cast<uint32_t>(PlayerDrawer::AnimationType::eHit);
	const uint32_t kDeadIndex	 = static_cast<uint32_t>(PlayerDrawer::AnimationType::eDead);
}

PlayerDrawer* PlayerDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	PlayerDrawer* newDrawer = new PlayerDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void PlayerDrawer::LoadResource()
{
	// モデル設定
	pModels[1] = Model::LoadObj("player/body", true);
	pModels[0] = Model::LoadObj("player/leg_L", true);
	pModels[2] = Model::LoadObj("player/leg_R", true);
}

void PlayerDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelToon");

	slimeActor_.Initialize(0, { {} }, 0);
	hitActor_.Initialize();
}

void PlayerDrawer::InitializeObjects()
{
	InsertObject("Body",	 DrawObjectForModel::Create({}, spVP_, pModels[0]));
	InsertObject("Leg_L",	 DrawObjectForModel::Create({}, spVP_, pModels[1]));
	InsertObject("Leg_R",	 DrawObjectForModel::Create({}, spVP_, pModels[2]));
}

void PlayerDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex,	 AnimationTimer(Timer(PlayerAnimationConfig::kIdleFrame), true));
	InsertAnimationTimer(kMoveIndex,	 AnimationTimer(Timer(PlayerAnimationConfig::Move::kFrame), true));
	InsertAnimationTimer(kJumpIndex,	 AnimationTimer(Timer(PlayerAnimationConfig::Jump::kFrame), false));
	InsertAnimationTimer(kLandingIndex,	 AnimationTimer(Timer(PlayerAnimationConfig::Landing::kFrame), false));
	InsertAnimationTimer(kAttackIndex,	 AnimationTimer(Timer(PlayerAnimationConfig::kAttackFrame), false));
	InsertAnimationTimer(kHitIndex,		 AnimationTimer(Timer(PlayerAnimationConfig::Hit::kFrame), false));
	InsertAnimationTimer(kDeadIndex,	 AnimationTimer(Timer(PlayerAnimationConfig::Dead::kFrame), false));
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
		float rad = pParent_->rota_.y_;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, +0.1f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// ジャンプ
	else if (index & static_cast<uint32_t>(AnimationType::eJump))
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
		Vector3 powerDirection = -front + Vector3(0.0f, -0.5f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// 着地
	else if (index & static_cast<uint32_t>(AnimationType::eLanding))
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

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.1f, 0.0f);

			DustParticle::Emit(Anime::Landing::kDustNum, pParent_->pos_, powerDirection, spVP_);
		}
	}
	// 攻撃
	else if (index & static_cast<uint32_t>(AnimationType::eAttack))
	{
	}
	// 被弾
	else if (index & static_cast<uint32_t>(AnimationType::eHit))
	{
		hitActor_.Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// 死亡
	else if (index & static_cast<uint32_t>(AnimationType::eDead))
	{
		DebriParticle::Emit(Anime::Dead::kDebriNum, pParent_->pos_, spVP_);
	}
}

void PlayerDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);
	
	cbColor_->data_.texColorRate = hitActor_.ColorValue();

	//Transform::Status status = animeStatus_;
	//outlineObj_->Update(status);
}