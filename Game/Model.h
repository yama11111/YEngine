#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Vertices.h"
#include "PipelineSet.h"
#include "TextureManager.h"
#include <string>

namespace Game
{
	struct Material
	{
		std::string name_; // �}�e���A����
		Math::Vec3 ambient_; // �A���r�G���g�e���x
		Math::Vec3 diffuse_; // �f�B�t���[�Y�e���x
		Math::Vec3 specular_; // �X�y�L�����[�e���x
		float alpha_; // �A���t�@�l
		std::string textureFileName_; // �e�N�X�`���t�@�C����
		Material() 
		{
			ambient_ = { 0.3f,0.3f,0.3f };
			diffuse_ = { 0.0f,0.0f,0.0f };
			specular_ = { 0.0f,0.0f,0.0f };
			alpha_ = 1.0f;
		}
	};

	class Model
	{
	private:
		// ���_�C���f�b�N�X
		DX::VertexIndex3D vtIdx_;
	public:
		// ���I�|�C���^(������)
		static Model* Create();
		// ���f���ǂݍ���
		static Model* Load(const char* fileName);
	public:
		// �`��
		void Draw(Transform& trfm, ViewProjection& vp, const UINT tex);
	private:
		// �R���X�g���N�^
		Model() = default;
	private:
		// �p�C�v���C���ݒ�
		static DX::PipelineSet pplnSet_;
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager, std::vector<D3D12_ROOT_PARAMETER>* rootParams);
		// �ÓI�`��R�}���h
		static void StaticSetDrawCommand();
	};
}
