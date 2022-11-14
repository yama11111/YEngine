#include "PBody.h"
#include <cassert>
#include "Calc.h"
#include "DrawerDef.h"

Game::Model* PBody::pModel_ = nullptr;

void PBody::StaticInitialize(Game::Model* pModel)
{
	assert(pModel);

	pModel_ = pModel;
}

void PBody::Initialize(Math::Mat4* pParent, Math::Power* pIdlePP, Math::Power* pWalkPendPP)
{
	assert(pParent);
	assert(pIdlePP);
	assert(pWalkPendPP);

	core_.SetParent(pParent);
	pIdlePP_ = pIdlePP;
	pWalkPendPP_ = pWalkPendPP;

	body_.SetParent(&core_.m_);
	for (size_t i = 0; i < 2; i++)
	{
		ears_[i].SetParent(&core_.m_);
	}

	Reset({});
}

void PBody::Reset(Trfm::Status state)
{
	assert(pIdlePP_);
	assert(pWalkPendPP_);

	ResetTransfer();

	core_.Initialize(state);

	const Math::Vec3 bodyS = { 0.500f, 0.500f, 0.500f };
	const Math::Vec3 earS  = { 0.125f, 0.125f, 0.500f };
	const Math::Vec4 color = { 0.80f,0.10f,0.40f,1.0f };

	body_.Initialize(
		{
			{},
			{},
			bodyS,
		}, 
		color
	);

	for (size_t i = 0; i < 2; i++)
	{
		float px = 0.4f;
		float ry = -PI / 6;
		if (i) 
		{
			px *= -1; 
			ry *= -1;
		}
		ears_[i].Initialize(
			{
				{px,0.6f,-0.25f},
				{(PI / 6),ry,0},
				earS,
			},
			color
		);
	}


	idlePE_.Initialize({}, Math::Vec3(0, 0.2f, 0), PlayerPower::IdleP);

	walkPendPE_.Initialize({}, Math::Vec3(0, 0.3f, +0.2f), PlayerPower::WalkP);

	Update();
}

void PBody::ResetTransfer()
{
	tPos_ = tRota_ = tScale_ = {};
}

void PBody::Update()
{
	tPos_ += idlePE_.In(pIdlePP_->Ratio());
	tPos_ += walkPendPE_.In(pWalkPendPP_->Ratio());

	core_.UniqueUpdate({tPos_, tRota_, tScale_});
	body_.Update();
	for (size_t i = 0; i < 2; i++)
	{
		ears_[i].Update();
	}
}

void PBody::Draw(Game::ViewProjection& vp, const UINT tex)
{
	pModel_->Draw(body_, vp, tex);
	for (size_t i = 0; i < 2; i++)
	{
		pModel_->Draw(ears_[i], vp, tex);
	}
}

Math::Vec3 PBody::Size()
{
	Math::Vec3 result;

	//result.x_ = 
	//result.y_ = 
	//result.z_ = 

	return result;
}