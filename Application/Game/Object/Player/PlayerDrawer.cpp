#include "PlayerDrawer.h"
#include "DrawObjectForModel.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "DebriParticle.h"
#include "ColorConfig.h"
#include "Def.h"
#include <cmath>

#include "CircleShadowManager.h"

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

std::unique_ptr<PlayerDrawer> PlayerDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	std::unique_ptr<PlayerDrawer> newDrawer = std::make_unique<PlayerDrawer>();

	newDrawer->Initialize(pParent, drawPriority);

	return std::move(newDrawer);
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

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skTurquoise[5];
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Body", CircleShadowManager::GetInstance()->CBPtr(0));
	InsertConstBuffer("Leg_L", CircleShadowManager::GetInstance()->CBPtr(0));
	InsertConstBuffer("Leg_R", CircleShadowManager::GetInstance()->CBPtr(0));
	
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
	InsertObject("Body",	 DrawObjectForModel::Create({}, spVP_, pModels[0]));
	InsertObject("Leg_L",	 DrawObjectForModel::Create({}, spVP_, pModels[1]));
	InsertObject("Leg_R",	 DrawObjectForModel::Create({}, spVP_, pModels[2]));

	InsertObject("Body_O",	 DrawObjectForModel::Create({}, spVP_, pModels[0]));
	InsertObject("Leg_L_O",	 DrawObjectForModel::Create({}, spVP_, pModels[1]));
	InsertObject("Leg_R_O",	 DrawObjectForModel::Create({}, spVP_, pModels[2]));
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
		float rad = pParent_->rota_.y;
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
		wobbleScaleValues.push_back(Vector3(-0.5f, +1.0f, -0.5f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();

		// 土煙を発生
		// 自分の足元
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// 正面と逆方向 かつ 下方向
		float rad = pParent_->rota_.y;
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

	CircleShadowManager::GetInstance()->ActivateCircleShadow(0, pParent_->pos_ - Vector3(0, 1.0f, 0));
	CircleShadowManager::GetInstance()->ActivateCircleShadow(1, pParent_->pos_ - Vector3(0, 1.0f, 0));
}