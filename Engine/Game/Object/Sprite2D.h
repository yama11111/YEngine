#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Texture.h"
#include "ObjectConfig.h"
#include "Transform.h"
#include "CBColor.h"
#include "CBTexConfig.h"
#include <list>
#include <array>

namespace YGame
{
	// �X�v���C�g2D�N���X
	class Sprite2D
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

		// �ݒ�p�X�e�[�^�X
		struct Status
		{
			bool isDiv_ = true; // �摜�T�C�Y�ɍ��킹�邩
			YMath::Vector2 size_; // �T�C�Y
			YMath::Vector2 anchor_ = { 0.5f, 0.5f }; // �A���J�[�|�C���g
			bool isFlipX_ = false; // ���E���]
			bool isFlipY_ = false; // �㉺���]
		};

		// �e�N�X�`���ݒ�p�X�e�[�^�X
		struct TexStatus
		{
			Texture* pTex_; // �e�N�X�`���|�C���^
			bool isDiv_ = true; // �摜�T�C�Y�ɍ��킹�邩
			YMath::Vector2 leftTop_ = { 0.0f,0.0f }; // �e�N�X�`������
			YMath::Vector2 size_ = { 0.0f,0.0f }; // �e�N�X�`���T�C�Y
		};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="status"> : �X�v���C�g�ݒ�</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) status.size_"> : �傫��</param>
		/// <param name="(Vector2) status.anchor_"> : �A���J�[�|�C���g (�����l�͒��S)</param>
		/// <param name="(bool) status.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) status.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : �e�N�X�`���ݒ�</param>
		/// <param name="(Texture*) texStatus.pTex_"> : �e�N�X�`���|�C���^</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texStatus.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		/// <returns>�X�v���C�g�|�C���^</returns>
		static Sprite2D* Create(const Status& status, const TexStatus& texStatus);

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
		void SetDrawCommand(Sprite2D::Object* pObj, const DrawLocation& location, const ShaderType& shaderType = ShaderType::eDefault);

		/// <summary>
		/// �X�v���C�g�T�C�Y�ݒ�
		/// </summary>
		/// <param name="size"> : �X�v���C�g�T�C�Y</param>
		void SetSize(const YMath::Vector2& size);

		/// <summary>
		/// �A���J�[�|�C���g�ݒ�
		/// </summary>
		/// <param name="anchor"> : �A���J�[�|�C���g</param>
		void SetAnchorPoint(const YMath::Vector2& anchor);

		/// <summary>
		/// �t���b�v�ݒ�
		/// </summary>
		/// <param name="isFlipX"> : X���t���b�v</param>
		/// <param name="isFlipY"> : Y���t���b�v</param>
		void SetFrip(const bool isFlipX, const bool isFlipY);

		/// <summary>
		/// �e�N�X�`������ݒ�
		/// </summary>
		/// <param name="leftTop"> : ����</param>
		/// <param name="adjust"> : �������邩</param>
		void SetTextureLeftTop(const YMath::Vector2& leftTop, const bool adjust = true);

		/// <summary>
		/// �e�N�X�`���T�C�Y�ݒ�
		/// </summary>
		/// <param name="texSize"> : �e�N�X�`���T�C�Y</param>
		void SetTextureSize(const YMath::Vector2& texSize);

		/// <summary>
		/// �e�N�X�`����`�ݒ�
		/// </summary>
		/// <param name="leftTop"> : �e�N�X�`������</param>
		/// <param name="texSize"> : �e�N�X�`���T�C�Y</param>
		void SetTextureRectangle(const YMath::Vector2& leftTop, const YMath::Vector2& texSize);

		/// <summary>
		/// �S�ݒ�
		/// </summary>
		/// <param name="status"> : �X�v���C�g�ݒ�</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) status.size_"> : �傫��</param>
		/// <param name="(Vector2) status.anchor_"> : �A���J�[�|�C���g(���S)</param>
		/// <param name="(bool) status.isFlipX_"> : X���]���邩</param>
		/// <param name="(bool) status.isFlipY_"> : Y���]���邩</param>
		/// <param name="--------------------------------"></param>
		/// <param name="texStatus"> : �e�N�X�`���ݒ�</param>
		/// <param name="(UINT) texStatus.index_"> : �e�N�X�`���|�C���^</param>
		/// <param name="(bool) isDiv_"> : �摜�T�C�Y�ɍ��킹�邩</param>
		/// <param name="(Vector2) texStatus.leftTop_"> : �e�N�X�`������</param>
		/// <param name="(Vector2) texStatus.size_"> : �e�N�X�`���T�C�Y</param>
		/// <param name="--------------------------------"></param>
		void SetAllStatus(const Status& status, const TexStatus& texStatus);

		/// <summary>
		/// �\�����邩�ݒ�
		/// </summary>
		/// <param name="isVisible"> : �\�����邩</param>
		void SetIsVisible(const bool isVisible);

	public:

		/// <summary>
		/// �T�C�Y�擾
		/// </summary>
		/// <returns>�T�C�Y</returns>
		YMath::Vector2 Size() const { return size_; }

		/// <summary>
		/// �A���J�[�|�C���g�擾
		/// </summary>
		/// <returns>�A���J�[�|�C���g</returns>
		YMath::Vector2 AnchorPoint() const { return anchor_; }

	public:

		Sprite2D() = default;

		~Sprite2D() = default;

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


		// �T�C�Y
		YMath::Vector2 size_;

		// �A���J�[�|�C���g
		YMath::Vector2 anchor_;

		// ���E���]
		bool isFlipX_ = false;

		// �㉺���]
		bool isFlipY_ = false;


		// �e�N�X�`��
		Texture* pTex_ = nullptr;

		// �e�N�X�`������
		YMath::Vector2 texLeftTop_;

		// �e�N�X�`���T�C�Y
		YMath::Vector2 texSize_;

		// �\�����邩
		bool isVisible_ = true;

	private:

		// �ÓI�X�v���C�g2D�i�[�pvector�z��
		static std::vector<std::unique_ptr<Sprite2D>> sSprites_;
	
	public:

		// �p�C�v���C���N���X�O���錾
		class Pipeline;

	};


#pragma region Object

	// �X�v���C�g2D�p�I�u�W�F�N�g�N���X
	class Sprite2D::Object : public Transform
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
	class Sprite2D::Pipeline
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
			Sprite2D* pSprite3D, 
			Sprite2D::Object* pObj, 
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

			// �X�v���C�g2D�|�C���^
			Sprite2D* pSprite2D_;

			// �X�v���C�g2D�p�I�u�W�F�N�g
			Sprite2D::Object* pObj_;

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
