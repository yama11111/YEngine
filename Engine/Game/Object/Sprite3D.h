#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Texture.h"
#include "ObjectConfig.h"
#include "Transform.h"
#include "ViewProjection.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include <list>
#include <array>

namespace YGame
{

	// �X�v���C�g3D�N���X
	class Sprite3D
	{

	public:

		// �I�u�W�F�N�g�N���X�O���錾
		class Object;

		// �V�F�[�_�[�̎��
		enum class ShaderType
		{
			eDefault = 0, // �f�t�H���g
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="pTex"> : �e�N�X�`���|�C���^</param>
		/// <returns>�X�v���C�g�|�C���^</returns>
		static Sprite3D* Create(Texture* pTex);

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
		void SetDrawCommand(Sprite3D::Object* pObj, const DrawLocation& location, const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// �\�����邩�ݒ�
		/// </summary>
		/// <param name="isVisible"> : �\�����邩</param>
		void SetIsVisible(const bool isVisible);

	public:

		Sprite3D() = default;

		~Sprite3D() = default;

	public:

		// ���_�f�[�^
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
		};

	private:

		// �e�N�X�`��
		Texture* pTex_ = nullptr;

		// �\�����邩
		bool isVisible_ = true;

	private:

		// ���_�f�[�^
		static YDX::Vertices<VData> vt_;

		// �������t���O
		static bool isInitVertices_;

		// �ÓI�X�v���C�g3D�i�[�pvector�z��
		static std::vector<std::unique_ptr<Sprite3D>> sSprites_;

	public:

		// �p�C�v���C���N���X�O���錾
		class Pipeline;

	};

#pragma region Object

	// �X�v���C�g3D�p�I�u�W�F�N�g�N���X
	class Sprite3D::Object : public Transform
	{

	public:

		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ʒu, ��], �傫��</param>
		/// <param name="isXAxisBillboard"> : X���r���{�[�h��</param>
		/// <param name="isYAxisBillboard"> : Y���r���{�[�h��</param>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="pTexConfig"> : �e�N�X�`���ݒ�|�C���^</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Object* Create(
			const Status& status = Status::Default(),
			bool isXAxisBillboard = false, bool isYAxisBillboard = false,
			ViewProjection* pVP = nullptr,
			CBColor* pColor = nullptr, 
			CBTexConfig* pTexConfig = nullptr,
			const bool isMutable = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="texConfigRPIndex"> : �e�N�X�`���ݒ胋�[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(
			const UINT transformRPIndex, 
			const UINT colorRPIndex,
			const UINT texConfigRPIndex);


		/// <summary>
		/// �r���{�[�h�ݒ�
		/// </summary>
		/// <param name="isXAxisBillboard"> : X���r���{�[�h��</param>
		/// <param name="isYAxisBillboard"> : Y���r���{�[�h��</param>
		void SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard);
		
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
			YMath::Matrix4 matWorld_; // 3D�ϊ��s��
			YMath::Matrix4 matBill_; // �r���{�[�h�s��
		};

	private:

		// �萔�o�b�t�@ (�s��)
		YDX::ConstBuffer<CBData> cBuff_;

		// X���r���{�[�h
		bool isXAxisBillboard_ = false;

		// Y���r���{�[�h
		bool isYAxisBillboard_ = false;

		// �r���[�v���W�F�N�V�����|�C���^
		ViewProjection* pVP_ = nullptr;

		// �F�|�C���^
		CBColor* pColor_ = nullptr;

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
	class Sprite3D::Pipeline
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
		/// <param name="pSprite2D"> : �X�v���C�g�|�C���^</param>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="locaiton"> : �`��ꏊ</param>
		/// <param name="shaderType"> : �V�F�[�_�[</param>
		static void StaticPushBackDrawSet(
			Sprite3D* pSprite3D, 
			Sprite3D::Object* pObj, 
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
			eTexConfigCB = 2, // �e�N�X�`���ݒ�
			eTexDT		 = 3, // �e�N�X�`��
		};

	private:

		// �V�F�[�_�[�Z�b�g
		class ShaderSet : public YDX::IShaderSet
		{

		public:

			// DefaultVS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultVSBlob_ = nullptr;

			// DefaultGS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultGSBlob_ = nullptr;
			
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

			// �X�v���C�g3D�|�C���^
			Sprite3D* pSprite3D_;

			// �X�v���C�g3D�p�I�u�W�F�N�g
			Sprite3D::Object* pObj_;

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

}