#include "ScrollCamera.h"

using YGame::ScrollCamera;
using YGame::ViewProjection;
using YGame::Camera;
using YMath::Vector3;

void ScrollCamera::Initialize(const Vector3 distance, Vector3* pFollowPoint, const Vector3 tolerance)
{
	// 追従位置
	Vector3 followPoint;

	// 追従点があるなら
	if (pFollowPoint)
	{
		// 代入
		followPoint = *pFollowPoint;
	}

	// 初期化 + 代入
	Camera::Initialize(followPoint + distance, pFollowPoint, true);

	distance_ = distance;
	tolerance_ = tolerance;
}

void ScrollCamera::Update()
{
	// 追従位置
	Vector3 followPoint;

	// 追従点があるなら
	if (pFollowPoint_)
	{
		// 代入
		followPoint = *pFollowPoint_;
	}

	// 視点を 追従点 + 距離 の位置に
	pos_ = followPoint + distance_;

	// カメラ更新
	Camera::Update();
}

void ScrollCamera::SetFollowPoint(Vector3* pFollowPoint)
{
	// 追従点
	Camera::SetFollowPoint(pFollowPoint);
}
