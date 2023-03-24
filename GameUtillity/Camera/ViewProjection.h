#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	// �r���[�v���W�F�N�V����
	class ViewProjection
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
		// �������p�X�e�[�^�X(���_�A�����_�A������x�N�g��)
		struct InitStatus
		{
			YMath::Vector3 eye_ = { 0.0f, 0.0f, -100.0f };
			YMath::Vector3 target_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 up_ = { 0.0f, 1.0f, 0.0f };
		};
	public:
		// �R���X�g���N�^
		ViewProjection();
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="state"> : �������p�X�e�[�^�X</param>
		/// <param name="------------------------------------"></param>
		/// <param name="state.eye_"> : ���_</param>
		/// <param name="state.target_"> : �����_</param>
		/// <param name="state.up_"> : ������x�N�g��</param>
		void Initialize(const InitStatus& state);
		// �r���[�ϊ� + �v���W�F�N�V�����ϊ�
		void Update();
	};
}