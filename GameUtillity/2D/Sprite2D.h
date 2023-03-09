#pragma once
#include "Sprite2DCommon.h"
#include "Vertices.h"
#include "BaseObject.h"
#include "Color.h"

namespace YGame
{
	// �X�v���C�g2D�p�I�u�W�F�N�g
	class ObjectSprite2D : public BaseObject
	{
	public:
		// �萔�o�b�t�@
		YDX::ConstBuffer<Sprite2DCommon::CBData> cBuff_;
	public:
		// ����
		static ObjectSprite2D* Create(const Status& state);
	private:
		ObjectSprite2D() = default;
	public:
		~ObjectSprite2D() override = default;
	};

	// �X�v���C�g2D�N���X
	class Sprite2D : private Sprite2DCommon
	{
	private:
		// ���_�f�[�^
		YDX::Vertices<VData> vt_;
		// �F
		std::unique_ptr<Color> defColor_;

		// �T�C�Y
		YMath::Vector2 size_;
		// �A���J�[�|�C���g
		YMath::Vector2 anchor_;
		// ���E���]
		bool isFlipX_ = false;
		// �㉺���]
		bool isFlipY_ = false;

		// �e�N�X�`��
		UINT tex_ = UINT32_MAX;
		// �e�N�X�`������
		YMath::Vector2 texLeftTop_;
		// �e�N�X�`���T�C�Y
		YMath::Vector2 texSize_;

		// ��\��
		bool isInvisible_ = false;
	public:
		// �ݒ�p�X�e�[�^�X
		struct Status
		{
			YMath::Vector2 size_; // �T�C�Y
			YMath::Vector2 anchor_ = { 0.0f, 0.0f }; // �A���J�[�|�C���g
			bool isFlipX_ = false; // ���E���]
			bool isFlipY_ = false; // �㉺���]
		};
		// �e�N�X�`���ݒ�p�X�e�[�^�X
		struct TexStatus
		{
			UINT index_ = UINT32_MAX; // �e�N�X�`���C���f�b�N�X
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // �e�N�X�`������
			YMath::Vector2 size_ = { 0.0f,0.0f }; // �e�N�X�`���T�C�Y
		};
	public:
		// ����
		static Sprite2D* Create(const Status& state, const TexStatus& texState, const bool div = false);
	public:
		// �`�� (�e�N�X�`�� + �F �L)
		void Draw(ObjectSprite2D* obj, Color* color, const UINT tex);
		// �`�� (�e�N�X�`�� �L)
		void Draw(ObjectSprite2D* obj, const UINT tex);
		// �`�� (�F �L)
		void Draw(ObjectSprite2D* obj, Color* color);
		// �`�� (�f�t�H���g)
		void Draw(ObjectSprite2D* obj);
	public:
		// �T�C�Y�ݒ�
		void SetSize(const YMath::Vector2& size);
		// �A���J�[�|�C���g�ݒ�
		void SetAnchorPoint(const YMath::Vector2& anchor);
		// �t���b�v�ݒ�
		void SetFrip(const bool isFlipX, const bool isFlipY);
		// �e�N�X�`������ݒ�
		void SetTextureLeftTop(const YMath::Vector2& leftTop, const bool adjust = true);
		// �e�N�X�`���T�C�Y�ݒ�
		void SetTextureSize(const YMath::Vector2& texSize);
		// �e�N�X�`����`�ݒ�
		void SetTextureRectangle(const YMath::Vector2& leftTop, const YMath::Vector2& texSize);
		// �S�ݒ�
		void SetAllStatus(const Status& state, const TexStatus& texState, const bool div = false);
		// ��\���ݒ�
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	public:
		// �T�C�Y�擾
		YMath::Vector2 Size() const { return size_; }
		// �A���J�[�|�C���g�擾
		YMath::Vector2 AnchorPoint() const { return anchor_; }
	private:
		Sprite2D() = default;
	public:
		~Sprite2D() = default;
	};
}
