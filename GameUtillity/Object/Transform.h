#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	class Transform
	{
	public:
		
		// �ʒu
		YMath::Vector3 pos_;
		
		// ��]
		YMath::Vector3 rota_;
		
		// �傫��
		YMath::Vector3 scale_;
		
		// �s��
		YMath::Matrix4 m_;
		
		// �e�s��
		YMath::Matrix4* parent_;
	
	public:
		
		// �ݒ�p�X�e�[�^�X(�ʒu�A��]�A�傫��)
		struct Status
		{
			YMath::Vector3 pos_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 rota_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 scale_ = { 1.0f, 1.0f, 1.0f };
		};

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		void Initialize(const Status& status);
		
		/// <summary>
		/// �A�t�B���ϊ�
		/// </summary>
		void UpdateMatrix();
		
		/// <summary>
		/// �A�t�B���ϊ� (�ʒu�A��]�A�傫�� �����Z�����I�u�W�F�N�g�ōs��v�Z)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		void UpdateMatrix(const Status& status);
	
	public:
		
		Transform();
		
		virtual ~Transform() = default;
	};
}
