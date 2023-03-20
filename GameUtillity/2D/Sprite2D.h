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
		/// <summary>
		/// ���� + ������
		/// </summary>
		/// <param name="state"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) state.pos_"> : �ʒu</param>
		/// <param name="(Vector3) state.rota_"> : ��]</param>
		/// <param name="(Vector3) state.scale_"> : �傫��</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
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
		/// <param name="state"> : �X�v���C�g�ݒ�</param>
		/// <param name="(Vector2) state.size_"> : �傫��</param>
		/// <param name="(Vector2) state.anchor_"> : �A���J�[�|�C���g (�����l�͒��S)</param>
		/// <param name="(bool) state.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) state.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texState"> : �e�N�X�`���ݒ�</param>
		/// <param name="(UINT) texState.index_"> : �e�N�X�`���C���f�b�N�X</param>
		/// <param name="(Vector2) texState.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texState.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite2D* Create(const Status& state, const TexStatus& texState, const bool isDiv = false);
	public:
		/// <summary>
		/// �`�� (�e�N�X�`�� + �F �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="tex"> : �e�N�X�`���C���f�b�N�X</param>
		void Draw(ObjectSprite2D* pObj, Color* pColor, const UINT tex);
		/// <summary>
		/// �`�� (�e�N�X�`�� �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="tex"> : �e�N�X�`���C���f�b�N�X</param>
		void Draw(ObjectSprite2D* pObj, const UINT tex);
		/// <summary>
		/// �`�� (�F �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		void Draw(ObjectSprite2D* pObj, Color* pColor);
		/// <summary>
		/// �`�� (�f�t�H���g)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(ObjectSprite2D* pObj);
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
		/// <param name="state"> : �X�v���C�g�ݒ�</param>
		/// <param name="(Vector2) state.size_"> : �傫��</param>
		/// <param name="(Vector2) state.anchor_"> : �A���J�[�|�C���g(���S)</param>
		/// <param name="(bool) state.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) state.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texState"> : �e�N�X�`���ݒ�</param>
		/// <param name="(UINT) texState.index_"> : �e�N�X�`���C���f�b�N�X</param>
		/// <param name="(Vector2) texState.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texState.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		/// <param name="isDiv"> : �摜�T�C�Y�ɍ��킹�邩</param>
		void SetAllStatus(const Status& state, const TexStatus& texState, const bool isDiv = false);
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
