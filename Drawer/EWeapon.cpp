#include "EWeapon.h"
#include <cassert>
#include "Calc.h"
#include "DrawerDef.h"

Game::Model* EWeapon::pModel_ = nullptr;

void EWeapon::StaticInitialize(Game::Model* pModel)
{
	assert(pModel);

	pModel_ = pModel;
}

void EWeapon::Initialize(Math::Mat4* pParent, Math::Power* pIdlePP, Math::Power* pWalkFlyPP)
{
	assert(pParent);
	assert(pIdlePP);
	assert(pWalkFlyPP);

	core_.SetParent(pParent);
	pIdlePP_ = pIdlePP;
	pWalkFlyPP_ = pWalkFlyPP;

	blade_.SetParent(&core_.m_);
	guard_.SetParent(&core_.m_);
	for (size_t i = 0; i < 2; i++)
	{
		sub_[i].SetParent(&core_.m_);
	}
	grip_.SetParent(&core_.m_);

	Reset({},{},{});
}

void EWeapon::Reset(Trfm::Status state, Math::Vec3 pith, Math::Vec3 top)
{
	tPos_ = tRota_ = tScale_ = {};
	top_ = top;
	pith_ = pith;

	core_.Initialize(state);

	const Math::Vec3 bladeS = { 0.125f, 0.125f, 1.500f };
	const Math::Vec3 subS   = { 0.050f, 0.250f, 0.050f };
	const Math::Vec3 guardS = { 0.050f, 0.200f, 0.200f };
	const Math::Vec3 gripS  = { 0.075f, 0.075f, 0.500f };
	const Math::Vec4 color = { 0.80f,0.10f,0.10f,1.0f };

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
			{PI / 4, 0,0},
			guardS
		},
		color
	);

	for (size_t i = 0; i < 2; i++)
	{
		float py = subS.y_ * 2 + 0.1f;
		if (i) { py *= -1; }

		sub_[i].Initialize(
			{
				{0.0f,py,0.0f},
				{},
				subS
			},
			color
		);
	}

	grip_.Initialize(
		{
			{0.0f,0.0f,-(gripS.z_ + guardS.z_ + 0.25f)},
			{},
			gripS
		},
		color
	);

	idlePE_.Initialize({}, { 0, 0.2f, 0 }, EnemyPower::IdleP);
	float px = -0.2f;
	if (top.x_ <= 0) { px *= -1; }
	idleTE_.Initialize({}, { px, -0.2f, 0 }, EnemyPower::IdleP);

	walkFlyPE_.Initialize({}, { 0, 0.5f, -1.0f }, EnemyPower::WalkP);
	walkFlyTE_.Initialize({}, { 0, 4.0f, 0 }, EnemyPower::WalkP);


	Update();
}

void EWeapon::ResetTransfer()
{
	tPos_ = tRota_ = tScale_ = {};
}

void EWeapon::Update()
{
	Math::Vec3 t = top_;

	tPos_ += idlePE_.In(pIdlePP_->Ratio());
	t += idleTE_.In(pIdlePP_->Ratio());

	tPos_ += walkFlyPE_.In(pWalkFlyPP_->Ratio());
	t += walkFlyTE_.In(pWalkFlyPP_->Ratio());

	core_.pos_ = pith_;
	core_.rota_ = Math::AdjustAngle((t - pith_).Normalized());

	core_.UniqueUpdate({ tPos_, tRota_, tScale_ });
	blade_.Update();
	guard_.Update();
	for (size_t i = 0; i < 2; i++)
	{
		sub_[i].Update();
	}
	grip_.Update();
}

void EWeapon::Draw(Game::ViewProjection& vp, const UINT tex)
{
	pModel_->Draw(grip_, vp, tex);
	pModel_->Draw(guard_, vp, tex);
	for (size_t i = 0; i < 2; i++)
	{
		pModel_->Draw(sub_[i], vp, tex);
	}
	pModel_->Draw(blade_, vp, tex);
}

Math::Vec3 EWeapon::Size()
{
	Math::Vec3 result;

	//result.x_ = 
	//result.y_ = 
	//result.z_ = 

	return result;
}