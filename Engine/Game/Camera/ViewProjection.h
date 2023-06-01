#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	// �r���[�v���W�F�N�V����
	struct ViewProjection
	{
	
	public:
		
		// ���_
		YMath::Vector3 eye_;
		
		// �����_
		YMath::Vector3 target_;
		
		// ������x�N�g��
		YMath::Vector3 up_;
		
		// �r���[�s��
		YMath::Matrix4 view_;
		
		// �v���W�F�N�V�����s��
		YMath::Matrix4 pro_;
	
	public:
		
		// �ݒ�p�X�e�[�^�X(���_�A�����_�A������x�N�g��)
		struct Status
		{

		public:

			// ���_
			YMath::Vector3 eye_;
			
			// �����_
			YMath::Vector3 target_;
			
			// ������x�N�g��
			YMath::Vector3 up_;

		public:

			// �f�t�H���g�l
			static Status Default();
		};

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �������p�X�e�[�^�X</param>
		/// <param name="------------------------------------"></param>
		/// <param name="status.eye_"> : ���_</param>
		/// <param name="status.target_"> : �����_</param>
		/// <param name="status.up_"> : ������x�N�g��</param>
		void Initialize(const Status& status = Status::Default());
		
		// �r���[�ϊ� + �v���W�F�N�V�����ϊ�
		void UpdateMatrix();
	
	public:
		
		// �R���X�g���N�^
		ViewProjection();
	
	};
}