#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Texture.h"
#include "Transform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include "ScreenDesc.h"
#include <list>
#include <array>

namespace YGame
{
	// �|�X�g�G�t�F�N�g�N���X
	class PostEffect
	{

	public:

		// �I�u�W�F�N�g�N���X�O���錾
		class Object;

		// �V�F�[�_�[�̎��
		enum class ShaderType
		{
			eDefault		 = 0, // �f�t�H���g
			eColorInversion	 = 1, // �F���]
			eUVShiftBlur	 = 2, // ���ςڂ���
			eGaussianBlur	 = 3, // �K�E�X�ڂ���
			eBloom			 = 4, // �u���[��
			eEnd,
		};

	public:
		
		/// <summary>
		/// ����
		/// </summary>
		/// <returns>�|�X�g�G�t�F�N�g�|�C���^</returns>
		static PostEffect* Create();

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// �`��R�}���h
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="shaderType"> : �V�F�[�_�[</param>
		void SetDrawCommand(PostEffect::Object* pObj, const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// �������݊J�n
		/// </summary>
		void StartRender();

		/// <summary>
		/// �������ݏI��
		/// </summary>
		void EndRender();

		/// <summary>
		/// �\�����邩�ݒ�
		/// </summary>
		/// <param name="isVisible"> : �\�����邩</param>
		inline void SetIsVisible(const bool isVisible) { isVisible_ = isVisible; }

	public:

		PostEffect() = default;

		~PostEffect() = default;

	public:

		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
			YMath::Vector2 uv_;  // uv���W
		};

	private:

		// ���_�f�[�^
		YDX::Vertices<VData> vt_;

		// �e�N�X�`���̐�
		static const size_t kTextureNum_ = 2;

		// �e�N�X�`��
		std::array<Texture*, kTextureNum_> pTexs_;

		// �\�����邩
		bool isVisible_ = true;


		// RTV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;

		// DSV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;

		// �[�x�o�b�t�@
		YDX::GPUResource depthBuff_;


	private:

		// �ÓI�|�X�g�G�t�F�N�g�i�[�pvector�z��
		static std::vector<std::unique_ptr<PostEffect>> sPostEffects_;

	public:

		// �p�C�v���C���N���X�O���錾
		class Pipeline;

	private:

		void CreateRTV();

		void CreateDepthBuff(const YMath::Vector2& size);

		void CreateDSV();

	private:

		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* spDevice_;

		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* spCmdList_;

		// �ÓI�X�N���[���ݒ�|�C���^
		static YDX::ScreenDesc sScreenDesc_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pDevice"> : �f�o�C�X�|�C���^</param>
		/// <param name="pCmdList"> : �R�}���h���X�g�|�C���^</param>
		static void StaticInitialize(
			ID3D12Device* pDevice,
			ID3D12GraphicsCommandList* pCmdList);

	};


#pragma region Object

	// �X�v���C�g2D�p�I�u�W�F�N�g�N���X
	class PostEffect::Object : public Transform
	{

	public:

		/// <summary>
		/// ���� + ������ (Transform�ȊO�� null�̎� �f�t�H���g�ŏ�����)
		/// </summary>
		/// <param name="status"> : �ʒu, ��], �傫��</param>
		/// <param name="pColor"> : �F�|�C���^</param>
		/// <param name="pTexConfig"> : �e�N�X�`���ݒ�|�C���^</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static Object* Create(
			const Status& status = Status::Default(),
			CBColor* pColor = nullptr,
			CBTexConfig* pTexConfig = nullptr,
			const bool isMutable = true);

	public:

		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="transformRPIndex"> : �g�����X�t�H�[�����[�g�p�����[�^�ԍ�</param>
		/// <param name="colorRPIndex"> : �F���[�g�p�����[�^�ԍ�</param>
		/// <param name="texConfigRPIndex"> : �e�N�X�`���ݒ胋�[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(
			const UINT transformRPIndex,
			const UINT colorRPIndex,
			const UINT texConfigRPIndex);


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
		};

	private:

		// �萔�o�b�t�@ (�s��)
		YDX::ConstBuffer<CBData> cBuff_;

		// �F�|�C���^
		CBColor* pColor_ = nullptr;

		// �e�N�X�`���ݒ�|�C���^
		CBTexConfig* pTexConfig_ = nullptr;

	public:

		// ����l�N���X
		class Default
		{

		public:

			// �ÓI�ˉe�ϊ��s��(���s���e)
			static YMath::Matrix4 sProjection_;

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
	class PostEffect::Pipeline
	{

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// �ÓI�`�惊�X�g�N���A
		/// </summary>
		static void StaticClearDrawSet();

		/// <summary>
		/// �ÓI�`��Z�b�g�}��
		/// </summary>
		/// <param name="pPostEffect"> : �|�X�g�G�t�F�N�g�|�C���^</param>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		/// <param name="shaderType"> : �V�F�[�_�[</param>
		static void StaticPushBackDrawSet(
			PostEffect* pPostEffect, 
			PostEffect::Object* pObj,
			const ShaderType& shaderType);

		/// <summary>
		/// �ÓI�`��
		/// </summary>
		static void StaticDraw();

	public:

		// ���[�g�p�����[�^�ԍ�
		enum class RootParameterIndex
		{
			eTransformCB = 0, // �s��
			eColorCB	 = 1, // �F
			eTexConfigCB = 2, // �e�N�X�`���ݒ�
			eTex0DT		 = 3, // �e�N�X�`��0
			eTex1DT		 = 4, // �e�N�X�`��1
		};

	private:

		// �V�F�[�_�[�Z�b�g
		class ShaderSet : public YDX::IShaderSet
		{

		public:

			// DefaultVS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultVSBlob_ = nullptr;
		
		public:
			
			// DefaultPS
			Microsoft::WRL::ComPtr<ID3DBlob> defaultPSBlob_ = nullptr;

			//ColorInversionPS
			Microsoft::WRL::ComPtr<ID3DBlob> colorInversionPSBlob_ = nullptr;

			// UVShiftBlurPS
			Microsoft::WRL::ComPtr<ID3DBlob> uvShiftBlurPSBlob_ = nullptr;
			
			// GaussianPS
			Microsoft::WRL::ComPtr<ID3DBlob> gaussianBlurPSBlob_ = nullptr;

			// BloomPS
			Microsoft::WRL::ComPtr<ID3DBlob> bloomPSBlob_ = nullptr;

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

			// �|�X�g�G�t�F�N�g�|�C���^
			PostEffect* pPostEffect_;

			// �|�X�g�G�t�F�N�g�p�I�u�W�F�N�g
			PostEffect::Object* pObj_;

			// �p�C�v���C���C���f�b�N�X
			size_t pipelineIndex_;

		public:

			/// <summary> 
			/// �`��
			/// </summary>
			void Draw();

		};

	private:

		// �V�F�[�_�[�̐�
		static const size_t sShaderNum_ = static_cast<size_t>(ShaderType::eEnd);

		// �p�C�v���C���ݒ�
		static std::array<YDX::PipelineSet, sShaderNum_> sPipelineSets_;

		// �`��p���X�g�z��
		static std::list<std::unique_ptr<DrawSet>> sDrawSets_;

	};

#pragma endregion

}
