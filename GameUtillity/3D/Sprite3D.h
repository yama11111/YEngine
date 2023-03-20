#pragma once
#include "Sprite3DCommon.h"
#include "Vertices.h"
#include "BaseObject.h"
#include "ViewProjection.h"
#include "Color.h"

namespace YGame
{
	// �X�v���C�g3D�p�I�u�W�F�N�g
	class ObjectSprite3D : public BaseObject
	{
	public:
		// �萔�o�b�t�@
		YDX::ConstBuffer<Sprite3DCommon::CBData> cBuff_;
	public:
		/// <summary>
		/// ���� + ������
		/// </summary>
		/// <param name="state"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) state.pos_"> : �ʒu</param>
		/// <param name="(Vector3) state.rota_"> : ��]</param>
		/// <param name="(Vector3) state.scale_"> : �傫��</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static ObjectSprite3D* Create(const Status& state);
	private:
		ObjectSprite3D() = default;
	public:
		~ObjectSprite3D() override = default;
	};

	// �X�v���C�g3D�N���X
	class Sprite3D : private Sprite3DCommon
	{
	private:
		// ���_�f�[�^
		YDX::Vertices<VData> vt_;
		// �F
		std::unique_ptr<Color> defColor_;

		// X���r���{�[�h
		bool isXAxisBillboard_ = false;
		// Y���r���{�[�h
		bool isYAxisBillboard_ = false;

		// �e�N�X�`��
		UINT tex_ = UINT32_MAX;

		// ��\��
		bool isInvisible_ = false;
	public:
		// �r���{�[�h�ݒ�p�X�e�[�^�X
		struct Status
		{
			bool isXAxisBillboard_ = false; // X���r���{�[�h
			bool isYAxisBillboard_ = false; // Y���r���{�[�h
		};
	public:
		/// <summary>
		/// ����
		/// </summary>
		/// <param name="state"> : �r���{�[�h�ݒ�p�X�e�[�^�X</param>
		/// <param name="(bool) state.isXAxisBillboard_"> : X���r���{�[�h</param>
		/// <param name="(bool) state.isYAxisBillboard_"> : Y���r���{�[�h</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texIndex"> : �e�N�X�`���C���f�b�N�X</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite3D* Create(const Status& state, const UINT texIndex);
	public:
		/// <summary>
		/// �`�� (�e�N�X�`�� + �F �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="tex"> : �e�N�X�`���C���f�b�N�X</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor, const UINT tex);
		/// <summary>
		/// �`�� (�e�N�X�`�� �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		/// <param name="tex"> : �e�N�X�`���C���f�b�N�X</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp, const UINT tex);
		/// <summary>
		/// �`�� (�F �L)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor);
		/// <summary>
		/// �`�� (�f�t�H���g)
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="vp"> : �r���[�v���W�F�N�V����</param>
		void Draw(ObjectSprite3D* pObj, const ViewProjection& vp);
	private:
		// �r���{�[�h�s��v�Z
		YMath::Matrix4 BillboardMatrix(const ViewProjection& vp);
	private:
		Sprite3D() = default;
	public:
		~Sprite3D() = default;
	};
}
