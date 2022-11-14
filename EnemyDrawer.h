#pragma once
#include "EBody.h"
#include "EWing.h"
#include "EWeapon.h"

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

	Math::Power idlePP_;

	// �������[�V����
	bool isWalk_ = false;

	Math::Ease<Math::Vec3> walkRE_;
	Math::Power walkRP_;

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

