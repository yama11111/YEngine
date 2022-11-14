#include "EnemyDrawer.h"
#include <cassert>
#include "Calc.h"

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

	body_.Initialize(&core_.m_);
	wing_.Initialize(&core_.m_);
	for (size_t i = 0; i < 2; i++)
	{
		sword_[i].Initialize(&core_.m_);
	}

	Reset();
}

void EnemyDrawer::Reset()
{
	float scale = 1.0f;
	core_.Initialize({ {},{},{scale,scale,scale} });

	body_.Reset({ {0.0f,1.50f,0.0f} });
	wing_.Reset({ {0.0f,1.0f,-2.50f} }, { 0,3.0f,1.0f });

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
		const float p = 1.2f;
		const int ps = 60;

		isIdle_ = false;
		isSwitchI_ = false;

		idlePP_.Initialize(ps);

		idleBPE_.Initialize({}, Math::Vec3(0, 0.4f, 0), p);
		idleWPE_.Initialize({}, Math::Vec3(0, 0.6f, 0), p);
		idleWFE_.Initialize(wing_.focus_, wing_.focus_ + Math::Vec3(0, 0.3f, 0), p);
		for (size_t i = 0; i < 2; i++)
		{
			float px = -0.2f;
			if (i) { px *= -1; }

			idleSPE_[i].Initialize({}, Math::Vec3(0, 0.2f, 0), p);
			idleSTE_[i].Initialize(sword_[i].top_, sword_[i].top_ + Math::Vec3(px, -0.2f, 0), p);
		}
	}

	// 歩きモーション
	{
		const float p = 1.2f;
		const int s = 10;

		isWalk_ = false;

		walkRP_.Initialize(s);

		walkRE_.Initialize({}, { (PI / 4.0f),0.0f,0.0f }, p);

		walkFlyPP_.Initialize(s);

		for (size_t i = 0; i < 2; i++)
		{
			walkFlySTE_[i].Initialize(sword_[i].top_, sword_[i].top_ + Math::Vec3(0, 4.0f, 0), p);
		}

		walkFlySPE_.Initialize({}, Math::Vec3(0, 0.5f, -1.0f), p);
	}

	Update();
}

void EnemyDrawer::UpdateIdle()
{
	isIdle_ = !isWalk_;

	if (idlePP_.IsMax()) { isSwitchI_ = false; }
	if (idlePP_.IsZero()) { isSwitchI_ = true; }

	idlePP_.Update(isSwitchI_ && isIdle_);

	body_.tPos_ += idleBPE_.In(idlePP_.Ratio());
	wing_.tPos_ += idleWPE_.In(idlePP_.Ratio());
	wing_.focus_ = idleWFE_.In(idlePP_.Ratio());
	for (size_t i = 0; i < 2; i++)
	{
		sword_[i].tPos_ += idleSPE_[i].In(idlePP_.Ratio());
		sword_[i].top_ = idleSTE_[i].In(idlePP_.Ratio());
	}
}

void EnemyDrawer::UpdateWalking()
{
	walkRP_.Update(isWalk_);

	core_.rota_ = walkRE_.In(walkRP_.Ratio());

	walkFlyPP_.Update(isWalk_);

	for (size_t i = 0; i < 2; i++)
	{
		sword_[i].tPos_ += walkFlySPE_.In(walkFlyPP_.Ratio());
		sword_[i].top_ = walkFlySTE_[i].In(walkFlyPP_.Ratio());
	}
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

