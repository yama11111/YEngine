#include "CoinDrawer.h"
#include "DrawObjectForModel.h"
#include "ColorConfig.h"
#include "Lerp.h"
#include "Def.h"

using YGame::CoinDrawer;
using YGame::Model;
using YMath::Timer;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	// モデルポインタ
	Model* pModel = nullptr;

	// アニメーション番号
	const uint32_t kIdleIndex = static_cast<uint32_t>(CoinDrawer::AnimationType::eIdle);
	const uint32_t kEarnIndex = static_cast<uint32_t>(CoinDrawer::AnimationType::eEarn);
}

CoinDrawer* CoinDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	CoinDrawer* newDrawer = new CoinDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void CoinDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::LoadObj("crystal", true);
}

void CoinDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelToon");


	// 立ちアニメーション用
	idlePosEas_.Initialize({ 0.0f, +0.1f, 0.0f, -0.1f, 0.0f }, 1.0f);
	idleRotaEas_.Initialize({ 0.0f, +kPI / 4.0f, 0.0f, -kPI / 4.0f, 0.0f }, 1.0f);

	// 獲得アニメーション用
	earnPosEas_.Initialize(0.0f, +5.0f, 3.0f);
	earnRotaEas_.Initialize(0.0f, +kPI * 6.0f, 3.0f);

	slimeActor_.Initialize(0, { {} }, 0);
}

void CoinDrawer::InitializeObjects()
{
	InsertObject("Coin", DrawObjectForModel::Create(Transform::Status::Default(), spVP_, pModel));
}

void CoinDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, AnimationTimer(Timer(120), true));
	InsertAnimationTimer(kEarnIndex, AnimationTimer(Timer( 30), false));
}

void CoinDrawer::GetReadyForAnimation(const uint32_t index)
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

void CoinDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	animeStatus_.pos_.y_ += idlePosEas_.In(animationTimers_[kIdleIndex].timer.Ratio());
	animeStatus_.rota_.y_ += idleRotaEas_.In(animationTimers_[kIdleIndex].timer.Ratio());

	animeStatus_.pos_.y_ += earnPosEas_.Out(animationTimers_[kEarnIndex].timer.Ratio());
	animeStatus_.rota_.y_ += earnRotaEas_.In(animationTimers_[kEarnIndex].timer.Ratio());

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eIn);
}