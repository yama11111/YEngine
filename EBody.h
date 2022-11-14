#pragma once
#include "Model.h"

class EBody
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
	// �p
	Trfm horn_;
	// ��
	Trfm ears1_[2];
	Trfm ears2_[2];
public:
	// ������
	void Initialize(Math::Mat4* pParent);
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

