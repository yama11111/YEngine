#include "Camera.h"
#include "CalcTransform.h"
#include <cassert>

using YGame::Transform;
using YGame::ViewProjection;
using YGame::Camera;
using YMath::Vector3;
using YMath::MultVec3Mat4;

void Camera::Initialize(const Transform::Status& status, YMath::Vector3* pFollowPos, bool isFollow)
{
	// 初期化 + 代入
	shake_.Initialize();
	pos_ = status.pos_;
	rota_ = status.rota_;
	transform_.Initialize(status);
	vp_.Initialize({});

	pFollowPoint_ = pFollowPos;
	SetIsFollow(isFollow);

	// 更新
	Update();
}

void Camera::UpdateTarget()
{
	// 追従する && 追従点が前回と違う場所にあるなら
	if (isFollow_ && (vp_.eye_ != *pFollowPoint_))
	{
		// 注視点に追従点代入
		vp_.target_ = *pFollowPoint_;
	}
	// 無いなら
	else
	{
		// 自分の向いている方向を注視点とする
		Vector3 forward = MultVec3Mat4(Vector3(0, 0, 1), transform_.m_);
		vp_.target_ = vp_.eye_ + forward;
	}
}
void Camera::Update()
{
	// 位置 + 回転更新
	transform_.pos_ = pos_;
	transform_.rota_ = rota_;
	
	// アフィン変換
	transform_.UpdateMatrix();
	
	// カメラシェイク更新
	shake_.Update();


	// 視点更新
	vp_.eye_ = transform_.pos_;
	// 注視点更新
	UpdateTarget();
	// 上方向ベクトル更新
	vp_.up_ = MultVec3Mat4(Vector3(0, 1, 0), transform_.m_);

	// ビュープロジェクション行列更新
	vp_.UpdateMatrix();
}

void Camera::Shaking(const int swing, const int dekey)
{
	// カメラシェイク
	shake_.Activate(swing, dekey);
}

YGame::ViewProjection Camera::GetViewProjection()
{
	// 戻り値用
	YGame::ViewProjection result = vp_;
	
	// カメラシェイク加算
	result.eye_ += shake_.Value() / 10.0f;
	result.target_ += shake_.Value() / 10.0f;
	
	// 行列更新
	result.UpdateMatrix();

	return result;
}

Vector3 Camera::Direction()
{
	// 向きを計算
	Vector3 vel = MultVec3Mat4(Vector3(0, 0, 1), transform_.m_);
	
	return vel.Normalized();
}

void Camera::SetFollowPoint(YMath::Vector3* pFollowPoint, const bool isFollow)
{
	// nullチェック
	assert(pFollowPoint);
	
	// 代入
	pFollowPoint_ = pFollowPoint;
	isFollow_ = isFollow;
}

void Camera::SetIsFollow(const bool isFollow)
{
	// 追従点があるなら
	if (pFollowPoint_) 
	{
		// 代入
		isFollow_ = isFollow; 
	}
	// 無いなら
	else 
	{
		// 追従点しない
		isFollow_ = false; 
	}
}
