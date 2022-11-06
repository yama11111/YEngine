#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Math
{
	struct MatView
	{
	public:
		// �]���p�s��
		Mat4 m_;
		// ���_
		Vec3 eye_;
		// �����_
		Vec3 target_;
		// ������x�N�g��
		Vec3 up_;
	public:
		// �������p�X�e�[�^�X
		struct InitStatus
		{
			Vec3 eye_ = { 0.0f, 0.0f, -100.0f };
			Vec3 target_ = { 0.0f, 0.0f, 0.0f };
			Vec3 up_ = { 0.0f, 1.0f, 0.0f };
		};
	public:
		// �R���X�g���N�^
		MatView();
		// �R���X�g���N�^ (�����L)
		MatView(const InitStatus& init);
		// ������
		void Initialize(const InitStatus& init);
		// �r���[�ϊ� �� �]���p�s��ɑ��
		void Update();
	};
}
