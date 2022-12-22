#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace YGame
{
	class ViewProjection
	{
	public:
		// ���_
		YMath::Vec3 eye_;
		// �����_
		YMath::Vec3 target_;
		// ������x�N�g��
		YMath::Vec3 up_;
		// �r���[�s��
		YMath::Mat4 view_;
		// �v���W�F�N�V�����s��
		YMath::Mat4 pro_;
	public:
		// �������p�X�e�[�^�X(���_�A�����_�A������x�N�g��)
		struct InitStatus
		{
			YMath::Vec3 eye_ = { 0.0f, 0.0f, -100.0f };
			YMath::Vec3 target_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 up_ = { 0.0f, 1.0f, 0.0f };
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