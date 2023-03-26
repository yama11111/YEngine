#pragma once
#include "Sprite3DCommon.h"
#include "Transform.h"

namespace YGame
{
	// �X�v���C�g3D�p�I�u�W�F�N�g�N���X
	class Sprite3DObject :
		public Transform, 
		private Sprite3DObjectCommon
	{
	private:
		// �萔�o�b�t�@ (�s��)
		YDX::ConstBuffer<Sprite3DObjectCommon::CBData> cBuff_;
		// �r���[�v���W�F�N�V�����|�C���^
		ViewProjection* pVP_ = nullptr;
		// �F�|�C���^
		Color* pColor_ = nullptr;

		// X���r���{�[�h
		bool isXAxisBillboard_ = false;
		// Y���r���{�[�h
		bool isYAxisBillboard_ = false;
	public:
		/// <summary>
		/// ���� + ������ (�f�t�H���g������)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="isXAxisBillboard"> : X���r���{�[�h��</param>
		/// <param name="isYAxisBillboard"> : Y���r���{�[�h��</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite3DObject* Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard);
		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="isXAxisBillboard"> : X���r���{�[�h��</param>
		/// <param name="isYAxisBillboard"> : Y���r���{�[�h��</param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite3DObject* Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard, 
			ViewProjection* pVP, Color* pColor);
	public:
		// �r���{�[�h�ݒ�
		void SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard);
		// �r���[�v���W�F�N�V�����ݒ� (null = Default)
		void SetViewProjection(ViewProjection* pVP);
		// �F�ݒ� (null = Default)
		void SetColor(Color* pColor);
	public:
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		// �r���{�[�h�s��v�Z
		YMath::Matrix4 BillboardMatrix();
	private:
		Sprite3DObject() = default;
	public:
		~Sprite3DObject() = default;
	};

	// �X�v���C�g3D�N���X
	class Sprite3D : private Sprite3DCommon
	{
	private:
		// ���_�f�[�^
		YDX::Vertices<VData> vt_;

		// �e�N�X�`��
		UINT tex_ = UINT32_MAX;

		// ��\��
		bool isInvisible_ = false;
	public:
		/// <summary>
		/// ����
		/// </summary>
		/// <param name="texIndex"> : �e�N�X�`���C���f�b�N�X</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite3D* Create(const UINT texIndex);
	public:
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(Sprite3DObject* pObj);
	private:
		Sprite3D() = default;
	public:
		~Sprite3D() = default;
	};
}
