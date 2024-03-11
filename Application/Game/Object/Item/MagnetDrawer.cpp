#include "MagnetDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

#include "WorldManager.h"
#include "CircleShadowManager.h"
#include "ColorConfig.h"

#include "WaveParticle.h"

#include "Lerp.h"
#include "Def.h"

using YGame::MagnetDrawer;
using YGame::Model;
using YMath::Timer;
using YMath::Vector3;
using YMath::Vector4;
using YGame::ViewProjectionManager;
using AnimeTimer = YGame::BaseDrawer::AnimationTimer;

namespace
{
	// モデルポインタ
	Model* pModel = nullptr;

	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();

	// アニメーション番号
	const uint32_t kIdleIndex = static_cast<uint32_t>(MagnetDrawer::AnimationType::eIdle);
	const uint32_t kEarnIndex = static_cast<uint32_t>(MagnetDrawer::AnimationType::eEarn);
	const uint32_t kSuctionIndex = static_cast<uint32_t>(MagnetDrawer::AnimationType::eSuction);
	const uint32_t kDeadIndex = static_cast<uint32_t>(MagnetDrawer::AnimationType::eDead);
	const uint32_t kCircleShadowIndex = static_cast<uint32_t>(MagnetDrawer::AnimationType::eCircleShadow);

	// アニメーションタイマー
	const AnimeTimer kIdleTimer = { Timer(120), true };
	const AnimeTimer kEarnTimer = { Timer(30), false };
	const AnimeTimer kSuctionTimer = { Timer(30), true };
	const AnimeTimer kDeadTimer = { Timer(30), false };
	const AnimeTimer kCircleShadowTimer = { Timer(1), true };

	// アニメーション値
	const std::vector<Vector3> kEarnWobbleScaleValues =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(-0.5f, +1.0f, -0.5f),
		Vector3(0.0f, 0.0f, 0.0f),
	};

	const float kExponent = 3.0f;
}

std::unique_ptr<MagnetDrawer> MagnetDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<MagnetDrawer> newDrawer = std::make_unique<MagnetDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void MagnetDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::LoadObj("magnet", true);
}

void MagnetDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skYellow;
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Magnet", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_1));
	InsertConstBuffer("Magnet_O", cbOutline_.get());

	SetShaderTag("ModelToon");
	SetShaderTag("Magnet_O", "ModelOutline");

	// 立ちアニメーション用
	idlePosEas_.Initialize({ 0.0f, +0.1f, 0.0f, -0.1f, 0.0f }, 1.0f);
	idleRotaEas_.Initialize({ 0.0f, +kPI / 4.0f, 0.0f, -kPI / 4.0f, 0.0f }, 1.0f);

	// 獲得アニメーション用
	earnPosEas_.Initialize(0.0f, +5.0f, 3.0f);
	earnRotaEas_.Initialize(0.0f, +kPI * 6.0f, 3.0f);
	
	isEarn_ = false;

	emitTimer_.Initialize(0);
	emitCounter_ = 0;

	slimeActor_.Initialize(0, { {} }, 0);
}

void MagnetDrawer::InitializeObjects()
{
	InsertObject("Magnet", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Magnet_O", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void MagnetDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, kIdleTimer);
	InsertAnimationTimer(kEarnIndex, kEarnTimer);
	InsertAnimationTimer(kSuctionIndex, kSuctionTimer);
	InsertAnimationTimer(kDeadIndex, kDeadTimer);
	InsertAnimationTimer(kCircleShadowIndex, kCircleShadowTimer);
}

void MagnetDrawer::GetReadyForAnimation(const uint32_t index)
{
	if (index & static_cast<uint32_t>(AnimationType::eIdle))
	{

	}
	else if (index & static_cast<uint32_t>(AnimationType::eEarn))
	{
		// ブヨブヨアニメ
		uint32_t wobbleFrame = animationTimers_[index].timer.EndFrame();

		slimeActor_.Initialize(wobbleFrame, kEarnWobbleScaleValues, kExponent);
		slimeActor_.Wobble();

		emitTimer_.Initialize(20, true);
		emitCounter_ = 0;

		isEarn_ = true;
	}
}

void MagnetDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	animeStatus_.pos_.y += idlePosEas_.In(animationTimers_[kIdleIndex].timer.Ratio());
	animeStatus_.rota_.y += idleRotaEas_.In(animationTimers_[kIdleIndex].timer.Ratio());

	animeStatus_.pos_.y += earnPosEas_.Out(animationTimers_[kEarnIndex].timer.Ratio());
	animeStatus_.rota_.y += earnRotaEas_.In(animationTimers_[kEarnIndex].timer.Ratio());

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eIn);

	emitTimer_.Update();
	if (emitTimer_.IsEnd())
	{
		WaveParticle::Emit(
			20,
			*pParentWorldPos_ + Vector3(0.0f, earnPosEas_.End(), 0.0f), {}, 5.0f,
			ColorConfig::skTurquoise[2], pVPMan->ViewProjectionPtr(vpKey_));
		
		emitCounter_++;
		
		emitTimer_.Initialize(10, (emitCounter_ < 2));
	}

	if (isEarn_ == false)
	{
		if (IsActAnimation(kCircleShadowIndex))
		{
			CircleShadowManager::Key shadowKey = CircleShadowManager::Key::eWorld_0;
			CircleShadowManager::GetInstance()->ActivateCircleShadow(shadowKey, pParent_->pos_ - Vector3(0, 1.0f, 0));
		}
	}

}