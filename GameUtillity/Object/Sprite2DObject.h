#pragma once
#include "Transform.h"
#include "Color.h"
#include <memory>

namespace YGame
{
	// �X�v���C�g2D�p�I�u�W�F�N�g�N���X
	class Sprite2DObject : public Transform
	{
	private:
		
		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D�ϊ��s��
		};

	private:
		
		// �萔�o�b�t�@ (�s��)
		YDX::ConstBuffer<CBData> cBuff_;
		
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
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite2DObject* Create(const Status& status, const bool isMutable = true);
		
		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Sprite2DObject* Create(const Status& status, Color* pColor, const bool isMutable = true);
	
	public:
		
		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="colorRPIndex"></param>
		void SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex);
		
		
		/// <summary>
		/// �F�ݒ� (null = Default)
		/// </summary>
		/// <param name="pColor"> : �F�|�C���^</param>
		void SetColor(Color* pColor);
	
#pragma region Common

	public:

		// �R�����N���X
		class Common
		{
		public:

			// �ÓI�ˉe�ϊ��s��(���s���e)
			static YMath::Matrix4 sProjection_;

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
		
		Sprite2DObject() = default;
	
	public:
		
		~Sprite2DObject() = default;
	
	};
}
