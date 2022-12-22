#pragma once
#include "ConstBuffer.h"
#include "Vec3.h"
#include "Mat4.h"

namespace YGame
{
	class Object
	{
	public:
		// �s��
		YMath::Mat4 m_;
		// �ʒu
		YMath::Vec3 pos_;
		// ��]
		YMath::Vec3 rota_;
		// �傫��
		YMath::Vec3 scale_;
		// �F
		YMath::Vec4 color_;
	private:
		// �萔�o�b�t�@(3D�ϊ��s��)
		YDX::ConstBuffer<YDX::TransformCBData> cbTrfm_;
		// �萔�o�b�t�@(�}�e���A��1)
		YDX::ConstBuffer<YDX::ColorCBData> cbColor_;
		// �e�s��
		YMath::Mat4* parent_ = nullptr;
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
		void Initialize(const Status& state, const YMath::Vec4& color = {1.0f,1.0f,1.0f,1.0f});
		// �A�t�B���ϊ����r���[�v���W�F�N�V�����ϊ����]��
		void Update();
		// ���o�p����ϊ�
		void UniqueUpdate(const Status& state);
		// �`��O�R�}���h
		void SetDrawCommand(const YMath::Mat4& view, const YMath::Mat4& projection);
	public:
		// �e�s��ݒ�
		void SetParent(YMath::Mat4* parent);
	public:
		// �R���X�g���N�^
		Object();
	};
}
