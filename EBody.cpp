#include "EBody.h"
#include <cassert>
#include "Calc.h"

Game::Model* EBody::pModel_ = nullptr;

void EBody::StaticInitialize(Game::Model* pModel)
{
	assert(pModel);

	pModel_ = pModel;
}

void EBody::Initialize(Math::Mat4* pParent)
{
	assert(pParent);

	core_.SetParent(pParent);

	body_.SetParent(&core_.m_);
	horn_.SetParent(&core_.m_);
	for (size_t i = 0; i < 2; i++)
	{
		ears1_[i].SetParent(&core_.m_);
		ears2_[i].SetParent(&core_.m_);
	}

	Reset({});
}

void EBody::Reset(Trfm::Status state)
{
	tPos_ = tRota_ = tScale_ = {};

	core_.Initialize(state);

	const Math::Vec3 bodyS = { 0.750f, 0.750f, 0.750f };
	const Math::Vec3 hornS = { 0.200f, 0.200f, 0.750f };
	const Math::Vec3 earS  = { 0.200f, 0.200f, 0.500f };
	const Math::Vec4 color = { 0.40f,0.10f,0.80f,1.0f };

	body_.Initialize(
		{
			{},
			{},
			bodyS,
		},
		color
		);

	horn_.Initialize(
		{
			{0,0.6f,1.0f},
			{-(PI / 6), 0, 0},
			hornS,
		},
		color
		);

	for (size_t i = 0; i < 2; i++)
	{
		float px = 0.7f;
		float ry = -PI / 6;
		if (i)
		{
			px *= -1;
			ry *= -1;
		}
		ears1_[i].Initialize(
			{
				{px,0.8f,-0.5f},
				{(PI / 6),ry,0},
				earS,
			},
			color
			);
	}

	for (size_t i = 0; i < 2; i++)
	{
		float px = 0.7f;
		float ry = -PI / 6;
		if (i)
		{
			px *= -1;
			ry *= -1;
		}
		ears2_[i].Initialize(
			{
				{px,0.2f,-0.5f},
				{-(PI / 6),ry,0},
				earS,
			},
			color
			);
	}

	Update();
}

void EBody::ResetTransfer()
{
	tPos_ = tRota_ = tScale_ = {};
}

void EBody::Update()
{
	core_.UniqueUpdate({ tPos_, tRota_, tScale_ });
	body_.Update();
	horn_.Update();
	for (size_t i = 0; i < 2; i++)
	{
		ears1_[i].Update();
		ears2_[i].Update();
	}
}

void EBody::Draw(Game::ViewProjection& vp, const UINT tex)
{
	pModel_->Draw(body_, vp, tex);
	pModel_->Draw(horn_, vp, tex);
	for (size_t i = 0; i < 2; i++)
	{
		pModel_->Draw(ears1_[i], vp, tex);
		pModel_->Draw(ears2_[i], vp, tex);
	}
}

Math::Vec3 EBody::Size()
{
	Math::Vec3 result;

	//result.x_ = 
	//result.y_ = 
	//result.z_ = 

	return result;
}