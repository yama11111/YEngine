#pragma once
#include "ConstBufferManager.h"
#include "MatWorld.h"

namespace Object
{
	class Transform
	{
	private:
		// �]���p�s��
		Math::MatWorld mw_;
		// �萔�o�b�t�@(�}�e���A��)
		DX::ConstBuffer<DX::MaterialData> cbMtrl_;
		// �萔�o�b�t�@(3D�ϊ��s��)
		DX::ConstBuffer<DX::TransformData> cbTrfm_;
		// �e�s��
		Math::MatWorld* parent_ = nullptr;
	public:
		// �R���X�g���N�^
		Transform();
		// �R���X�g���N�^(�����L)
		Transform(const Math::MatWorld::InitStatus& init, const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// ������
		void Initialize(const Math::MatWorld::InitStatus& init, const Math::Vec4& color = {1.0f,1.0f,1.0f,1.0f});
		// �A�t�B���ϊ����r���[�v���W�F�N�V�����ϊ����]��
		void Update();
		// ���o�p����ϊ�
		void UniqueUpdate(const Math::MatWorld::InitStatus& state);
		// �`��O�R�}���h
		void SetDrawCommand(const Math::Mat4& view, const Math::Mat4& projection);
	public:
		// �ʒu�ݒ�
		void SetPos(const Math::Vec3& pos) { mw_.pos_ = pos; }
		// �p�x�ݒ�
		void SetRota(const Math::Vec3& rota) { mw_.rota_ = rota; }
		// �傫���ݒ�
		void SetScale(const Math::Vec3& scale) { mw_.scale_ = scale; }
		// �e�s��ݒ�
		void SetParent(Math::MatWorld* parent);
		// �F�ݒ�
		void SetColor(const Math::Vec4& color) { cbMtrl_.map_->color_ = color; }
	private:
		// �ÓI�萔�o�b�t�@�}�l�[�W���[�|�C���^
		static DX::ConstBufferManager* pCBManager_;
	public:
		// �ÓI������
		static void StaticInitialize(DX::ConstBufferManager* pCBManager);
	};
}
