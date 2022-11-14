#include "PWeapon.h"
#include <cassert>
#include "Calc.h"

Game::Model* PWeapon::pModel_ = nullptr;

void PWeapon::StaticInitialize(Game::Model* pModel)
{
	assert(pModel);

	pModel_ = pModel;
}

void PWeapon::Initialize(Math::Mat4* pParent)
{
	assert(pParent);

	core_.SetParent(pParent);

	blade_.SetParent(&core_.m_);
	guard_.SetParent(&core_.m_);
	grip_.SetParent(&core_.m_);

	Reset({},{},{});
}

void PWeapon::Reset(Trfm::Status state, Math::Vec3 pith, Math::Vec3 top)
{
	tPos_ = tRota_ = tScale_ = {};
	top_ = top;
	pith_ = pith;

	core_.Initialize(state);

	const Math::Vec3 bladeS = { 0.075f, 0.200f, 1.000f };
	const Math::Vec3 guardS = { 0.050f, 0.200f, 0.200f };
	const Math::Vec3 gripS  = { 0.050f, 0.050f, 0.300f };
	const Math::Vec4 color = { 0.10f,0.80f,0.40f,1.0f };

	blade_.Initialize(
		{
			{0.0f,0.0f,bladeS.z_ + guardS.z_ + 0.25f},
			{},
			bladeS
		},
		color
	);
	guard_.Initialize(
		{
			{0.0f,0.0f,0.0f},
			{PI/ 4, 0,0},
			guardS
		},
		color
	);
	grip_.Initialize(
		{
			{0.0f,0.0f,-(gripS.z_ + guardS.z_ + 0.25f)},
			{},
			gripS
		},
		color
	);

	Update();
}

void PWeapon::ResetTransfer()
{
	tPos_ = tRota_ = tScale_ = {};
}

void PWeapon::Update()
{
	core_.pos_ = pith_;
	core_.rota_ = Math::AdjustAngle((top_ - pith_).Normalized());

	core_.UniqueUpdate({ tPos_, tRota_, tScale_ });
	blade_.Update();
	guard_.Update();
	grip_.Update();
}

void PWeapon::Draw(Game::ViewProjection& vp, const UINT tex)
{
	pModel_->Draw(grip_, vp, tex);
	pModel_->Draw(guard_, vp, tex);
	pModel_->Draw(blade_, vp, tex);
}

Math::Vec3 PWeapon::Size()
{
	Math::Vec3 result;

	//result.x_ = 
	//result.y_ = 
	//result.z_ = 

	return result;
}