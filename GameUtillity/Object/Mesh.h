#pragma once
#include "Vertices.h"
#include "Texture.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <unordered_map>
#include <string>
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

		// �e�N�X�`��
		Texture* pTex_;

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
		/// ���b�V���ǂݍ���
		/// </summary>
		/// <param name="directoryPath"> : �f�B���N�g���p�X </param>
		/// <param name="objFileName"> : obj�t�@�C���� </param>
		/// <param name="isSmoothing"> : �X���[�V���O���邩</param>
		/// <returns>���I�C���X�^���X (new ���ꂽ����)</returns>
		static Mesh* Load(const std::string& directoryPath, const std::string& objFileName, const bool isSmoothing);

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
		/// <param name="v"></param>
		/// <param name="indices"></param>
		static void CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t>& indices);

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

	private:

		Mesh() = default;

	public:

		~Mesh() = default;
	};
}

