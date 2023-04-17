#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Color.h"
#include <memory>

namespace YGame
{
	// �X�v���C�g3D�p�I�u�W�F�N�g�N���X
	class Sprite3DObject : public Transform
	{
	private:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D�ϊ��s��
			YMath::Matrix4 matBill_; // �r���{�[�h�s��
		};

	private:
		
		// �萔�o�b�t�@ (�s��)
		YDX::ConstBuffer<CBData> cBuff_;
		
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
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite3DObject* Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard, const bool isMutable = true);
		
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
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite3DObject* Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard,
			ViewProjection* pVP, Color* pColor, const bool isMutable = true);
	
	public:
		
		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="colorRPIndex"></param>
		void SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex);

		
		/// <summary>
		/// �r���[�v���W�F�N�V�����ݒ� (null = Default)
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		void SetViewProjection(ViewProjection* pVP);
		
		/// <summary>
		/// �F�ݒ� (null = Default)
		/// </summary>
		/// <param name="pColor"> : �F�|�C���^</param>
		void SetColor(Color* pColor);

		/// <summary>
		/// �r���{�[�h�ݒ�
		/// </summary>
		/// <param name="isXAxisBillboard"> : X���r���{�[�h��</param>
		/// <param name="isYAxisBillboard"> : Y���r���{�[�h��</param>
		void SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard);
	
	private:
		
		/// <summary>
		/// �r���{�[�h�s��v�Z
		/// </summary>
		/// <returns>�r���{�[�h�s��</returns>
		YMath::Matrix4 BillboardMatrix();
	
#pragma region Common

	public:

		// �R�����N���X
		class Common
		{
		public:

			// �r���[�v���W�F�N�V�����|�C���^ (�f�t�H���g)
			static std::unique_ptr<ViewProjection> sDefVP_;
			
			// �F (�f�t�H���g)
			static std::unique_ptr<Color> sDefColor_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

		};

	private:

		// �R����
		static Common common_;

#pragma endregion

	private:
		
		Sprite3DObject() = default;
	
	public:
		
		~Sprite3DObject() = default;
	};
}

