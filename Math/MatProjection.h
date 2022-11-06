#pragma once
#include "Mat4.h"

namespace Math
{
	struct MatProjection
	{
	public:
		// �]���p�s��
		Mat4 m_;
	public:
		// �ˉe�ϊ���
		enum Projection
		{
			// ���s���e�ϊ�
			OrthoGraphic = 0,
			// �������e�ϊ�
			Perspective = 1,
		};
		// �R���X�g���N�^
		MatProjection(const int projection);
		// ������
		void Initialize(const int projection);
	};
}

