#pragma once
#include "Vertices.h"
#include "Material.h"
#include "Vector2.h"
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
			YMath::Vector3 tangent_; // �ڋ��
			YMath::Vector4 color_;	 // ���_�F
		};

	private:
		
		// ���_�C���f�b�N�X�z��
		YDX::VertexIndex<VData> vtIdx_;

		// ���_�@���X���[�V���O�p�f�[�^
		std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData_;
		
		// �}�e���A��
		Material mtrl_;

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
		/// <param name="mateRPIndex"> : ���[�g�p�����[�^�ԍ�</param>
		/// <param name="texRPIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void Draw(UINT mateRPIndex, UINT texRPIndex);

	private:

		// �@���v�Z
		static void CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t>& indices);
		
		// �@���v�Z (�X���[�V���O)
		static void CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
			std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData);

	private:

		Mesh() = default;

	public:

		~Mesh() = default;
	};
}

