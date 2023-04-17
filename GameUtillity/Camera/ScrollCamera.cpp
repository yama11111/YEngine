#include "ScrollCamera.h"

using YGame::ScrollCamera;
using YGame::ViewProjection;
using YGame::Camera;
using YMath::Vector3;

void ScrollCamera::Initialize(const Vector3 distance, Vector3* pFollowPoint, const Vector3 tolerance)
{
	// 初期化 + 代入
	Camera::Initialize(*pFollowPoint + distance, pFollowPoint);

	distance_ = distance;
	tolerance_ = tolerance;
}

void ScrollCamera::Update()
{
	// 視点を 追従点 + 距離 の位置に
	pos_ = *pFollowPoint_ + distance_;

	// カメラ更新
	Camera::Update();
}
