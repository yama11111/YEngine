#pragma once
#include "ConstBuffer.h"
#include "Vec3.h"
#include "Mat4.h"

namespace Game
{
	class Object
	{
	public:
		// �s��
		Math::Mat4 m_;
		// �ʒu
		Math::Vec3 pos_;
		// ��]
		Math::Vec3 rota_;
		// �傫��
		Math::Vec3 scale_;
		// �F
		Math::Vec4 color_;
	private:
		// �萔�o�b�t�@(3D�ϊ��s��)
		DX::ConstBuffer<DX::TransformCBData> cbTrfm_;
		// �萔�o�b�t�@(�}�e���A��1)
		DX::ConstBuffer<DX::ColorCBData> cbColor_;
		// �e�s��
		Math::Mat4* parent_ = nullptr;
	public:
		// �ݒ�p�X�e�[�^�X(�ʒu�A��]�A�傫��)
		struct Status
		{
			Math::Vec3 pos_ = { 0.0f, 0.0f, 0.0f };
			Math::Vec3 rota_ = { 0.0f, 0.0f, 0.0f };
			Math::Vec3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// ������
		void Initialize(const Status& state, const Math::Vec4& color = {1.0f,1.0f,1.0f,1.0f});
		// �A�t�B���ϊ����r���[�v���W�F�N�V�����ϊ����]��
		void Update();
		// ���o�p����ϊ�
		void UniqueUpdate(const Status& state);
		// �`��O�R�}���h
		void SetDrawCommand(const Math::Mat4& view, const Math::Mat4& projection);
	public:
		// �e�s��ݒ�
		void SetParent(Math::Mat4* parent);
	public:
		// �R���X�g���N�^
		Object();
	};
}
