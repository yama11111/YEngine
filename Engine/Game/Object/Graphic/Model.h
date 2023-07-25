#pragma once
#include "BaseGraphic.h"
#include "Mesh.h"
#include "PipelineSetting.h"

namespace YGame
{
	// ���f��
	class Model :
		public BaseGraphic
	{

	public:

		/// <summary>
		/// ����(������)
		/// </summary>
		/// <param name="pTexs"> : �e�N�X�`���|�C���^�z��</param>
		/// <returns>���f���|�C���^</returns>
		static Model* CreateCube(const std::unordered_map<std::string, Texture*>& pTexs);

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

		/// <summary>
		/// ���f���p�̃p�C�v���C���ݒ�擾
		/// </summary>
		/// <returns>�p�C�v���C���ݒ�</returns>
		static PipelineSetting GetPipelineSetting();

	public:

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rpIndices"> : ���[�g�p�����[�^��� + �ԍ�</param>
		void SetDrawCommand(std::unordered_map<std::string, uint32_t>& rpIndices) override;

	public:

		Model() = default;

		~Model() = default;

	private:

		// ���b�V���z��
		std::vector<std::unique_ptr<Mesh>> meshes_;

		// �m�[�h�z��
		std::vector<std::unique_ptr<Node>> nodes_;
	
	private:

		// �ÓI���f���i�[�pvector�z��
		static std::vector<std::unique_ptr<Model>> sModels_;
	
	public:

		// FBX�ǂݍ��݃N���X�O���錾
		class FbxLoader;
	};

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
}
