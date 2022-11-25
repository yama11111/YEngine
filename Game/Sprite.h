#pragma once
#include "Vertices.h"
#include "PipelineSet.h"
#include "Object.h"
#include "TextureManager.h"

namespace Game
{
	class Sprite
	{
	private:
		// ���_�f�[�^
		DX::Vertices<DX::SpriteVData> vt_;
		// �e�N�X�`��
		UINT tex_ = -1;
		// �T�C�Y
		Math::Vec2 size_;
		// �A���J�[�|�C���g
		Math::Vec2 anchor_;
		// ���E���]
		bool isFlipX_ = false;
		// �㉺���]
		bool isFlipY_ = false;
		// ��\��
		bool isInvisible_ = false;
	public:
		// �ݒ�p�X�e�[�^�X
		struct Status
		{
			Math::Vec2 size; // �T�C�Y
			Math::Vec2 anchor = { 0.0f, 0.0f }; // �A���J�[�|�C���g
			bool isFlipX = false; // ���E���]
			bool isFlipY = false; // �㉺���]
		};
	public:
		// ����
		static Sprite* Create(const Status& state, const UINT tex);
	public:
		// �`��
		void Draw(Object& obj, const UINT tex);
		void Draw(Object& obj);
	public:
		// �T�C�Y�ݒ�
		void SetSize(const Math::Vec2& size);
		// �A���J�[�|�C���g�ݒ�
		void SetAnchorPoint(const Math::Vec2& anchor);
		// �t���b�v�ݒ�
		void SetFrip(const bool isFlipX, const bool isFlipY);
		// �S�ݒ�
		void SetStatus(const Status& state);
		// ��\���ݒ�
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	public:
		// �T�C�Y�擾
		Math::Vec2 Size() const { return size_; }
		// �A���J�[�|�C���g�擾
		Math::Vec2 AnchorPoint() const { return anchor_; }
	private:
		// �R���X�g���N�^
		Sprite() = default;
	private:
		// �ÓI�ˉe�ϊ��s��(���s���e)
		static Math::Mat4 projection_;
		// �p�C�v���C���ݒ�
		static DX::PipelineSet pplnSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
