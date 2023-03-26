#include "Transform.h"
#include "CalcTransform.h"

using YGame::Transform;
using YMath::Matrix4;
using YMath::Vector4;

Transform::Transform() :
	pos_(0.0f, 0.0f, 0.0f),
	rota_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	m_(Matrix4::Identity()),
	parent_(nullptr)
{}

void Transform::Initialize(const Status& status)
{
	pos_ = status.pos_;
	rota_ = status.rota_;
	scale_ = status.scale_;
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(scale_) * MatRotation(rota_) * MatTranslation(pos_);
	if (parent_) { m_ *= *parent_; }
}

void Transform::UpdateMatrix(const Status& status)
{
	Status s = { pos_,rota_,scale_ };
	s.pos_ += status.pos_;
	s.rota_ += status.rota_;
	s.scale_ += status.scale_;

	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(s.scale_) * MatRotation(s.rota_) * MatTranslation(s.pos_);
	if (parent_) { m_ *= *parent_; }
}
