#include "Level.h"
#include "MathVector.h"
#include "MathUtil.h"
#include "FileUtil.h"
#include <cassert>
#include <fstream>
#include <sstream>

#include "PlayerDrawer.h"
#include "CloudDrawer.h"
#include "SkydomeDrawer.h"
#include "DefaultDrawer.h"

#pragma region ���O���

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Level;
using YGame::GameObject;
using YGame::Model;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

#pragma region Static

list<unique_ptr<Level>> Level::sLevelDatas_;

#pragma endregion

void Level::LoadAsset()
{
}

Level* Level::LoadJson(const std::string& fileName)
{
	// ���I���x���f�[�^����
	std::unique_ptr<Level> newLevel = std::make_unique<Level>();

	// �t���p�X
	const std::string fullpath = "Resources/LevelData/" + fileName;

	// �t�@�C���X�g���[��
	std::ifstream file;

	// �t�@�C���J��
	file.open(fullpath);
	
	// �t�@�C���I�[�v�����s���`�F�b�N
	assert(file.fail() == false);


	// json�����񂩂�𓀂����f�[�^
	nlohmann::json deserialized;
	
	// ��
	file >> deserialized;

	// ���������x���f�[�^���`�F�b�N
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	// "name" �𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();
	
	// ���������x���f�[�^���`�F�b�N
	assert(name.compare("scene") == 0);

	// "object" �S�đ���
	for (nlohmann::json& object : deserialized["objects"])
	{
		// �f�[�^�ǂݍ���
		newLevel->LoadData(object);
	}

	// �ԋp�p�|�C���^
	Level* pLevel = newLevel.get();

	// ���X�g�ɑ}��
	sLevelDatas_.push_back(std::move(newLevel));

	// �|�C���^��Ԃ�
	return pLevel;
}

void Level::LoadData(nlohmann::json& object, GameObject* pParent)
{
	// "type" �ȊO�x��
	assert(object.contains("type"));

	// ��ʂ��擾
	std::string type = object["type"].get<std::string>();

	// MESH
	if (type.compare("MESH") == 0)
	{
		// �I�u�W�F�N�g
		std::unique_ptr<GameObject> newObj;

		// ���O
		std::string name;

		// �I�u�W�F�N�g����
		newObj = std::make_unique<GameObject>();

		// �t�@�C����
		if (object.contains("name"))
		{
			name = object["name"];
			name = YFile::ReplaceExtension(name, "");
		}

		// �g�����X�t�H�[���̃p�����[�^�ǂݍ���
		nlohmann::json& transform = object["transform"];

		// �������p
		YGame::Transform::Status status{};

		// �ʒu
		status.pos_.x_ = +static_cast<float>(transform["translation"][1]);
		status.pos_.y_ = +static_cast<float>(transform["translation"][2]);
		status.pos_.z_ = -static_cast<float>(transform["translation"][0]);

		// ��]
		status.rota_.x_ = -static_cast<float>(transform["rotation"][1]);
		status.rota_.y_ = -static_cast<float>(transform["rotation"][2]);
		status.rota_.z_ = +static_cast<float>(transform["rotation"][0]);
		status.rota_ = YMath::ConvertFromDegreeToRadian(status.rota_);

		// �傫��
		status.scale_.x_ = static_cast<float>(transform["scaling"][1]);
		status.scale_.y_ = static_cast<float>(transform["scaling"][2]);
		status.scale_.z_ = static_cast<float>(transform["scaling"][0]);

		// ������
		newObj->Initialize(name, status, pParent);
		if (name == "Cloud.")
		{
			newObj->SetDrawer(CloudDrawer::Create(nullptr, 1));
		}
		else if (name == "Skydome.")
		{
			newObj->SetDrawer(SkydomeDrawer::Create(nullptr, 0));
		}

		// �q��ǂݍ���
		if (object.contains("children"))
		{
			// �q�̐�����
			for (size_t i = 0; i < object["children"].size(); i++)
			{
				// �q�I�u�W�F�N�g�ǂݍ���
				LoadData(object["children"][i], newObj.get());
			}
		}

		// ���X�g�ɑ}��
		objs_.push_back(std::move(newObj));
	}
	//// CAMERA
	//else if (type.compare("CAMERA") == 0)
	//{
	//	// �I�u�W�F�N�g
	//	std::unique_ptr<Camera> newCamera;

	//	// ���O
	//	std::string name;

	//	// �I�u�W�F�N�g����
	//	newCamera= std::make_unique<Camera>();

	//	// �t�@�C����
	//	if (object.contains("file_name"))
	//	{
	//		name = object["file_name"];
	//	}

	//	// �g�����X�t�H�[���̃p�����[�^�ǂݍ���
	//	nlohmann::json& transform = object["transform"];

	//	// �������p
	//	YGame::Transform::Status status{};

	//	// �ʒu
	//	status.pos_.x_ = +static_cast<float>(transform["translation"][1]);
	//	status.pos_.y_ = +static_cast<float>(transform["translation"][2]);
	//	status.pos_.z_ = -static_cast<float>(transform["translation"][0]);

	//	// ��]
	//	status.rota_.x_ = -static_cast<float>(transform["rotation"][2]);
	//	status.rota_.y_ = +static_cast<float>(transform["rotation"][0]);
	//	status.rota_.z_ = -static_cast<float>(transform["rotation"][1]);
	//	status.rota_ = YMath::ConvertFromDegreeToRadian(status.rota_);
	//	
	//	// ������
	//	newCamera->Initialize(status.pos_, status.rota_);
	//	//newCamera->Initialize({0,0,-10}, {});

	//	// ���X�g�ɑ}��
	//	cameras_.push_back(std::move(newCamera));

	//}
	// ����ȊO�Ȃ�e��
	else
	{
		return;
	}
}


void Level::ClearAllData()
{
	// ����Ȃ�
	if (sLevelDatas_.empty() == false)
	{
		// �N���A
		sLevelDatas_.clear();
	}
}

void Level::Initialize()
{
}

void Level::Update()
{
	// �S���f��
	for (std::unique_ptr<GameObject>& obj : objs_)
	{
		// �s��X�V
		obj->Update();
	}
}

void Level::Draw()
{
	// �S���f��
	for (std::unique_ptr<GameObject>& obj : objs_)
	{
		// �`��
		obj->Draw();
	}
}
