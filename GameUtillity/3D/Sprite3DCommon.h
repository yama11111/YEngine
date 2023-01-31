#pragma once
#include "PipelineSet.h"
#include "ShaderCommon.h"
#include "TextureManager.h"
#include "Vec3.h"
#include "Mat4.h"
#include <memory>

namespace YGame
{
	class Sprite3DCommon
	{
	public:
		// ���_�f�[�^
		struct VData
		{
			YMath::Vec3 pos_; // xyz���W
		};
		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			YMath::Mat4 matWorld_; // 3D�ϊ��s��
			YMath::Mat4 matBill_; // �r���{�[�h�s��
		};
	public:
		// ���[�g�p�����[�^�ԍ�
		enum class RootParameterIndex
		{
			SpriteCB = 0,
			ColorCB = 1,
			TexDT = 2,
		};
	protected:
		// �p�C�v���C���ݒ�
		static YDX::PipelineSet pipelineSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	private:
		// �V�F�[�_�[�Z�b�g
		class ShaderSet : public YDX::ShaderCommon
		{
		public:
			// �W�I���g���V�F�[�_�I�u�W�F�N�g
			Microsoft::WRL::ComPtr<ID3DBlob> gsBlob_ = nullptr;
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
			// �e�N�X�`���}�l�[�W���[�|�C���^
			TextureManager* pTexManager_;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}

