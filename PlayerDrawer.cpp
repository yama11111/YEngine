#include "PlayerDrawer.h"
#include <cassert>
#include "Calc.h"
#include "DrawerDef.h"

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
	
	body_.Initialize(&core_.m_, &idlePP_, &walkPendPP_);

	sword_.Initialize(&core_.m_, &idlePP_, &walkPendPP_);
	for (size_t i = 0; i < 2; i++)
	{
		legs_[i].Initialize(&core_.m_, &walkLegP_);
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
		isIdle_ = false;
		isSwitchI_ = false;

		idlePP_.Initialize(PlayerSecond::IdleS);
	}

	// 歩きモーション
	{
		isWalk_ = false;
		isSwitchW_ = false;

		walkPP_.Initialize(PlayerSecond::WalkS);
		walkPE_.Initialize({}, { 0.0f,0.4f,0.0f }, PlayerPower::WalkP);

		walkRP_.Initialize(PlayerSecond::WalkS);
		walkRE_.Initialize({}, { (PI / 6.0f),0.0f,0.0f }, PlayerPower::WalkP);


		isSwitchLeg_ = false;
		isFB = false;

		walkLegP_.Initialize(PlayerSecond::WalkS);


		walkJumpCount_ = 0;
		isSwitchPend_ = false;

		walkPendPP_.Initialize(PlayerSecond::WalkS);
	}

	Update();
}

void PlayerDrawer::UpdateIdle()
{
	isIdle_ = !isWalk_;

	if (idlePP_.IsMax()) { isSwitchI_ = false; }
	if (idlePP_.IsZero()) { isSwitchI_ = true; }

	idlePP_.Update(isSwitchI_ && isIdle_);
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
		if (walkPendPP_.IsMax()) { isSwitchPend_ = false; }
		if (walkPendPP_.IsZero()) { isSwitchPend_ = true; }
	}

	walkPendPP_.Update(isSwitchPend_ && isWalk_);
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
	legs_[0].Update(isFB);
	legs_[1].Update(!isFB);

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