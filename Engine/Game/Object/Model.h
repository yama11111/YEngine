#pragma once
#include "Mesh.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "ObjectConfig.h"
#include "ViewProjection.h"
#include "CBColor.h"
#include "CBLightGroup.h"
#include "CBMaterial.h"
#include "CBTexConfig.h"

namespace YGame
{
	// ���f���N���X
	class Model
	{
	
	public:

		// �I�u�W�F�N�g�N���X�O���錾
		class Object;

		// �V�F�[�_�[�̎��
		enum class ShaderType
		{
			ePhong	 = 0, // Phong
			eToon	 = 1, // Toon
			eDefault = 2, // �f�t�H���g
		};

	public:

		/// <summary>
		/// ����(������)
		/// </summary>
		/// <returns>���f���|�C���^</returns>
		static Model* CreateCube();

		/// <summary>
		/// ����(������)
		/// </summary>
		/// <param name="texFileName"> : �摜�̃t�@�C����</param>
		/// <returns>���f���|�C���^</returns>
		static Model* CreateCube(const std::string& texFileName);

		/// <summary>
		/// ���f��(.obj)�ǂݍ���
		/// </summary>
		/// <param name="modelFileName"> : ���f���̃t�H���_�� (obj�Ɠ������O�̎��̂�) </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���f���|�C���^</returns>
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// ���f��(.obj)�ǂݍ���
		/// </summary>
		/// <param name="modelFileName"> : ���f���̃t�H���_�� (obj�Ɠ������O�̎��̂�) </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���f���|�C���^</returns>
		static Model* LoadFbx(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// �`��R�}���h
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="locaiton"> : �`��ꏊ</param>
		/// <param name="shaderType"> : �V�F�[�_�[</param>
		void SetDrawCommand(
			Model::Object* pObj, 
			const DrawLocation& location, 
			const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// �\�����邩�ݒ�
		/// </summary>
		/// <param name="isVisible"> : �\�����邩</param>
		void SetIsVisible(const bool isVisible);

	public:

		Model() = default;

		~Model() = default;

	private:

		// ���b�V���z��
		std::vector<std::unique_ptr<Mesh>> meshes_;

		// �m�[�h�z��
		std::vector<std::unique_ptr<Node>> nodes_;

		// �\�����邩
		bool isVisible_ = true;

		// �t�@�C���p�X
		std::string fileName_;

	private:

		// �ÓI���f���i�[�pvector�z��
		static std::vector<std::unique_ptr<Model>> sModels_;
	
	public:

		// �p�C�v���C���N���X�O���錾
		class Pipeline;

		// FBX�ǂݍ��݃N���X�O���錾
		class FbxLoader;

	};


#pragma region Object

	// ���f���p�I�u�W�F�N�g�N���X
	class Model::Object : public Transform
	{

	public:

		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ʒu, ��], �傫��</param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="pMaterial"> : �}�e���A���|�C���^</param>
		/// <param name="pLightGroup"> : �����|�C���^</param>
		/// <param name="pTexConfig"> : �e�N�X�`���ݒ�|�C���^</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Object* Create(
			const Status& status = Status::Default(),
			ViewProjection* pVP = nullptr,
			CBColor* pColor = nullptr,
			CBMaterial* pMaterial = nullptr,
			CBLightGroup* pLightGroup = nullptr,
			CBTexConfig* pTexConfig = nullptr,
			const bool isMutable = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="transformRPIndex"> : �g�����X�t�H�[�����[�g�p�����[�^�ԍ�</param>
		/// <param name="colorRPIndex"> : �F���[�g�p�����[�^�ԍ�</param>
		/// <param name="materialRPIndex"> : �}�e���A�����[�g�p�����[�^�ԍ�</param>
		/// <param name="lightRPIndex"> : ���C�g�O���[�v���[�g�p�����[�^�ԍ�</param>
		/// <param name="texConfigRPIndex"> : �e�N�X�`���ݒ胋�[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(
			const UINT transformRPIndex,
			const UINT colorRPIndex,
			const UINT materialRPIndex,
			const UINT lightRPIndex,
			const UINT texConfigRPIndex);


		/// <summary>
		/// �r���[�v���W�F�N�V�����ݒ� (null = Default)
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// �F�ݒ� (null = Default)
		/// </summary>
		/// <param name="pColor"> : �F�|�C���^</param>
		void SetColor(CBColor* pColor);

		/// <summary>
		/// �}�e���A���ݒ� (null = Default)
		/// </summary>
		/// <param name="pMaterial"> : �}�e���A���|�C���^</param>
		void SetMaterial(CBMaterial* pMaterial);

		/// <summary>
		/// �����ݒ� (null = Default)
		/// </summary>
		/// <param name="pLightGroup"> : �����|�C���^</param>
		void SetLightGroup(CBLightGroup* pLightGroup);

		/// <summary>
		/// �e�N�X�`���ݒ� (null = Default)
		/// </summary>
		/// <param name="pTexConfig"> : �e�N�X�`���ݒ�|�C���^</param>
		void SetTexConfig(CBTexConfig* pTexConfig);

	private:

		Object() = default;

	public:

		~Object() = default;


	private:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Matrix4 matWorld_;	 // ���[���h�s��
			YMath::Matrix4 matViewProj_; // �r���[�v���W�F�N�V�����s��
			YMath::Vector3 cameraPos_;	 // �J�������W
			float pad_;
		};

	private:

		// �萔�o�b�t�@
		YDX::ConstBuffer<CBData> cBuff_;

		// �r���[�v���W�F�N�V�����|�C���^
		ViewProjection* pVP_ = nullptr;

		// �F�|�C���^
		CBColor* pColor_ = nullptr;

		// �}�e���A���|�C���^
		CBMaterial* pMaterial_ = nullptr;

		// �����|�C���^
		CBLightGroup* pLightGroup_ = nullptr;

		// �e�N�X�`���ݒ�|�C���^
		CBTexConfig* pTexConfig_ = nullptr;

	public:

		// ����l�N���X
		class Default
		{

		public:

			// �r���[�v���W�F�N�V�����|�C���^ (�f�t�H���g)
			static std::unique_ptr<ViewProjection> sVP_;

			// �F (�f�t�H���g)
			static std::unique_ptr<CBColor> sColor_;

			// �}�e���A�� (�f�t�H���g)
			static std::unique_ptr<CBMaterial> sMaterial_;

			// �����|�C���^ (�f�t�H���g)
			static std::unique_ptr<CBLightGroup> sLightGroup_;

			// �e�N�X�`���ݒ� (�f�t�H���g)
			static std::unique_ptr<CBTexConfig> sTexConfig_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

		};

	};

#pragma endregion


#pragma region Pipeline

	// �p�C�v���C���N���X
	class Model::Pipeline
	{

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// �ÓI�`�惊�X�g�N���A
		/// </summary>
		/// <param name="locaiton"> : �`��ꏊ</param>
		static void StaticClearDrawSet(const DrawLocation& location);

		/// <summary>
		/// �ÓI�`��Z�b�g�}��
		/// </summary>
		/// <param name="pModel"> : ���f���|�C���^</param>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="locaiton"> : �`��ꏊ</param>
		static void StaticPushBackDrawSet(
			Model* pModel, 
			Model::Object* pObj, 
			const DrawLocation& location, 
			const ShaderType& shaderType);

		/// <summary>
		/// �ÓI�`��
		/// </summary>
		/// <param name="locaiton"> : �`��ꏊ</param>
		static void StaticDraw(const DrawLocation& location);

	public:

		// ���[�g�p�����[�^�ԍ�
		enum class RootParameterIndex
		{
			eTransformCB = 0, // �s��
			eColorCB	 = 1, // �F
			eMaterialCB	 = 2, // �}�e���A��
			eLightCB	 = 3, // ��
			eTexConfigCB = 4, // �e�N�X�`���ݒ�
			eTexDT		 = 5, // �e�N�X�`��
		};

	private:

		// �V�F�[�_�[�Z�b�g
		class ShaderSet : public YDX::IShaderSet
		{

		public:

			// PhongVS
			Microsoft::WRL::ComPtr<ID3DBlob> phongVSBlob_ = nullptr;

			// PhongPS
			Microsoft::WRL::ComPtr<ID3DBlob> phongPSBlob_ = nullptr;


			// ToonVS
			Microsoft::WRL::ComPtr<ID3DBlob> toonVSBlob_ = nullptr;

			// ToonPS
			Microsoft::WRL::ComPtr<ID3DBlob> toonPSBlob_ = nullptr;


			// DefaultVS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultVSBlob_ = nullptr;

			// DefaultPS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultPSBlob_ = nullptr;

		public:

			/// <summary>
			/// �V�F�[�_�[�t�@�C���ǂݍ���
			/// </summary>
			void Load() override;

		};

	public:

		// �`��Z�b�g
		struct DrawSet
		{

		public:

			// ���f���|�C���^
			Model* pModel_;

			// ���f���p�I�u�W�F�N�g
			Model::Object* pObj_;

		public:

			/// <summary> 
			/// �`��
			/// </summary>
			void Draw();

		};

	private:

		// �V�F�[�_�[�̐�
		static const size_t sShaderNum_ = static_cast<size_t>(ShaderType::eDefault) + 1;

		// �p�C�v���C���ݒ�
		static std::array<YDX::PipelineSet, sShaderNum_> sPipelineSets_;

		// �`��p���X�g�z��
		static std::array<std::array<std::list<std::unique_ptr<DrawSet>>, sShaderNum_>, DrawLocationNum> sDrawSets_;

	};

#pragma endregion


#pragma region FbxLoader

	// FBX�ǂݍ��݃N���X
	class Model::FbxLoader
	{

	public:

		// �ÓIFBX�}�l�[�W���[
		static FbxManager* sFbxMan_;

		// �ÓIFBX�C���|�[�^�[
		static FbxImporter* sFbxImp_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// �ÓI�I������
		/// </summary>
		static void StaticFinalize();

	public:

		/// <summary>
		/// �ċA�I�Ƀm�[�h�\�������
		/// </summary>
		/// <param name="pModel"> : ���f���|�C���^</param>
		/// <param name="fbxNode"> : ��͂���m�[�h</param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <param name="parent"> : �e�m�[�h</param>
		static void ParseNodeRecursive(Model* pModel, FbxNode* fbxNode, const bool isSmoothing, Node* parent = nullptr);

	};

#pragma endregion

}
