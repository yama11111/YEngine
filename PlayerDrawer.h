#pragma once
#include "PBody.h"
#include "PWeapon.h"
#include "PLeg.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class PlayerDrawer
{
private:
	// Transform �ȗ�
	using Trfm = Game::Transform;
private:
	// �j
	Trfm core_;
	// ��
	PBody body_;
	// ��
	PWeapon sword_;
	// ��
	PLeg legs_[2]{};

	// �������[�V����
	bool isIdle_ = false;

	bool isSwitchI_ = false;
	Math::Ease<Math::Vec3> idleBPE_;
	Math::Ease<Math::Vec3> idleSPE_;
	Math::Power idlePP_;

	// �������[�V����
	bool isWalk_ = false;

	bool isSwitchW_ = false;
	Math::Ease<Math::Vec3> walkPE_;
	Math::Ease<Math::Vec3> walkRE_;
	Math::Power walkPP_;
	Math::Power walkRP_;

	bool isSwitchLeg_ = false;
	bool isFB = false;
	Math::Ease<Math::Vec3> walkLegFPE_[2];
	Math::Ease<Math::Vec3> walkLegBPE_[2];
	Math::Ease<Math::Vec3> walkLegFRE_[2];
	Math::Ease<Math::Vec3> walkLegBRE_[2];
	Math::Power walkLegP_;

	int walkJumpCount_ = 0;
	bool isSwitchJump_ = false;
	Math::Ease<Math::Vec3> walkJumpBPE_;
	Math::Ease<Math::Vec3> walkJumpSPE_;
	Math::Power walkJumpPP_;

public:
	// ������
	void Initialize(Math::Mat4* pPlayer);
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

