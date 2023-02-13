#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
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
		// ������
		void Initialize(const InitStatus& state);
		// �r���[�ϊ� + �v���W�F�N�V�����ϊ�
		void Update();
	};
}