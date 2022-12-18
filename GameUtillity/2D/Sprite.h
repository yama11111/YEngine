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
		YDX::Vertices<YDX::SpriteVData> vt_;
		// �T�C�Y
		YMath::Vec2 size_;
		// �A���J�[�|�C���g
		YMath::Vec2 anchor_;
		// ���E���]
		bool isFlipX_ = false;
		// �㉺���]
		bool isFlipY_ = false;

		// �e�N�X�`��
		UINT tex_ = UINT32_MAX;
		// �e�N�X�`������
		YMath::Vec2 texLeftTop_;
		// �e�N�X�`���T�C�Y
		YMath::Vec2 texSize_;

		// ��\��
		bool isInvisible_ = false;
	public:
		// �ݒ�p�X�e�[�^�X
		struct Status
		{
			YMath::Vec2 size_; // �T�C�Y
			YMath::Vec2 anchor_ = { 0.0f, 0.0f }; // �A���J�[�|�C���g
			bool isFlipX_ = false; // ���E���]
			bool isFlipY_ = false; // �㉺���]
		};
		// �e�N�X�`���ݒ�p�X�e�[�^�X
		struct TexStatus
		{
			UINT index_ = UINT32_MAX; // �e�N�X�`���C���f�b�N�X
			YMath::Vec2 leftTop_ = { 0.0f,0.0f }; // �e�N�X�`������
			YMath::Vec2 size_ = { 0.0f,0.0f }; // �e�N�X�`���T�C�Y
		};
	public:
		// ����
		static Sprite* Create(const Status& state, const TexStatus& texState, const bool div = false);
	public:
		// �`��
		void Draw(Object& obj, const UINT tex);
		// �`��
		void Draw(Object& obj);
	public:
		// �T�C�Y�ݒ�
		void SetSize(const YMath::Vec2& size);
		// �A���J�[�|�C���g�ݒ�
		void SetAnchorPoint(const YMath::Vec2& anchor);
		// �t���b�v�ݒ�
		void SetFrip(const bool isFlipX, const bool isFlipY);
		// �e�N�X�`������ݒ�
		void SetTextureLeftTop(const YMath::Vec2& leftTop, const bool adjust = true);
		// �e�N�X�`���T�C�Y�ݒ�
		void SetTextureSize(const YMath::Vec2& texSize);
		// �e�N�X�`����`�ݒ�
		void SetTextureRectangle(const YMath::Vec2& leftTop, const YMath::Vec2& texSize);
		// �S�ݒ�
		void SetAllStatus(const Status& state, const TexStatus& texState, const bool div = false);
		// ��\���ݒ�
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	public:
		// �T�C�Y�擾
		YMath::Vec2 Size() const { return size_; }
		// �A���J�[�|�C���g�擾
		YMath::Vec2 AnchorPoint() const { return anchor_; }
	private:
		// �R���X�g���N�^
		Sprite() = default;
	private:
		// �ÓI�ˉe�ϊ��s��(���s���e)
		static YMath::Mat4 projection_;
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet pplnSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
