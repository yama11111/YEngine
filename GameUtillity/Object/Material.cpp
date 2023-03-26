#include "Material.h"
#include "FileUtillity.h"
#include <memory>
#include <cassert>
#include <fstream>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma region ���O���

using YGame::Material;

#pragma endregion

#pragma region Static

YGame::TextureManager* Material::spTexManager_ = nullptr;
UINT Material::sDefTexIndex_ = UINT32_MAX;

void Material::StaticInitialize()
{
	// ���
	spTexManager_ = TextureManager::GetInstance();

	// �f�t�H���g�̃e�N�X�`����ݒ�
	sDefTexIndex_ = spTexManager_->Load("white1x1.png", false);
}

#pragma endregion

Material::Material() :
	name_(),
	ambient_(0.2f, 0.2f, 0.2f),
	diffuse_(0.5f, 0.5f, 0.5f),
	specular_(0.10f, 0.10f, 0.10f),
	alpha_(1.0f),
	texFileName_(),
	texIndex_(sDefTexIndex_)
{
	// �萔�o�b�t�@����
	cBuff_.Create();
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
			m.texIndex_ = spTexManager_->Load(directoryPath, m.texFileName_);
		}

	}

	// �t�@�C�������
	file.close();

	// �}�e���A����Ԃ�
	return m;
}

Material Material::Load(const std::string directoryPath, const aiMaterial* src, const std::string extension)
{
	// �߂�l�p
	Material material = Material();

	// �ǂݍ���
	aiString path;
	if (src->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
	{
		// �t�@�C����
		std::string fileName = std::string(path.C_Str());

		// �g���q��ύX����Ȃ�
		if (extension != "")
		{
			// �g���q�ݒ�
			fileName = YUtil::ReplaceExtension(fileName, extension);
		}

		// �ǂݍ���(���)
		material.texFileName_ = fileName;
		material.texIndex_ = spTexManager_->Load(directoryPath, fileName);
	}

	// �}�e���A����Ԃ�
	return material;
}

void Material::SetDrawCommand(UINT mateRPIndex, UINT texRPIndex)
{
	// �}�e���A��
	cBuff_.SetDrawCommand(mateRPIndex);

	// �e�N�X�`��
	spTexManager_->SetDrawCommand(texRPIndex, texIndex_);
}
