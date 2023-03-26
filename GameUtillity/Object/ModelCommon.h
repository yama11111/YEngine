#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "Material.h"
#include "ViewProjection.h"
#include "LightGroup.h"
#include "Color.h"
#include <unordered_map>
#include <memory>

// include���p
struct aiMesh;

namespace YGame
{
	// ���f���p�I�u�W�F�N�g�R�����N���X
	class ModelObjectCommon
	{
	protected:
		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Matrix4 matWorld_;	 // ���[���h�s��
			YMath::Matrix4 matViewProj_; // �r���[�v���W�F�N�V�����s��
			YMath::Vector3 cameraPos_;	 // �J�������W
		};
	protected:
		// �r���[�v���W�F�N�V�����|�C���^ (�f�t�H���g)
		static std::unique_ptr<ViewProjection> sDefVP_;
		// �����|�C���^ (�f�t�H���g)
		static std::unique_ptr<LightGroup> sDefLightGroup_;
		// �F (�f�t�H���g)
		static std::unique_ptr<Color> sDefColor_;
	public:
		// �ÓI������ (�f�t�H���g�l�ݒ�)
		static void StaticInitialize();
	};

	// ���f���R�����N���X
	class ModelCommon
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
		// ���b�V���\����
		struct Mesh
		{
			// ���_�C���f�b�N�X�z��
			YDX::VertexIndex<VData> vtIdx_;
			// ���_�@���X���[�V���O�p�f�[�^
			std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData_;
			// �}�e���A��
			Material mtrl_;
		};
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
		class ShaderSet : public YDX::ShaderCommon
		{
		public:
			// ���_�V�F�[�_�I�u�W�F�N�g
			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
			// �s�N�Z���V�F�[�_�I�u�W�F�N�g
			Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
		public:
			// �V�F�[�_�[�t�@�C���ǂݍ���
			void Load(ID3DBlob* errorBlob);
		};
		// �p�C�v���C���ݒ�\����
		struct PipelineSetStatus : public YDX::PipelineSet::IStatus
		{
			// ������
			void Initialize(ID3DBlob* errorBlob_) override;
		};
	protected:
		// �@���v�Z
		static void CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t> indices);
		// �@���v�Z (�X���[�V���O)
		static void CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
			std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData);
		// ���_���ǂݍ���(assimp)
		static YDX::VertexIndex<VData> LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized);
	protected:
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet sPipelineSet_;
	public:
		// �ÓI������
		static void StaticInitialize();
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}

