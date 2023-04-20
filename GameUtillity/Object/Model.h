#pragma once
#include "Mesh.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "ModelObject.h"

namespace YGame
{
	// ���f���N���X
	class Model
	{
	private:
		
		// ���b�V���z��
		std::vector<std::unique_ptr<Mesh>> meshes_;
		
		// ��\��
		bool isInvisible_ = false;

		// �t�@�C���p�X
		std::string fileName_;

	private:

		// �ÓI���f���i�[�pvector�z��
		static std::vector<std::unique_ptr<Model>> models_;

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
		/// ���f���ǂݍ���
		/// </summary>
		/// <param name="modelFileName"> : ���f���̃t�H���_�� (obj�Ɠ������O�̎��̂�) </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���f���|�C���^</returns>
		static Model* Load(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// �S�폜
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pObj"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(ModelObject* pObj);
		
		/// <summary>
		/// ��\���ݒ�
		/// </summary>
		/// <param name="isInvisible"> : ��\����</param>
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }

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
				LightCB		 = 2, // ��
				MaterialCB	 = 3, // �}�e���A��
				TexDT		 = 4, // �e�N�X�`��
			};

		private:

			// �V�F�[�_�[�Z�b�g
			class ShaderSet : public YDX::IShaderSet
			{
			public:
				
				// ���_�V�F�[�_�I�u�W�F�N�g
				Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
				
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
		
		Model() = default;

		~Model() = default;
	};
}
