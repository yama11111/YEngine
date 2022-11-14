#include "PLeg.h"
#include <cassert>

Game::Model* PLeg::pModel_ = nullptr;

void PLeg::StaticInitialize(Game::Model* pModel)
{
	assert(pModel);

	pModel_ = pModel;
}

void PLeg::Initialize(Math::Mat4* pParent)
{
	assert(pParent);

	core_.SetParent(pParent);

	foot_.SetParent(&core_.m_);
	ankle_.SetParent(&core_.m_);

	Reset({});
}

void PLeg::Reset(Trfm::Status state)
{
	tPos_ = tRota_ = tScale_ = {};

	core_.Initialize(state);

	const Math::Vec3 ankleS = { 0.15f,0.2f,0.15f };
	const Math::Vec3 footS  = { 0.25f,0.2f,0.45f };
	const Math::Vec4 color  = { 0.1f,0.8f,0.4f,1.0f };

	const float y = (ankleS.y_ + footS.y_) / 2;

	ankle_.Initialize(
		{
			{0.0f,y,(ankleS.z_ - footS.z_ + 0.1f)},
			{},
			ankleS
		}, 
		color
	);
	foot_.Initialize(
		{
			{0.0f,-y,0.0f},
			{},
			footS
		},
		color
	);

	Update();
}

void PLeg::ResetTransfer()
{
	tPos_ = tRota_ = tScale_ = {};
}

void PLeg::Update()
{
	core_.UniqueUpdate({ tPos_, tRota_, tScale_ });
	foot_.Update();
	ankle_.Update();
}

void PLeg::Draw(Game::ViewProjection& vp, const UINT tex)
{
	pModel_->Draw(ankle_, vp, tex);
	pModel_->Draw(foot_, vp, tex);
}

Math::Vec3 PLeg::Size()
{
	Math::Vec3 result;

	result.x_ = foot_.scale_.x_;
	result.y_ = foot_.scale_.y_ + ankle_.scale_.y_;
	result.z_ = foot_.scale_.z_;

	return result;
}

