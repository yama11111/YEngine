#pragma once
#include "EBody.h"
#include "EWing.h"
#include "EWeapon.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class EnemyDrawer
{
private:
	// Transform �ȗ�
	using Trfm = Game::Transform;
private:
	// �j
	Trfm core_;
	// ��
	EBody body_;
	// ��
	EWing wing_;
	// ��
	EWeapon sword_[2]{};

	// �������[�V����
	bool isIdle_ = false;

	bool isSwitchI_ = false;
	Math::Ease<Math::Vec3> idleBPE_;
	Math::Ease<Math::Vec3> idleWPE_;
	Math::Ease<Math::Vec3> idleWFE_;
	Math::Ease<Math::Vec3> idleSPE_[2];
	Math::Ease<Math::Vec3> idleSTE_[2];
	Math::Power idlePP_;

	// �������[�V����
	bool isWalk_ = false;

	Math::Ease<Math::Vec3> walkRE_;
	Math::Power walkRP_;

	Math::Ease<Math::Vec3> walkFlySPE_;
	Math::Ease<Math::Vec3> walkFlySTE_[2];
	Math::Power walkFlyPP_;

public:
	// ������
	void Initialize(Math::Mat4* pEnemy);
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw(Game::ViewProjection& vp);
public:
	// 
	void SetWalkActivate(const bool isAct) { isWalk_ = isAct; }
	// 
private:
	// 
	void UpdateIdle();
	// 
	void UpdateWalking();
	// 
	void UpdateAttack();
	// 
	void UpdateFinal();
private:
	// �ÓI���f���|�C���^
	static Game::Model* pModel_;
	// �e�N�X�`��
	static UINT tex_;
public:
	// �ÓI������
	static void StaticInitialize(Game::Model* pModel, const UINT tex);
};

