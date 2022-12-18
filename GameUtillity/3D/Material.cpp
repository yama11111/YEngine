#include "Material.h"
#include <cassert>
#include <fstream>
#include <sstream>

using Game::Material;

Game::TextureManager* Material::pTexManager_ = nullptr;

void Material::StaticInitialize(TextureManager* pTexManager)
{
	assert(pTexManager);
	pTexManager_ = pTexManager;
}

Material::Material() :
	ambient_(0.3f, 0.3f, 0.3f),
	diffuse_(1.0f, 1.0f, 1.0f),
	specular_(0.0f, 0.0f, 0.0f),
	alpha_(1.0f),
	texIndex_(0)
{
	cbMtrl_.Create();
	cbMtrl_.map_->ambient_ = ambient_;
	cbMtrl_.map_->diffuse_ = diffuse_;
	cbMtrl_.map_->specular_ = specular_;
	cbMtrl_.map_->alpha_ = alpha_;
}

void Material::Load(const std::string& directoryPath, const std::string& mtlFileName)
{
	// �t�@�C���X�g���[��
	std::ifstream file;
	// .mtl�t�@�C�����J��
	file.open(directoryPath + mtlFileName);
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
			lineStream >> name_;
		}
		// �擪������ "Ka" �Ȃ�A���r�G���g�F
		if (key == "Ka")
		{
			// �ǂݍ���
			lineStream >> ambient_.x_;
			lineStream >> ambient_.y_;
			lineStream >> ambient_.z_;
		}
		// �擪������ "Kd" �Ȃ�f�B�t���[�Y�F
		if (key == "Kd")
		{
			// �ǂݍ���
			lineStream >> diffuse_.x_;
			lineStream >> diffuse_.y_;
			lineStream >> diffuse_.z_;
		}
		// �擪������ "vn" �Ȃ�X�y�L�����[�F
		if (key == "Ks")
		{
			// �ǂݍ���
			lineStream >> specular_.x_;
			lineStream >> specular_.y_;
			lineStream >> specular_.z_;
		}

		// �擪������ "map_Kd" �Ȃ�e�N�X�`���t�@�C����
		if (key == "map_Kd")
		{
			// �ǂݍ���
			lineStream >> textureFileName_;
			texIndex_ = pTexManager_->Load(directoryPath, textureFileName_);
		}

	}

	file.close();
}

void Material::LoadTexture(const std::string& directoryPath, const std::string& texFileName)
{
	textureFileName_ = texFileName;
	texIndex_ = pTexManager_->Load(directoryPath, texFileName);
}

void Material::SetDrawCommand(const UINT tex)
{
	pTexManager_->SetDrawCommand(tex);
	cbMtrl_.SetDrawCommand();
}

void Material::SetDrawCommand()
{
	pTexManager_->SetDrawCommand(texIndex_);
	cbMtrl_.SetDrawCommand();
}
