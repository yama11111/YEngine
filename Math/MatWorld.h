#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Math
{
	struct MatWorld
	{
	public:
		// �]���p�s��
		Mat4 m_;
		// �ʒu
		Vec3 pos_;
		// �p�x
		Vec3 rota_;
		// �傫��
		Vec3 scale_;
	public:
		// �������p�X�e�[�^�X
		struct InitStatus
		{
			Vec3 pos_ = { 0.0f, 0.0f, 0.0f };
			Vec3 rota_ = { 0.0f, 0.0f, 0.0f };
			Vec3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// �R���X�g���N�^
		MatWorld();
		// �R���X�g���N�^ (�����L)
		MatWorld(const InitStatus& init);
		// ������
		void Initialize(const InitStatus& init);
		// �A�t�B���ϊ� �� �]���p�s��ɑ��
		void Update();
	};
}
