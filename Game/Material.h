#pragma once
#include "Vec3.h"
#include "ConstBuffer.h"
#include "TextureManager.h"

namespace Game
{
	class Material
	{
	public:
		std::string name_; // �}�e���A����
		Math::Vec3 ambient_; // �A���r�G���g�e���x
		Math::Vec3 diffuse_; // �f�B�t���[�Y�e���x
		Math::Vec3 specular_; // �X�y�L�����[�e���x
		float alpha_; // �A���t�@�l
		std::string textureFileName_; // �e�N�X�`���t�@�C����
		UINT texIndex_ = UINT32_MAX;
	private:
		// �萔�o�b�t�@(�}�e���A��2)
		DX::ConstBuffer<DX::MaterialCBData> cbMtrl_;
	public:
		// �R���X�g���N�^
		Material();
	public:
		// �}�e���A���ǂݍ���
		void Load(const std::string& directoryPath, const std::string& mtlFileName);
		// �e�N�X�`���ǂݍ���
		void LoadTexture(const std::string& directoryPath, const std::string& texFileName);
		// �`��O�R�}���h
		void SetDrawCommand(const UINT tex);
		// �`��O�R�}���h
		void SetDrawCommand();
	private:
		// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
		static TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager);
	};
}