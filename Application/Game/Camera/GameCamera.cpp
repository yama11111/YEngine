#include "GameCamera.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "Lerp.h"

using YGame::GameCamera;
using YMath::Vector3;
using YMath::Power;

namespace
{
	const Vector3 kTarget = Vector3(+32.0f, -12.0f, +64.0f);
	const Vector3 kDistance = Vector3(-6.0f, +12.0f, -40.0f);

	const Vector3 kMaxRange = Vector3(+2.0f, +50.0f, +100000.0f);
	const Vector3 kMinRange = Vector3(-2.0f, -50.0f, -100000.0f);

	const Vector3 kSpeed = Vector3(0.5f, 0.5f, 0.0f);

	const Vector3 kAccelEndPos = (kDistance - kTarget) * 0.1f;
}

void GameCamera::Initialize()
{
	camera_.Initialize({}, {});

	target_ = kTarget;
	distance_ = kDistance;

	elderPlayerPos_ = {};

	movePower_.Initialize(60);

	accelPower_.Initialize(30);
	isActAccelPower_ = false;

	camera_.pos_ = distance_;
	camera_.rota_ = AdjustAngle(target_.Normalized());

	camera_.Update();
}

void GameCamera::Update()
{
	if (pPlayerPos_ == nullptr) { return; }
	
	UpdatePos();

	accelPower_.Update(isActAccelPower_);
	if (accelPower_.IsMax()) { isActAccelPower_ = false; }
	Vector3 animePos = YMath::EaseOut(Vector3(), kAccelEndPos, accelPower_.Ratio(), 3.0f);

	camera_.rota_ = YMath::AdjustAngle(target_.Normalized());
	camera_.Update({ animePos });

	elderPlayerPos_ = *pPlayerPos_;
}

void GameCamera::UpdatePos()
{
	Vector3 base = *pPlayerPos_ + distance_;
	if (YMath::InRange(camera_.pos_, base + kMinRange, base + kMaxRange)) { return; }

	Vector3 vectorCameraToBase = base - camera_.pos_;
	Vector3 direction = vectorCameraToBase.Normalized();

	Vector3 lengthRatio = vectorCameraToBase / 1.0f;
	lengthRatio = YMath::Abs(lengthRatio);
	lengthRatio = YMath::Clamp(lengthRatio, Vector3(), Vector3(1.0f, 1.0f, 1.0f));
	
	Vector3 speed = YMath::MultAtComponent(kSpeed, lengthRatio);

	camera_.pos_ += YMath::MultAtComponent(direction, speed);
}

void GameCamera::MoveOnJump()
{
}

void GameCamera::MoveOnAccel()
{
	isActAccelPower_ = true;
}

void GameCamera::Shaking(const float swing, const float dekey, const float place)
{
	camera_.Shaking(swing, dekey, place);
}

void GameCamera::SetPlayerPosPtr(YMath::Vector3* pFollowPoint)
{
	pPlayerPos_ = pFollowPoint;
}

YGame::ViewProjection GameCamera::GetViewProjection() const
{
	return camera_.GetViewProjection();
}
