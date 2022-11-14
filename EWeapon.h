#pragma once
#include "Model.h"

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
public:
	// ������
	void Initialize(Math::Mat4* pParent);
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

