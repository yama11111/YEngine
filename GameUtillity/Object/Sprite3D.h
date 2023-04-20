#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Sprite3DObject.h"
#include "Texture.h"

namespace YGame
{
	// �X�v���C�g3D�N���X
	class Sprite3D
	{
	public:
		
		// ���_�f�[�^
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
		};

	private:
		
		// ���_�f�[�^
		YDX::Vertices<VData> vt_;


		// �e�N�X�`��
		Texture* pTex_ = nullptr;

		// ��\��
		bool isInvisible_ = false;

	private:

		// �ÓI�X�v���C�g3D�i�[�pvector�z��
		static std::vector<std::unique_ptr<Sprite3D>> sprites_;

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
		/// �`��
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(Sprite3DObject* pObj);
	
#pragma region Pipeline

	public:

		// �p�C�v���C���N���X
		class Pipeline
		{

		public:

			// ���[�g�p�����[�^�ԍ�
			enum class RootParameterIndex
			{
				TransformCB	 = 0, // �s��
				ColorCB		 = 1, // �F
				TexDT		 = 2, // �e�N�X�`��
			};

		private:

			// �V�F�[�_�[�Z�b�g
			class ShaderSet : public YDX::IShaderSet
			{
			public:

				// ���_�V�F�[�_�I�u�W�F�N�g
				Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;

				// �W�I���g���V�F�[�_�I�u�W�F�N�g
				Microsoft::WRL::ComPtr<ID3DBlob> gsBlob_ = nullptr;

				// �s�N�Z���V�F�[�_�I�u�W�F�N�g
				Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;

			public:

				/// <summary>
				/// �V�F�[�_�[�t�@�C���ǂݍ���
				/// </summary>
				void Load() override;

			};

		protected:

			// �p�C�v���C���ݒ�
			static YDX::PipelineSet sPipelineSet_;

		public:

			/// <summary>
			/// �ÓI������
			/// </summary>
			static void StaticInitialize();

			/// <summary>
			/// �p�C�v���C���`��R�}���h
			/// </summary>
			static void StaticSetDrawCommond();

		};

#pragma endregion

	public:
		
		Sprite3D() = default;

		~Sprite3D() = default;
	
	};
}
