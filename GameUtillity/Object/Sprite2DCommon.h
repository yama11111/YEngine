#pragma once
#include "Vertices.h"
#include "ShaderCommon.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include "Color.h"
#include "Vector2.h"
#include "Matrix4.h"
#include <memory>

namespace YGame
{
	// �X�v���C�g2D�p�I�u�W�F�N�g�R�����N���X
	class Sprite2DObjectCommon
	{
	protected:
		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D�ϊ��s��
		};
	protected:
		// �ÓI�ˉe�ϊ��s��(���s���e)
		static YMath::Matrix4 sProjection_;
		// �F (�f�t�H���g)
		static std::unique_ptr<Color> sDefColor_;
	public:
		// �ÓI������ (�f�t�H���g�l�ݒ�)
		static void StaticInitialize();
	};
	
	// �X�v���C�g2D�R�����N���X
	class Sprite2DCommon
	{
	public:
		// ���_�f�[�^�\����
		struct VData
		{
			YMath::Vector3 pos_; // xyz���W
			YMath::Vector2 uv_;  // uv���W
		};
	public:
		// ���[�g�p�����[�^�ԍ�
		enum class RootParameterIndex
		{
			TransformCB	 = 0, // �s��
			ColorCB		 = 1, // �F
			TexDT		 = 2, // �e�N�X�`��
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
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet sPipelineSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* spTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize();
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
