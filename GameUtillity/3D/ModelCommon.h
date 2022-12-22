#pragma once
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

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
	protected:
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet pplnSet_;
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
	public:
		// �ÓI�������X�e�[�^�X
		struct StaticInitStatus
		{
			// ���[�g�p�����[�^�|�C���^
			std::vector<D3D12_ROOT_PARAMETER>* rootParams_;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}

