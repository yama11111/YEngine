#pragma once
#include "Model.h"
#include <vector>

class Floor
{
private:
	// �I�u�W�F�N�g
	std::vector<std::vector<YGame::ObjectModel>> objs;
public:
	struct InitStatus
	{
		size_t xNum_; // X�� ����
		size_t yNum_; // Y�� ����
		YMath::Vec3 pos_;// �ꏊ (���S)
		YMath::Vec3 scale_;// �傫�� (1��)
	};
public:
	// ������
	void Initialize(const InitStatus& state);
	// �X�V
	void Update();
	// �`��
	void Draw(const YGame::ViewProjection& vp);
private:
	// �ÓI���f���|�C���^
	static YGame::Model* pModel_;
	// �ÓI�e�N�X�`���C���f�b�N�X
	static UINT tex_;
public:
	// �ÓI�������X�e�[�^�X
	struct StaticInitStatus
	{
		YGame::Model* pModel_;// ���f���|�C���^
		UINT tex_;// �e�N�X�`���C���f�b�N�X
	};
public:
	// �ÓI������
	static void StaticIntialize(const StaticInitStatus& state);
};