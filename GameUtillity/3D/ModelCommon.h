#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Color.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Mat4.h"
#include <unordered_map>

struct aiMesh;
struct aiMaterial;

namespace YGame
{
	class ModelCommon
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
		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Mat4 matWorld_;	  // ���[���h�s��
			YMath::Mat4 matViewProj_; // �r���[�v���W�F�N�V�����s��
			YMath::Vec3 cameraPos_;	  // �J�������W
		};
		// �萔�o�b�t�@�f�[�^�\���� (�}�e���A��)
		struct MaterialCBData
		{
			YMath::Vec3 ambient_;  // �A���r�G���g�W��
			float pad1_; // �p�f�B���O1
			YMath::Vec3 diffuse_;  // �f�B�t���[�Y�W��
			float pad2_; // �p�f�B���O2
			YMath::Vec3 specular_; // �X�y�L�����[�W��
			float alpha_;		   // �A���t�@
		};
		// �}�e���A���\����
		struct Material
		{
		public:
			std::string name_;			 // �}�e���A����
			YMath::Vec3 ambient_;		 // �A���r�G���g�e���x
			YMath::Vec3 diffuse_;		 // �f�B�t���[�Y�e���x
			YMath::Vec3 specular_;		 // �X�y�L�����[�e���x
			float alpha_;				 // �A���t�@�l
		public:
			std::string texFileName_;	 // �e�N�X�`���t�@�C����
			UINT texIndex_;				 // �e�N�X�`���C���f�b�N�X
		public:
			YDX::ConstBuffer<MaterialCBData> cBuff_; // �萔�o�b�t�@(�}�e���A��2)
		public:
			Material(); // �R���X�g���N�^
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
			ModelCB,
			LightCB,
			ColorCB,
			MaterialCB,
			TexDT,
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
			void Initialize(ID3DBlob* errorBlob_) override;
		};
	protected:
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet pipelineSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI�������X�e�[�^�X
		struct StaticInitStatus
		{
			// �e�N�X�`���}�l�[�W���[�|�C���^
			TextureManager* pTexManager_;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	protected:
		// �@���v�Z
		static void CalculateNormals(std::vector<VData>& v, const std::vector<uint16_t> indices);
		// �@���v�Z (�X���[�V���O)
		static void CalculateSmoothedVertexNormals(std::vector<VData>& vertices,
			std::unordered_map<unsigned short, std::vector<unsigned short>>& smoothData);
		// ���_���ǂݍ���(assimp)
		static YDX::VertexIndex<VData> LoadVertices(const aiMesh* src, bool invU, bool invV, bool isNormalized);
		// �}�e���A���ǂݍ���(assimp)
		static Material LoadMaterial(const std::string directoryPath, const aiMaterial* src, const std::string extension);
		// �}�e���A���ǂݍ���
		static Material LoadMaterial(const std::string& directoryPath, const std::string& fileName);
	};
}

