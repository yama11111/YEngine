#include "EnemyDrawer.h"
#include <cassert>
#include "Calc.h"
#include "DrawerDef.h"

Game::Model* EnemyDrawer::pModel_ = nullptr;
UINT EnemyDrawer::tex_;

void EnemyDrawer::StaticInitialize(Game::Model* pModel, UINT tex)
{
	assert(pModel);

	pModel_ = pModel;
	tex_ = tex;

	EBody::StaticInitialize(pModel);
	EWing::StaticInitialize(pModel);
	EWeapon::StaticInitialize(pModel);
}

void EnemyDrawer::Initialize(Math::Mat4* pEnemy)
{
	assert(pEnemy);

	core_.SetParent(pEnemy);

	body_.Initialize(&core_.m_, &idlePP_, &walkRP_);
	wing_.Initialize(&core_.m_, &idlePP_, &walkFlyPP_);
	for (size_t i = 0; i < 2; i++)
	{
		sword_[i].Initialize(&core_.m_, &idlePP_, &walkFlyPP_);
	}

	Reset();
}

void EnemyDrawer::Reset()
{
	float scale = 1.0f;
	core_.Initialize({ {},{},{scale,scale,scale} });

	body_.Reset({ {0.0f,1.50f,0.0f} });
	wing_.Reset({ {0.0f,1.0f,-2.50f} });

	for (size_t i = 0; i < 2; i++)
	{
		float px1 = 2.0f;
		float px2 = 3.0f;
		if (i) 
		{
			px1 *= -1;
			px2 *= -1;
		}
		sword_[i].Reset({}, { px1, 1.0f, 1.0f }, { px2, 0.5f, 4.5f });
	}

	// 立ちモーション
	{
		isIdle_ = false;
		isSwitchI_ = false;

		idlePP_.Initialize(EnemySecond::IdleS);
	}

	// 歩きモーション
	{
		isWalk_ = false;

		walkRP_.Initialize(EnemySecond::WalkS);
		walkRE_.Initialize({}, { (PI / 4.0f),0.0f,0.0f }, EnemyPower::WalkP);

		walkFlyPP_.Initialize(EnemySecond::WalkS);
	}

	Update();
}

void EnemyDrawer::UpdateIdle()
{
	isIdle_ = !isWalk_;

	if (idlePP_.IsMax()) { isSwitchI_ = false; }
	if (idlePP_.IsZero()) { isSwitchI_ = true; }

	idlePP_.Update(isSwitchI_ && isIdle_);
}

void EnemyDrawer::UpdateWalking()
{
	walkRP_.Update(isWalk_);

	core_.rota_ = walkRE_.In(walkRP_.Ratio());

	walkFlyPP_.Update(isWalk_);
}

void EnemyDrawer::UpdateAttack()
{
}

void EnemyDrawer::UpdateFinal()
{
	body_.ResetTransfer();
	wing_.ResetTransfer();
	for (size_t i = 0; i < 2; i++)
	{
		sword_[i].ResetTransfer();
	}
}

void EnemyDrawer::Update()
{
	UpdateIdle();
	UpdateWalking();
	UpdateAttack();

	core_.Update();
	body_.Update();
	wing_.Update();
	for (size_t i = 0; i < 2; i++)
	{
		sword_[i].Update();
	}

	UpdateFinal();
}

void EnemyDrawer::Draw(Game::ViewProjection& vp)
{
	body_.Draw(vp, tex_);
	wing_.Draw(vp, tex_);
	for (size_t i = 0; i < 2; i++)
	{
		sword_[i].Draw(vp, tex_);
	}
}

