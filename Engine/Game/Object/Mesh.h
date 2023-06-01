#pragma once
#include "Vertices.h"
#include "Texture.h"
#include "Node.h"
#include "Vector2.h"
#include "Vector4.h"
#include <fbxsdk.h>
#include <unordered_map>
#include <memory>

namespace YGame
{
	class Mesh
	{

	public:

		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vector3 pos_;	 // xyz���W
			YMath::Vector3 normal_;	 // �@���x�N�g��
			YMath::Vector2 uv_;		 // uv���W
			//YMath::Vector3 tangent_; // �ڋ��
			//YMath::Vector4 color_;	 // ���_�F
		};

	private:
		
		// ���_�C���f�b�N�X�z��
		YDX::VertexIndex<VData> vtIdx_;

		// ���_�@���X���[�V���O�p�f�[�^
		std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData_;

		// �m�[�h
		Node node_;

		// �e�N�X�`��
		Texture* pTex_ = nullptr;

	public:

		/// <summary>
		/// ����(������)
		/// </summary>
		/// <returns>���I�C���X�^���X (new ���ꂽ����)</returns>
		static Mesh* CreateCube();

		/// <summary>
		/// ����(������)
		/// </summary>
		/// <param name="texFileName"> : �摜�̃t�@�C����</param>
		/// <returns>���I�C���X�^���X (new ���ꂽ����)</returns>
		static Mesh* CreateCube(const std::string& texFileName);

		/// <summary>
		/// ���b�V��(.obj)�ǂݍ���
		/// </summary>
		/// <param name="directoryPath"> : �f�B���N�g���p�X </param>
		/// <param name="objFileName"> : obj�t�@�C���� </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���I�C���X�^���X (new ���ꂽ����)</returns>
		static Mesh* LoadObj(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing);

		/// <summary>
		/// ���b�V��(.fbx)�ǂݍ���
		/// </summary>
		/// <param name="folderPath"> : ���f���t�H���_�̃p�X</param>
		/// <param name="fbxNode"> :  FBX�m�[�h</param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���I�C���X�^���X (new ���ꂽ����)</returns>
		static Mesh* LoadFbx(const std::string& folderPath, FbxNode* fbxNode, const bool isSmoothing);

	public:

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="texRPIndex"> : �e�N�X�`���p���[�g�p�����[�^�ԍ�</param>
		void Draw(const UINT texRPIndex);

	private:

		/// <summary>
		/// �@���v�Z
		/// </summary>
		/// <param name="vertices"> : ���_�z��</param>
		/// <param name="indices"> : �C���f�b�N�X�z��</param>
		static void CalculateNormals(std::vector<VData>& vertices, const std::vector<uint16_t>& indices);

		/// <summary>
		/// �@���v�Z (�X���[�V���O)
		/// </summary>
		/// <param name="vertices"> : ���_�z��</param>
		/// <param name="smoothData"> : �ۑ��p�X���[�X�f�[�^</param>
		static void CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
			std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData);
		
		/// <summary>
		/// �}�e���A��(�e�N�X�`��)�ǂݍ���
		/// </summary>
		/// <param name="directoryPath"> : �f�B���N�g���p�X</param>
		/// <param name="fileName"> : �t�@�C����</param>
		/// <returns>�e�N�X�`���|�C���^</returns>
		static Texture* LoadMaterial(const std::string& directoryPath, const std::string& fileName);


#pragma region FbxLoader

	public:

		// FBX�ǂݍ��ݗp
		class FbxLoader
		{

		public:

			/// <summary>
			/// ���_�ǂݎ��
			/// </summary>
			/// <param name="vertices"> : ���_�z��</param>
			/// <param name="fbxNode"> : ��͂���m�[�h</param>
			static void ParseMeshVertices(std::vector<VData>& vertices, FbxMesh* fbxMesh);

			/// <summary>
			/// �ʓǂݎ��
			/// </summary>
			/// <param name="vertices"> : ���_�z��</param>
			/// <param name="indices"> : �C���f�b�N�X�z��</param>
			/// <param name="fbxMesh"> : ��͂��郁�b�V��</param>
			static void ParseMeshFaces(std::vector<VData>& vertices, std::vector<uint16_t>& indices, FbxMesh* fbxMesh);

			/// <summary>
			/// �}�e���A���ǂݎ��
			/// </summary>
			/// <param name="folderPath"> : ���f���t�H���_�̃p�X</param>
			/// <param name="refPtrTex"> : �Q�ƃe�N�X�`���|�C���^</param>
			/// <param name="fbxNode"> : ��͂���m�[�h</param>
			static void ParseMaterial(const std::string& folderPath, Texture*& refPtrTex, FbxNode* fbxNode);

		public:

			/// <summary>
			/// Fbx�p�̍s�񂩂�s��ɕϊ�
			/// </summary>
			/// <param name="fbxMat"> : Fbx�p�s��</param>
			/// <returns>�s��</returns>
			static YMath::Matrix4 ConvertFromFbxAMatrixToMatrix4(const FbxAMatrix& fbxMat);

		};

#pragma endregion


	private:

		Mesh() = default;

	public:

		~Mesh() = default;
	};
}

