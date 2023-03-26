#pragma once
#include "ModelCommon.h"
#include "Transform.h"

namespace YGame
{
	// ���f���p�I�u�W�F�N�g�N���X
	class ModelObject :
		public Transform, 
		private ModelObjectCommon
	{
	private:
		// �萔�o�b�t�@ (�s��)
		YDX::ConstBuffer<ModelObjectCommon::CBData> cBuff_;
		// �r���[�v���W�F�N�V�����|�C���^
		ViewProjection* pVP_ = nullptr;
		// �F�|�C���^
		Color* pColor_ = nullptr;
		// �����|�C���^
		LightGroup* pLightGroup_ = nullptr;
	public:
		/// <summary>
		/// ���� + ������ (�f�t�H���g������)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static ModelObject* Create(const Status& status);
		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		/// <param name="-------------------------------------"></param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="pLightGroup"> : �����|�C���^</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static ModelObject* Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup);
	public:
		// �r���[�v���W�F�N�V�����ݒ� (null = Default)
		void SetViewProjection(ViewProjection* pVP);
		// �F�ݒ� (null = Default)
		void SetColor(Color* pColor);
		// ���C�g�O���[�v�ݒ� (null = Default)
		void SetLightGroup(LightGroup* pLightGroup);
	public:
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		ModelObject() = default;
	public:
		~ModelObject() override = default;
	};

	// ���f���N���X
	class Model : private ModelCommon
	{
	private:
		// ���b�V���z��
		std::vector<Mesh> meshes_;
		
		// ��\��
		bool isInvisible_ = false;
	public:
		// �ǂݍ��ݐݒ�\����
		struct LoadStatus
		{
			std::string directoryPath_;  // �f�B���N�g���p�X
			std::string modelFileName_;  // ���f����
			bool isSmoothing_ = false;   // �X���[�V���O���邩
			bool isInverseU_ = false;    // U���]�ݒ�
			bool isInverseV_ = true;     // V���]�ݒ�
			bool isNormalized_ = false;  // �@���v�Z���邩
			std::string extension_ = ""; // �g���q
		};
	public:
		// ����(������)
		static Model* Create();
		/// <summary>
		/// ���f���ǂݍ���
		/// </summary>
		/// <param name="modelFileName"> : ���f���̃t�H���_�� (obj�Ɠ������O�̎��̂�) </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);
		/// <summary>
		/// ���f���ǂݍ���(assimp)
		/// </summary>
		/// <param name="status"> �ǂݍ��ݐݒ�</param>
		/// <param name="(string) status.directoryPath_"> : �t�@�C���܂ł̃p�X��</param>
		/// <param name="(string) status.modelFileName_">  :���f���t�@�C����</param>
		/// <param name="(bool) status.isSmoothing_"> : �X���[�V���O���邩</param>
		/// <param name="(bool) status.isInverseU_"> : U���]�ݒ�</param>
		/// <param name="(bool) status.isInverseV_"> : V���]�ݒ�</param>
		/// <param name="(bool) status.isNormalized_"> : �@�����v�Z���邩</param>
		/// <param name="(string) status.extension_"> : �g���q</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Model* Load(const LoadStatus& status);
	public:
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(ModelObject* pObj);
	public:
		// ��\���ݒ�
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }
	private:
		Model() = default;
	public:
		~Model() = default;
	};
}
