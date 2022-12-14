#pragma once
#include "Vertices.h"
#include "Material.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"

struct aiMesh;
struct aiMaterial;

namespace Game
{
	class Model
	{
	private:
		struct Mesh
		{
			// ���_�C���f�b�N�X�z��
			DX::VertexIndex3D vtIdx_;
			// �}�e���A��
			Material mtrl_;
		};
	private:
		// ���b�V���z��
		std::vector<Mesh> meshes_;
	public:
		// �ǂݍ��ݐݒ�\����
		struct LoadStatus 
		{
			std::string directoryPath;
			std::string modelFileName;
			bool isInverseU;
			bool isInverseV;
			std::string extension = "";
		};
	public:
		// ����(������)
		static Model* Create();
		// ���f���ǂݍ���
		static Model* Load(const std::string& modelFileName);
		// ���f���ǂݍ���(assimp)
		static Model* Load(const LoadStatus& state);
	private:
		// ���_���ǂݍ���(assimp)
		static DX::VertexIndex3D LoadVertices(const aiMesh* src, bool invU, bool invV);
		// �}�e���A���ǂݍ���(assimp)
		static Material LoadMaterial(const std::string directoryPath, const aiMaterial* src, 
			const std::string extension);
		// �g���q�ϊ�
		static std::string ReplaceExtension(const std::string fileName, const std::string extention);
	public:
		// �`��
		void Draw(Object& obj, const ViewProjection& vp, const UINT tex);
		void Draw(Object& obj, const ViewProjection& vp);
	private:
		// �R���X�g���N�^
		Model() = default;
	private:
		// �p�C�v���C���ݒ�
		static DX::PipelineSet pplnSet_;
	public:
		// �ÓI������
		static void StaticInitialize(std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
