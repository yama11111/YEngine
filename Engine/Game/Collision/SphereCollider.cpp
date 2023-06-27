#include "SphereCollider.h"

using YGame::SphereCollider;
using YMath::Vector3;

void SphereCollider::Initialize(
	const Vector3& offset,
	const uint32_t attribute, const uint32_t mask,
	const float radius,
	const bool isSlip)
{
	// 親ポインタ null で初期化
	Initialize(nullptr, offset, attribute, mask, radius, isSlip);
}

void SphereCollider::Initialize(
	Transform* pParent, const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const float radius, 
	const bool isSlip)
{
	// 基底クラス初期化
	BaseCollider::Initialize(pParent, offset, attribute, mask, isSlip);

	// 形状 : 球
	shapeType_ = ShapeType::eSphere;

	// 半径
	Sphere::SetSphereRadius(radius);

	// 更新
	Update();
}

void SphereCollider::Update()
{
	// 中心点
	Vector3 center = offset_;

	// 親があるなら
	if (pParent_)
	{
		// 位置分ずらす
		center += pParent_->pos_;
	}

	// 中心点更新
	SetSphereCenter(center);
}

SphereCollider::SphereCollider(
	const Vector3& offset,
	const uint32_t attribute, const uint32_t mask,
	const float radius,
	const bool isSlip) :
	BaseCollider(offset, attribute, mask, isSlip)
{
	Sphere::SetSphereRadius(radius);
}

SphereCollider::SphereCollider(
	Transform* pParent, const Vector3& offset, 
	const uint32_t attribute, const uint32_t mask, 
	const float radius, 
	const bool isSlip) : 
	BaseCollider(pParent, offset, attribute, mask, isSlip)
{
	Sphere::SetSphereRadius(radius);
}
