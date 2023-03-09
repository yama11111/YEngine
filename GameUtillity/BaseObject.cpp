#include "BaseObject.h"
#include "CalcTransform.h"

using YGame::BaseObject;
using YMath::Matrix4;
using YMath::Vector4;

BaseObject::BaseObject() :
	pos_(0.0f, 0.0f, 0.0f), 
	rota_(0.0f, 0.0f, 0.0f), 
	scale_(1.0f, 1.0f, 1.0f), 
	m_(Matrix4::Identity()),
	parent_(nullptr)
{}

void BaseObject::Initialize(const Status& state)
{
	pos_ = state.pos_;
	rota_ = state.rota_;
	scale_ = state.scale_;
	UpdateMatrix();
}

void BaseObject::UpdateMatrix()
{
	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(scale_) * MatRotation(rota_) * MatTranslation(pos_);
	if (parent_) { m_ *= *parent_; }
}

void BaseObject::UpdateMatrix(const Status& state)
{
	Status s = { pos_,rota_,scale_ };
	s.pos_ += state.pos_;
	s.rota_ += state.rota_;
	s.scale_ += state.scale_;

	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(s.scale_) * MatRotation(s.rota_) * MatTranslation(s.pos_);
	if (parent_) { m_ *= *parent_; }
}