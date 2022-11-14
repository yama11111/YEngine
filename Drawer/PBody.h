#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class PBody
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
	// ��
	Trfm body_;
	// ��
	Trfm ears_[2];
private:
	// �������[�V����
	Math::Ease<Math::Vec3> idlePE_;
	Math::Power* pIdlePP_ = nullptr;
	// �����U��q���[�V����
	Math::Ease<Math::Vec3> walkPendPE_;
	Math::Power* pWalkPendPP_ = nullptr;
public:
	// ������
	void Initialize(Math::Mat4* pParent, Math::Power* pIdlePP, Math::Power* pWalkPendPP);
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

