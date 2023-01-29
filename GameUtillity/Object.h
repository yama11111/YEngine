#pragma once
#include "ConstBuffer.h"
#include "Vec3.h"
#include "Mat4.h"

namespace YGame
{
	template<typename T>
	class Object
	{
	public:
		// �ʒu
		YMath::Vec3 pos_;
		// ��]
		YMath::Vec3 rota_;
		// �傫��
		YMath::Vec3 scale_;
		// �s��
		YMath::Mat4 m_;
		// �e�s��
		YMath::Mat4* parent_;
		// �萔�o�b�t�@
		YDX::ConstBuffer<T> cBuff_;
	public:
		// �ݒ�p�X�e�[�^�X(�ʒu�A��]�A�傫��)
		struct Status
		{
			YMath::Vec3 pos_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 rota_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// ������
		void Initialize(const Status& state);
		// �A�t�B���ϊ�
		void UpdateMatrix();
		// �A�t�B���ϊ� (���o�p)
		void UpdateMatrix(const Status& state);
	public:
		// �R���X�g���N�^
		Object();
		// �f�X�g���N�^
		~Object() = default;
	};
}
