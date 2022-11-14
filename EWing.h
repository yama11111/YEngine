#pragma once
#include "Model.h"

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
	// �œ_
	Math::Vec3 focus_;
private:
	// �j
	Trfm core_;
	// �H
	Trfm blade1_[3];
	Trfm blade2_[3];
public:
	// ������
	void Initialize(Math::Mat4* pParent);
	// ���Z�b�g
	void Reset(Trfm::Status state, Math::Vec3 focus);
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

