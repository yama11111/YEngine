#include "LifeDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"
#include "ColorConfig.h"
#include "Lerp.h"
#include "Def.h"

#include "CircleShadowManager.h"

#include "WaveParticle.h"
#include "RecoveryParticle.h"

using YGame::LifeDrawer;
using YGame::Model;
using YMath::Timer;
using YMath::Vector3;
using YMath::Vector4;
using YGame::ViewProjectionManager;

namespace
{
	// モデルポインタ
	Model* pModel = nullptr;
	
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();

	// アニメーション番号
	const uint32_t kIdleIndex = static_cast<uint32_t>(LifeDrawer::AnimationType::eIdle);
	const uint32_t kEarnIndex = static_cast<uint32_t>(LifeDrawer::AnimationType::eEarn);
}

std::unique_ptr<LifeDrawer> LifeDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<LifeDrawer> newDrawer = std::make_unique<LifeDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void LifeDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::LoadObj("life", true);
}

void LifeDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);


	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skYellow;
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Life", CircleShadowManager::GetInstance()->CBPtr(1));
	InsertConstBuffer("Life_O", cbOutline_.get());

	SetShaderTag("ModelToon");
	SetShaderTag("Life_O", "ModelOutline");

	// 立ちアニメーション用
	idlePosEas_.Initialize({ 0.0f, +0.1f, 0.0f, -0.1f, 0.0f }, 1.0f);

	// 獲得アニメーション用
	earnPosEas_.Initialize(0.0f, +5.0f, 3.0f);

	slimeActor_.Initialize(0, { {} }, 0);
}

void LifeDrawer::InitializeObjects()
{
	InsertObject("Life", DrawObjectForModel::Create(Transform::Status::Default(), 
		pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Life_O", DrawObjectForModel::Create(Transform::Status::Default(), 
		pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void LifeDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, AnimationTimer(Timer(120), true));
	InsertAnimationTimer(kEarnIndex, AnimationTimer(Timer(30), false));
}

void LifeDrawer::GetReadyForAnimation(const uint32_t index)
{
	if (index & static_cast<uint32_t>(AnimationType::eIdle))
	{

	}
	else if (index & static_cast<uint32_t>(AnimationType::eEarn))
	{
		// ブヨブヨアニメ
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.25f, +0.25f, +0.25f));
		wobbleScaleValues.push_back(Vector3(-1.0f, -1.0f, -1.0f));

		uint32_t wobbleFrame = animationTimers_[index].timer.EndFrame();

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();
	}
}

void LifeDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	animeStatus_.pos_.y += idlePosEas_.In(animationTimers_[kIdleIndex].timer.Ratio());

	animeStatus_.pos_.y += earnPosEas_.Out(animationTimers_[kEarnIndex].timer.Ratio());

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eIn);

	CircleShadowManager::GetInstance()->ActivateCircleShadow(0, pParent_->pos_ - Vector3(0, 1.0f, 0));

}

void LifeDrawer::PlayRecoveryAnimation()
{
	WaveParticle::Emit(
		20,
		*pParentWorldPos_ + Vector3(0.0f, earnPosEas_.End(), 0.0f), {}, 5.0f,
		ColorConfig::skTurquoise[2], 
		pVPMan->ViewProjectionPtr(vpKey_));

	RecoveryParticle::Emit(5, *pParentWorldPos_, pVPMan->ViewProjectionPtr(vpKey_));

	PlayAnimation(static_cast<uint32_t>(LifeDrawer::AnimationType::eEarn), true);
}
