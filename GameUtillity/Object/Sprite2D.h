#pragma once
#include "Sprite2DCommon.h"
#include "Transform.h"

namespace YGame
{
	// �X�v���C�g2D�p�I�u�W�F�N�g�N���X
	class Sprite2DObject :
		public Transform,
		private Sprite2DObjectCommon
	{
	private:
		// �萔�o�b�t�@ (�s��)
		YDX::ConstBuffer<Sprite2DObjectCommon::CBData> cBuff_;
		// �F�|�C���^
		Color* pColor_ = nullptr;
	public:
		/// <summary>
		/// ���� + ������ (�f�t�H���g������)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite2DObject* Create(const Status& status);
		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite2DObject* Create(const Status& status, Color* pColor);
	public:
		// �F�ݒ� (null = Default)
		void SetColor(Color* pColor);
	public:
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		Sprite2DObject() = default;
	public:
		~Sprite2DObject() override = default;
	};

	// �X�v���C�g2D�N���X
	class Sprite2D : private Sprite2DCommon
	{
	private:
		// ���_�f�[�^
		YDX::Vertices<VData> vt_;

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
			YMath::Vector2 anchor_ = { 0.5f, 0.5f }; // �A���J�[�|�C���g
			bool isFlipX_ = false; // ���E���]
			bool isFlipY_ = false; // �㉺���]
		};
		// �e�N�X�`���ݒ�p�X�e�[�^�X
		struct TexStatus
		{
			UINT index_; // �e�N�X�`���C���f�b�N�X
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // �e�N�X�`������
			YMath::Vector2 size_ = { 0.0f,0.0f }; // �e�N�X�`���T�C�Y
		};
	public:
		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �X�v���C�g�ݒ�</param>
		/// <param name="(Vector2) status.size_"> : �傫��</param>
		/// <param name="(Vector2) status.anchor_"> : �A���J�[�|�C���g (�����l�͒��S)</param>
		/// <param name="(bool) status.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) status.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : �e�N�X�`���ݒ�</param>
		/// <param name="(UINT) texStatus.index_"> : �e�N�X�`���C���f�b�N�X</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texStatus.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite2D* Create(const Status& status, const TexStatus& texStatus, const bool isDiv = false);
	public:
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(Sprite2DObject* pObj);
	public:
		// �X�v���C�g�T�C�Y�ݒ�
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
		/// <summary>
		/// �S�ݒ�
		/// </summary>
		/// <param name="status"> : �X�v���C�g�ݒ�</param>
		/// <param name="(Vector2) status.size_"> : �傫��</param>
		/// <param name="(Vector2) status.anchor_"> : �A���J�[�|�C���g(���S)</param>
		/// <param name="(bool) status.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) status.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : �e�N�X�`���ݒ�</param>
		/// <param name="(UINT) texStatus.index_"> : �e�N�X�`���C���f�b�N�X</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texStatus.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : �摜�T�C�Y�ɍ��킹�邩</param>
		void SetAllStatus(const Status& status, const TexStatus& texStatus, const bool isDiv = false);
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
