#include "BaseCharacterDrawer.h"
#include "ViewProjectionManager.h"
#include "MathVector.h"

using YGame::BaseCharacterDrawer;
using YMath::Vector3;
using YMath::Matrix4;

namespace 
{
	// 描画範囲
	const float kRange = 750.0f;
}

void BaseCharacterDrawer::Update()
{
	BaseDrawer::Update();

	UpdateSeeThrough();
}

void BaseCharacterDrawer::UpdateSeeThrough()
{
	if (isSeeThrough_ == false) { return; }
	if (pParentPosMat_ == nullptr) { return; }

	// 視点との距離
	Vector3 eye = ViewProjectionManager::GetInstance()->ViewProjectionPtr(vpKey_)->eye_;
	Vector3 pos = YMath::VecTranslation(*pParentPosMat_);
	float distance = Vector3(eye - pos).Length();

	// 視点との距離の比率でアルファ値変化(遠いほど薄く)
	float distanceRate = 1.0f - distance / kRange;
	if (distanceRate >= 1.0f) { distanceRate = 1.0f; }

	cbColor_->data_.texColorRate.w = distanceRate;

	// 一定値以下は描画切る
	SetIsVisible((distanceRate >= 0.01f));
}

void BaseCharacterDrawer::SetParentPosMatPointer(YMath::Matrix4* pParentPosMat)
{
	pParentPosMat_ = pParentPosMat;
}

void BaseCharacterDrawer::SetWorldKey(const WorldKey worldKey)
{
	worldKey_ = worldKey;
}
