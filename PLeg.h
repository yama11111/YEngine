#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"

class PLeg
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
	Trfm foot_;
	// ����
	Trfm ankle_;
private:
	// �������[�V����
	Math::Ease<Math::Vec3> walkPE_[2];
	Math::Ease<Math::Vec3> walkRE_[2];
	Math::Power* pWalkP_ = nullptr;
public:
	// ������
	void Initialize(Math::Mat4* pParent, Math::Power* pWalkP);
	// ���Z�b�g
	void Reset(Trfm::Status state);
	// �]���p���Z�b�g
	void ResetTransfer();
	// �X�V
	void Update(const bool isFB);
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

