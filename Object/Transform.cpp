#include "Transform.h"
#include "Calc.h"

using Object::Transform;
using DX::ConstBufferManager;
using Math::Mat4;
using Math::Vec4;

ConstBufferManager* Transform::pCBManager_ = nullptr;

void Transform::StaticInitialize(ConstBufferManager* pCBManager)
{
	pCBManager_ = pCBManager;
}

Transform::Transform()
{
	pCBManager_->CreateCB(cbMtrl_);
	pCBManager_->CreateCB(cbTrfm_);
	Initialize({});
}

Transform::Transform(const Status& state, const Vec4& color)
{
	pCBManager_->CreateCB(cbMtrl_, color);
	pCBManager_->CreateCB(cbTrfm_);
	Initialize(state, color);
}

void Transform::Initialize(const Status& state, const Vec4& color)
{
	pos_ = state.pos_;
	rota_ = state.rota_;
	scale_ = state.scale_;
	Update();
	SetColor(color);
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

	pCBManager_->SetDrawCommand(cbMtrl_);
	pCBManager_->SetDrawCommand(cbTrfm_);
}

void Transform::SetParent(Mat4* parent)
{
	if (parent == nullptr) return;
	this->parent_ = parent;
}

void Transform::SetColor(const Math::Vec4& color)
{
	cbMtrl_.map_->color_ = color;
}
