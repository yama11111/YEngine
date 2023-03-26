#pragma once
#include "Model.h"
#include <vector>

namespace YGame
{
	class Floor
	{
	private:
		// �I�u�W�F�N�g
		std::vector<std::vector<std::unique_ptr<ModelObject>>> objs_;
		// ���f���|�C���^
		YGame::Model* pModel_ = nullptr;
	public:
		// �������X�e�[�^�X
		struct InitStatus
		{
			size_t xNum_; // X�� ����
			size_t yNum_; // Y�� ����
			YMath::Vector3 pos_; // �ꏊ (���S)
			YMath::Vector3 scale_; // �傫�� (1��)
			Model* pModel_; // ���f���|�C���^
		};
	public:
		// ������
		void Initialize(const InitStatus& status);
		// �X�V
		void Update();
		// �`��
		void Draw();
	};
}
