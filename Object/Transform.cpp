#include "Transform.h"

using Object::Transform;
using DX::ConstBufferManager;
using Math::MatWorld;
using Math::Mat4;
using Math::Vec4;

ConstBufferManager* Transform::pCBManager_ = nullptr;

void Transform::StaticInitialize(ConstBufferManager* pCBManager)
{
	pCBManager_ = pCBManager;
}

Transform::Transform() :
	mw_()
{
	pCBManager_->CreateCB(cbMtrl_);
	pCBManager_->CreateCB(cbTrfm_);
}

Transform::Transform(const MatWorld::InitStatus& init, const Vec4& color) :
	mw_(init)
{
	pCBManager_->CreateCB(cbMtrl_, color);
	pCBManager_->CreateCB(cbTrfm_);
}

void Transform::Initialize(const MatWorld::InitStatus& init, const Vec4& color)
{
	mw_.Initialize(init);
	SetColor(color);
}

void Transform::Update()
{
	mw_.Update();
	if (parent_) { mw_.m_ *= parent_->m_; }
}

void Transform::UniqueUpdate(const MatWorld::InitStatus& state)
{
	MatWorld m = mw_;
	m.pos_ += state.pos_;
	m.rota_ += state.rota_;
	m.scale_ += state.scale_;

	m.Update();
	if (parent_) { m.m_ *= parent_->m_; }
}

void Transform::SetDrawCommand(const Math::Mat4& view, const Math::Mat4& projection)
{
	cbTrfm_.map_->mat_ = mw_.m_ * view * projection;

	pCBManager_->SetDrawCommand(cbMtrl_);
	pCBManager_->SetDrawCommand(cbTrfm_);
}

void Transform::SetParent(MatWorld* parent)
{
	if (parent == nullptr) return;
	this->parent_ = parent;
}