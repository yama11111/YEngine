#include "PlayerDrawer.h"
#include <cassert>
#include "Calc.h"

Game::Model* PlayerDrawer::pModel_ = nullptr;
UINT PlayerDrawer::tex_;

void PlayerDrawer::StaticInitialize(Game::Model* pModel, UINT tex)
{
	assert(pModel);

	pModel_ = pModel;
	tex_ = tex;

	PLeg::StaticInitialize(pModel);
	PWeapon::StaticInitialize(pModel);
	PBody::StaticInitialize(pModel);
}

void PlayerDrawer::Initialize(Math::Mat4* pPlayer)
{
	assert(pPlayer);

	core_.SetParent(pPlayer);
	
	body_.Initialize(&core_.m_);
	sword_.Initialize(&core_.m_);
	for (size_t i = 0; i < 2; i++)
	{
		legs_[i].Initialize(&core_.m_);
	}

	Reset();
}

void PlayerDrawer::Reset() 
{
	core_.Initialize({});

	body_.Reset({ {0.0f,1.75f,0.0f} });

	sword_.Reset({}, { -1.0, 1, 0.5 }, { -1.25, 0.75, -0.5 });

	for (size_t i = 0; i < 2; i++)
	{
		float px = legs_[i].Size().x_ * 1.75f;
		if (i) px *= -1;
		legs_[i].Reset({ {px, legs_[i].Size().y_, 0.0f} });
	}

	// 立ちモーション
	{
		const float p = 2.0f;
		const int ps = 20;

		isIdle_ = false;
		isSwitchI_ = false;

		idlePP_.Initialize(ps);

		idleBPE_.Initialize({}, Math::Vec3(0, 0.2f, 0), p);
		idleSPE_.Initialize({}, Math::Vec3(0, 0.1f, 0), p);
	}

	// 歩きモーション
	{
		const float p = 1.2f;
		const int ps = 10;
		const int rs = 8;

		isWalk_ = false;
		isSwitchW_ = false;

		walkPP_.Initialize(ps);
		walkRP_.Initialize(rs);

		walkPE_.Initialize({}, { 0.0f,0.4f,0.0f }, p);
		walkRE_.Initialize({}, { (PI / 6.0f),0.0f,0.0f }, p);

		isSwitchLeg_ = false;
		isFB = false;
		walkLegP_.Initialize(ps);
		for (size_t i = 0; i < 2; i++)
		{
			walkLegFPE_[i].Initialize({}, +Math::Vec3(0, +0.75f, 2.0f), p);
			walkLegBPE_[i].Initialize({}, -Math::Vec3(0, -0.50f, 1.5f), p);

			walkLegFRE_[i].Initialize({}, -Math::Vec3((PI / 4.0f), 0, 0), p);
			walkLegBRE_[i].Initialize({}, +Math::Vec3((PI / 2.5f), 0, 0), p);
		}

		walkJumpCount_ = 0;
		isSwitchJump_ = false;

		walkJumpPP_.Initialize(ps);

		walkJumpBPE_.Initialize({}, Math::Vec3(0, 0.3f, +0.2f), p);
		walkJumpSPE_.Initialize({}, Math::Vec3(0, 0.2f, -0.2f), p);
	}

	Update();
}

void PlayerDrawer::UpdateIdle()
{
	isIdle_ = !isWalk_;

	if (idlePP_.IsMax()) { isSwitchI_ = false; }
	if (idlePP_.IsZero()) { isSwitchI_ = true; }

	idlePP_.Update(isSwitchI_ && isIdle_);

	body_.tPos_  += idleBPE_.In(idlePP_.Ratio());
	sword_.tPos_ += idleSPE_.In(idlePP_.Ratio());
}

void PlayerDrawer::UpdateWalking()
{
	if (walkPP_.IsMax()) { isSwitchW_ = false; }
	if (walkPP_.IsZero()) { isSwitchW_ = true; }

	walkPP_.Update(isSwitchW_ && isWalk_);
	walkRP_.Update(isWalk_);

	core_.pos_  = walkPE_.In(walkPP_.Ratio());
	core_.rota_ = walkRE_.In(walkRP_.Ratio());

	if (walkLegP_.IsMax()) { isSwitchLeg_ = false; }
	if (walkLegP_.IsZero()) 
	{
		isSwitchLeg_ = true; 
		isFB = !isFB;
	}

	walkLegP_.Update(isSwitchLeg_ && isWalk_);

	legs_[ isFB].tPos_  += walkLegFPE_[ isFB].In(walkLegP_.Ratio());
	legs_[ isFB].tRota_ += walkLegFRE_[ isFB].In(walkLegP_.Ratio());

	legs_[!isFB].tPos_  += walkLegBPE_[!isFB].In(walkLegP_.Ratio());
	legs_[!isFB].tRota_ += walkLegBRE_[!isFB].In(walkLegP_.Ratio());

	bool isAct = false;
	if (isWalk_)
	{
		if (++walkJumpCount_ >= 5)
		{
			walkJumpCount_ = 5;
			isAct = true;
		}
	}
	else 
	{
		walkJumpCount_ = 0; 
	}

	if (isAct)
	{
		if (walkJumpPP_.IsMax()) { isSwitchJump_ = false; }
		if (walkJumpPP_.IsZero()) { isSwitchJump_ = true; }
	}

	walkJumpPP_.Update(isSwitchJump_ && isWalk_);

	body_.tPos_  += walkJumpBPE_.In(walkJumpPP_.Ratio());
	sword_.tPos_ += walkJumpSPE_.In(walkJumpPP_.Ratio());
}

void PlayerDrawer::UpdateAttack()
{

}

void PlayerDrawer::UpdateFinal()
{
	body_.ResetTransfer();
	sword_.ResetTransfer();
	for (size_t i = 0; i < 2; i++)
	{
		legs_[i].ResetTransfer();
	}
}

void PlayerDrawer::Update()
{
	UpdateIdle();
	UpdateWalking();
	UpdateAttack();

	core_.Update();
	body_.Update();
	sword_.Update();
	for (size_t i = 0; i < 2; i++) 
	{
		legs_[i].Update();
	}

	UpdateFinal();
}

void PlayerDrawer::Draw(Game::ViewProjection& vp)
{
	body_.Draw(vp, tex_);
	sword_.Draw(vp, tex_);
	for (size_t i = 0; i < 2; i++)
	{
		legs_[i].Draw(vp, tex_);
	}
}