#include "PlayerDrawer.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "DebriParticle.h"
#include <cmath>
#include "Def.h"

using YGame::PlayerDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::PlayerAnimationConfig;

Model* PlayerDrawer::spModel_ = nullptr;

PlayerDrawer* PlayerDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	PlayerDrawer* newDrawer = new PlayerDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void PlayerDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("player.png")} });
}

void PlayerDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";

	HitActor::Initialize();
	SlimeActor::Initialize();
}

void PlayerDrawer::InsertAnimationTimers()
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

void PlayerDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
	// 立ち
	if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eIdle))
	{
	}
	// 移動
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eMove))
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
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eJump))
	{
		// ブヨブヨアニメ
		// 伸びる
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(-0.25f, +0.5f, -0.25f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);

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
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eLanding))
	{
		// ブヨブヨアニメ
		// 潰れる
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.5f, -0.25f, +0.5f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);

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

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.1f, 0.0f);

			DustParticle::Emit(Anime::Landing::kDustNum, pParent_->pos_, powerDirection, spVP_);
		}
	}
	// 攻撃
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eAttack))
	{
	}
	// 被弾
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eHit))
	{
		HitActor::Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// 死亡
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eDead))
	{
		DebriParticle::Emit(Anime::Dead::kDebriNum, pParent_->pos_, spVP_);
	}
}

void PlayerDrawer::UpdateAnimtion()
{
	HitActor::Update();

	SlimeActor::Update();

	animeStatus_.pos_ += HitActor::ShakePosValue();

	animeStatus_.scale_ += SlimeActor::WobbleScaleValue();
	
	cbColor_->data_.texColorRate = HitActor::ColorValue();
}