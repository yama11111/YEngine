#include "Material.h"
#include "FileUtillity.h"
#include <memory>
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region ���O���

using YGame::Material;
using YGame::Texture;

#pragma endregion

#pragma region Static

Texture* Material::spDefTexIndex_ = nullptr;

void Material::StaticInitialize()
{
	// �f�t�H���g�̃e�N�X�`����ݒ�
	spDefTexIndex_ = Texture::Load("white1x1.png", false);
}

#pragma endregion

Material::Material() :
	name_(),
	ambient_(0.8f, 0.8f, 0.8f),
	diffuse_(0.5f, 0.5f, 0.5f),
	specular_(0.10f, 0.10f, 0.10f),
	alpha_(1.0f),
	texFileName_(),
	pTex_(spDefTexIndex_)
{
	// �萔�o�b�t�@����
	cBuff_.Create(false);
	cBuff_.map_->ambient_ = ambient_;
	cBuff_.map_->diffuse_ = diffuse_;
	cBuff_.map_->specular_ = specular_;
	cBuff_.map_->alpha_ = alpha_;
}

Material Material::Load(const std::string& directoryPath, const std::string& fileName)
{
	// �߂�l�p
	Material m;

	// �t�@�C���X�g���[��
	std::ifstream file;
	// .mtl�t�@�C�����J��
	file.open(directoryPath + fileName);
	// �t�@�C���I�[�v�����s���`�F�b�N
	assert(file);

	// 1�s���ǂݍ���
	std::string line;
	while (std::getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream lineStream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		std::getline(lineStream, key, ' ');

		// �擪�̃^�u�����͖�������
		if (key[0] == '\t') { key.erase(key.begin()); }

		// �擪������ "newmtl" �Ȃ�}�e���A����
		if (key == "newmtl")
		{
			// �ǂݍ���
			lineStream >> m.name_;
		}
		// �擪������ "Ka" �Ȃ�A���r�G���g�F
		if (key == "Ka")
		{
			// �ǂݍ���
			lineStream >> m.ambient_.x_;
			lineStream >> m.ambient_.y_;
			lineStream >> m.ambient_.z_;
		}
		// �擪������ "Kd" �Ȃ�f�B�t���[�Y�F
		if (key == "Kd")
		{
			// �ǂݍ���
			lineStream >> m.diffuse_.x_;
			lineStream >> m.diffuse_.y_;
			lineStream >> m.diffuse_.z_;
		}
		// �擪������ "vn" �Ȃ�X�y�L�����[�F
		if (key == "Ks")
		{
			// �ǂݍ���
			lineStream >> m.specular_.x_;
			lineStream >> m.specular_.y_;
			lineStream >> m.specular_.z_;
		}

		// �擪������ "map_Kd" �Ȃ�e�N�X�`���t�@�C����
		if (key == "map_Kd")
		{
			// �ǂݍ���
			lineStream >> m.texFileName_;
			m.pTex_ = Texture::Load(directoryPath, m.texFileName_);
		}

	}

	// �t�@�C�������
	file.close();

	// �}�e���A����Ԃ�
	return m;
}

void Material::LoadTexture(const std::string& texFileName)
{
	// �摜�����
	texFileName_ = texFileName;
	
	// �摜�ǂݍ���
	pTex_ = Texture::Load(texFileName);
}

void Material::SetDrawCommand(UINT mateRPIndex, UINT texRPIndex)
{
	// �}�e���A��
	cBuff_.SetDrawCommand(mateRPIndex);

	// �e�N�X�`��
	pTex_->SetDrawCommand(texRPIndex);
}
