#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	template<typename T>
	class Object
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
		// �萔�o�b�t�@
		YDX::ConstBuffer<T> cBuff_;
	public:
		// �ݒ�p�X�e�[�^�X(�ʒu�A��]�A�傫��)
		struct Status
		{
			YMath::Vector3 pos_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 rota_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// ����
		static Object<T>* Create(const Status& state);
	public:
		// ������
		void Initialize(const Status& state);
		// �A�t�B���ϊ�
		void UpdateMatrix();
		// �A�t�B���ϊ� (���o�p)
		void UpdateMatrix(const Status& state);
	public:
		Object();
	public:
		~Object() = default;
	};
}
