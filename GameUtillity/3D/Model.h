#pragma once
#include "Vertices.h"
#include "Material.h"
#include "PipelineSet.h"
#include "Object.h"
#include "ViewProjection.h"
#include "Vec2.h"

struct aiMesh;
struct aiMaterial;

namespace YGame
{
	class Model
	{
	public:
		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vec3 pos_;	  // xyz���W
			YMath::Vec3 normal_;  // �@���x�N�g��
			YMath::Vec2 uv_;	  // uv���W
			YMath::Vec3 tangent_; // �ڋ��
			YMath::Vec4 color_;	  // ���_�F
		};
		// ���b�V���\����
		struct Mesh
		{
			// ���_�C���f�b�N�X�z��
			YDX::VertexIndex<VData> vtIdx_;
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
			std::string directoryPath_;
			std::string modelFileName_;
			bool isInverseU_;
			bool isInverseV_;
			bool isNormalized_ = false;
			std::string extension_ = "";
		};
	public:
		// ����(������)
		static Model* Create();
		// ���f���ǂݍ���
		static Model* Load(const std::string& modelFileName);
		// ���f���ǂݍ���(assimp)
		static Model* Load(const LoadStatus& state);
	private:
		// �@���v�Z
		static void Normalized(std::vector<VData>& v, const std::vector<uint16_t> indices);
		// ���_���ǂݍ���(assimp)
		static YDX::VertexIndex<VData> LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized);
		// �}�e���A���ǂݍ���(assimp)
		static Material LoadMaterial(const std::string directoryPath, const aiMaterial* src, 
			const std::string extension);
		// �g���q�ϊ�
		static std::string ReplaceExtension(const std::string fileName, const std::string extention);
	public:
		// �`�� (�e�N�X�`���L)
		void Draw(Object& obj, const ViewProjection& vp, const UINT tex);
		// �`��
		void Draw(Object& obj, const ViewProjection& vp);
	private:
		// �R���X�g���N�^
		Model() = default;
	private:
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet pplnSet_;
	public:
		// �ÓI������
		static void StaticInitialize(std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
