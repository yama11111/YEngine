#pragma once
#include "Model.h"

namespace YGame
{
	class Skydome
	{
	private:
		// �I�u�W�F�N�g
		std::unique_ptr<ModelObject> obj_;
		// ���f���|�C���^
		YGame::Model* pModel_ = nullptr;
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���ݒ�p�X�e�[�^�X</param>
		/// <param name="status.pos_"> : �ʒu</param>
		/// <param name="status.rota_"> : ��]</param>
		/// <param name="status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------------"></param>
		/// <param name="pModel"> : </param>
		void Initialize(const Transform::Status status, YGame::Model* pModel);
		// �X�V
		void Update();
		// �`��
		void Draw();
	};
}
