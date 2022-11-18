#include "Transform.h"
#include "Calc.h"

using Game::Transform;
using DX::ConstBuffer;
using Math::Mat4;
using Math::Vec4;

Transform::Transform()
{
	cbTrfm_.Create();
	cbTrfm_.map_->mat_ = Math::Mat4::Identity();
	cbColor_.Create();
	cbColor_.map_->color_ = Math::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Initialize({});
}

void Transform::Initialize(const Status& state, const Vec4& color)
{
	pos_ = state.pos_;
	rota_ = state.rota_;
	scale_ = state.scale_;
	Update();

	color_ = color;
}

void Transform::Update()
{
	// アフィン変換
	m_ = Mat4::Identity();
	m_ *= MatScale(scale_) * MatRotation(rota_) * MatTranslation(pos_);
	if (parent_) { m_ *= *parent_; }
}

void Transform::UniqueUpdate(const Status& state)
{
	Status s = { pos_,rota_,scale_ };
	s.pos_ += state.pos_;
	s.rota_ += state.rota_;
	s.scale_ += state.scale_;

	// アフィン変換
	m_ = Mat4::Identity();
	m_ *= MatScale(s.scale_) * MatRotation(s.rota_) * MatTranslation(s.pos_);
	if (parent_) { m_ *= *parent_; }
}

void Transform::SetDrawCommand(const Math::Mat4& view, const Math::Mat4& projection)
{
	cbTrfm_.map_->mat_ = m_ * view * projection;
	cbTrfm_.SetDrawCommand();

	cbColor_.map_->color_ = color_;
	cbColor_.SetDrawCommand();
}

void Transform::SetParent(Mat4* parent)
{
	if (parent == nullptr) return;
	this->parent_ = parent;
}
