#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class EWeapon
{
private:
	// Transform �ȗ�
	using Trfm = Game::Transform;
public:
	// �]���pPos
	Math::Vec3 tPos_;
	// �]���pRota
	Math::Vec3 tRota_;
	// �]���pScale
	Math::Vec3 tScale_;
	// �؂���
	Math::Vec3 top_;
	// �c
	Math::Vec3 pith_;
private:
	// �j
	Trfm core_;
	// ���g
	Trfm blade_;
	// ��
	Trfm guard_;
	// ���g2
	Trfm sub_[2];
	// ������
	Trfm grip_;
private:
	// �������[�V����
	Math::Ease<Math::Vec3> idlePE_;
	Math::Ease<Math::Vec3> idleTE_;
	Math::Power* pIdlePP_ = nullptr;
	// �������[�V����
	Math::Ease<Math::Vec3> walkFlyPE_;
	Math::Ease<Math::Vec3> walkFlyTE_;
	Math::Power* pWalkFlyPP_ = nullptr;
public:
	// ������
	void Initialize(Math::Mat4* pParent, Math::Power* pIdlePP, Math::Power* pWalkFlyPP);
	// ���Z�b�g
	void Reset(Trfm::Status state, Math::Vec3 pith, Math::Vec3 top);
	// �]���p���Z�b�g
	void ResetTransfer();
	// �X�V
	void Update();
	// �`��
	void Draw(Game::ViewProjection& vp, const UINT tex);
public:
	// �S�̃T�C�Y
	Math::Vec3 Size();
private:
	// �ÓI���f���|�C���^
	static Game::Model* pModel_;
public:
	// �ÓI������
	static void StaticInitialize(Game::Model* pModel);
};

