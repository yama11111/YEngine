#pragma once
#include "Model.h"
#include "Collider.h"
#include "Keys.h"

class Player : Collision::Collider
{
private:
	// �I�u�W�F�N�g
	Game::Object obj_;

	// �L�[
	Input::Keys* keys = nullptr;
public:
	// ������
	void Initialize();
	// ���Z�b�g
	void Reset();
	// �Փˎ�����
	void OnCollision(const uint32_t attribute) override;
	// �X�V
	void Update();
	// �`��
	void Draw(const Game::ViewProjection& vp);
private:
	// �W�����v
	void Jump();
public:
	// �ʒu�擾
	Math::Vec3 Pos() override { return obj_.pos_; };
private:
	// �ÓI���f���|�C���^
	static Game::Model* model_;
	// �ÓI�e�N�X�`���C���f�b�N�X
	static UINT tex_;
public:
	// �ÓI�������X�e�[�^�X
	struct StaticInitStatus
	{
		Game::Model* model_;// ���f���|�C���^
		UINT tex_;// �e�N�X�`���C���f�b�N�X
	};
public:
	// �ÓI������
	static void StaticIntialize(const StaticInitStatus& state);
};

