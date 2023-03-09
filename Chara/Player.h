#pragma once
#include "Keys.h"
#include "Character.h"
#include "Sprite2D.h"

class Player : public Character
{
private:
	// �W�����v��
	int jumpCount_ = 0;
public:
	// ������
	void Initialize(const YGame::BaseObject::Status& state);
	// ���Z�b�g
	void Reset(const YGame::BaseObject::Status& state);
	// �X�V
	void Update();
	// �`��
	void Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup);
	// 2D�`��
	void Draw2D();
private:
	// �W�����v
	void Jump();
	// �ړ��A�b�v�f�[�g
	void UpdateMove();
public:
	// �ʒu�|�C���^�擾
	YMath::Vector3* PosPointer() { return &obj_->pos_; }
private:
	// �ÓI���f���|�C���^
	static YGame::Model* pModel_;
	// �ÓI�e�N�X�`���C���f�b�N�X
	static UINT tex_;
	// 
	static YInput::Keys* keys_;
public:
	// �ÓI�������X�e�[�^�X
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// ���f���|�C���^
		UINT tex_; // �e�N�X�`���C���f�b�N�X
	};
public:
	// �ÓI������
	static void StaticIntialize(const StaticInitStatus& state);
};

