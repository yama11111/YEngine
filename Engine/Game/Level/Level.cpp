#include "Level.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <json.hpp>

#pragma region ���O���

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Level;
using YGame::Model;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region Static

list<unique_ptr<Level>> Level::sLevelDatas_;

#pragma endregion

void Level::ClearAllData()
{
	// ����Ȃ�
	if (sLevelDatas_.empty() == false)
	{
		// �N���A
		sLevelDatas_.clear();
	}
}

static bool LoadObject(nlohmann::json& object, Level::ObjectSet* objSet, Level::ObjectSet* pParent)
{
	// "type" �ȊO�x��
	assert(object.contains("type"));


	// ��ʂ��擾
	std::string type = object["type"].get<std::string>();

	// MESH
	if (type.compare("MESH") == 0)
	{
		// �v�f�ǉ�
		objSet->pModel_ = Model::CreateCube();

		// �t�@�C����
		if (object.contains("file_name"))
		{
			objSet->objFileName_ = object["file_name"];
		}
	}
	else { return false; }

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

	// �傫��
	status.scale_.x_ = static_cast<float>(transform["scaling"][1]);
	status.scale_.y_ = static_cast<float>(transform["scaling"][2]);
	status.scale_.z_ = static_cast<float>(transform["scaling"][0]);

	// �I�u�W�F�N�g�ɓ����
	objSet->pObjs_.reset(Model::Object::Create(status));

	// �q��ǂݍ���
	if (object.contains("children"))
	{
		// �q�̐�����
		for (size_t i = 0; i < object["children"].size(); i++)
		{
			// �q�I�u�W�F�N�g����
			std::unique_ptr<Level::ObjectSet> newChildObjSet = std::make_unique<Level::ObjectSet>();

			// �q�I�u�W�F�N�g�ǂݍ���
			if (LoadObject(object["children"][i], newChildObjSet.get(), objSet))
			{
				// �q��}��
				objSet->child_.swap(newChildObjSet);
			}
		}
	}

	// �e������Ȃ�
	if (pParent)
	{
		// �s���e�q�֌W��
		objSet->pObjs_->parent_ = &pParent->pObjs_->m_;
	}

	// �I�u�W�F�N�g��Ԃ�
	return true;
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
		// �I�u�W�F�N�g����
		std::unique_ptr<Level::ObjectSet> newObjSet = std::make_unique<Level::ObjectSet>();

		// �I�u�W�F�N�g�ǂݍ���
		if (LoadObject(object, newObjSet.get(), nullptr))
		{
			// �I�u�W�F�N�g�ǂݍ���
			newLevel->objSets_.push_back(std::move(newObjSet));
		}
	}

	// �ԋp�p�|�C���^
	Level* pLevel = newLevel.get();

	// ���X�g�ɑ}��
	sLevelDatas_.push_back(std::move(newLevel));

	// �|�C���^��Ԃ�
	return pLevel;
}

void Level::UpdateObjSet(ObjectSet* obj)
{
	obj->pObjs_->UpdateMatrix();
	if (obj->child_ )
	{
		UpdateObjSet(obj->child_.get());
	}
}

void Level::DrawObjSet(ObjectSet* obj)
{
	obj->pModel_->SetDrawCommand(obj->pObjs_.get(), DrawLocation::Center);
	if (obj->child_)
	{
		DrawObjSet(obj->child_.get());
	}
}

void Level::Update()
{
	// �S���f��
	for (std::unique_ptr<Level::ObjectSet>& objSet : objSets_)
	{
		// �s��X�V
		UpdateObjSet(objSet.get());
	}
}

void Level::Draw()
{
	// �S���f��
	for (std::unique_ptr<Level::ObjectSet>& objSet : objSets_)
	{
		// �`��
		DrawObjSet(objSet.get());
	}
}
