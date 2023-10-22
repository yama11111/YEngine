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
	pModel = Model::LoadObj("skydome", true);
}

void CoinDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelToon");
}

void CoinDrawer::InitializeObjects()
{
	InsertObject("Coin", DrawObjectForModel::Create({}, spVP_, pModel));
}

void CoinDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, AnimationTimer());
	InsertAnimationTimer(kEarnIndex, AnimationTimer());
}

void CoinDrawer::GetReadyForAnimation(const uint32_t index)
{
	index;
}

void CoinDrawer::UpdateAnimation()
{

}