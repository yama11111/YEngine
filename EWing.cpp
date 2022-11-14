#include "EWing.h"
#include <cassert>
#include "Calc.h"

Game::Model* EWing::pModel_ = nullptr;

void EWing::StaticInitialize(Game::Model* pModel)
{
	assert(pModel);

	pModel_ = pModel;
}

void EWing::Initialize(Math::Mat4* pParent)
{
	assert(pParent);

	core_.SetParent(pParent);

	for (size_t i = 0; i < 3; i++)
	{
		blade1_[i].SetParent(&core_.m_);
		blade2_[i].SetParent(&core_.m_);
	}

	Reset({}, {});
}

void EWing::Reset(Trfm::Status state, Math::Vec3 focus)
{
	tPos_ = tRota_ = tScale_ = {};

	core_.Initialize(state);

	const Math::Vec3 bladeS = { 0.150f, 0.150f, 1.250f };
	const Math::Vec4 color = { 0.40f,0.10f,0.80f,1.0f };

	const float x = 1.0f;
	const float y = 0.5f;

	focus_ = focus;

	for (size_t i = 0; i < 3; i++)
	{
		float w = 2.0f;

		Math::Vec3 p1 = {  (x * i) + w, (y * (i + 1)), 0.0f };
		Math::Vec3 p2 = { -(x * i) - w, (y * (i + 1)), 0.0f };

		Math::Vec3 r1 = Math::AdjustAngle((focus_ - p1).Normalized());
		Math::Vec3 r2 = Math::AdjustAngle((focus_ - p2).Normalized());

		blade1_[i].Initialize({ p1,r1,bladeS, }, color);
		blade2_[i].Initialize({ p2,r2,bladeS, }, color);
	}

	Update();
}

void EWing::ResetTransfer()
{
	tPos_ = tRota_ = tScale_ = {};
}

void EWing::Update()
{
	core_.UniqueUpdate({ tPos_, tRota_, tScale_ });
	for (size_t i = 0; i < 3; i++)
	{
		blade1_[i].rota_ = Math::AdjustAngle((focus_ - blade1_[i].pos_).Normalized());
		blade2_[i].rota_ = Math::AdjustAngle((focus_ - blade2_[i].pos_).Normalized());

		blade1_[i].Update();
		blade2_[i].Update();
	}
}

void EWing::Draw(Game::ViewProjection& vp, const UINT tex)
{
	for (size_t i = 0; i < 3; i++)
	{
		pModel_->Draw(blade1_[i], vp, tex);
		pModel_->Draw(blade2_[i], vp, tex);
	}
}

Math::Vec3 EWing::Size()
{
	Math::Vec3 result;

	//result.x_ = 
	//result.y_ = 
	//result.z_ = 

	return result;
}