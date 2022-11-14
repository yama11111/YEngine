#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class EWing
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
private:
	// �j
	Trfm core_;
	// �œ_
	Math::Vec3 focus_;
	// �H
	Trfm blade1_[3];
	Trfm blade2_[3];
private:
	// �������[�V����
	Math::Ease<Math::Vec3> idlePE_;
	Math::Ease<Math::Vec3> idleFE_;
	Math::Power* pIdlePP_ = nullptr;
	// ���胂�[�V����
	Math::Power* pWalkFlyPP_ = nullptr;
public:
	// ������
	void Initialize(Math::Mat4* pParent, Math::Power* pIdlePP, Math::Power* pWalkFlyPP);
	// ���Z�b�g
	void Reset(Trfm::Status state);
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

