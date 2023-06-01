#include "Level.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <json.hpp>

#pragma region 名前空間

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
	// あるなら
	if (sLevelDatas_.empty() == false)
	{
		// クリア
		sLevelDatas_.clear();
	}
}

static bool LoadObject(nlohmann::json& object, Level::ObjectSet* objSet, Level::ObjectSet* pParent)
{
	// "type" 以外警告
	assert(object.contains("type"));


	// 種別を取得
	std::string type = object["type"].get<std::string>();

	// MESH
	if (type.compare("MESH") == 0)
	{
		// 要素追加
		objSet->pModel_ = Model::CreateCube();

		// ファイル名
		if (object.contains("file_name"))
		{
			objSet->objFileName_ = object["file_name"];
		}
	}
	else { return false; }

	// トランスフォームのパラメータ読み込み
	nlohmann::json& transform = object["transform"];

	// 初期化用
	YGame::Transform::Status status{};

	// 位置
	status.pos_.x_ = +static_cast<float>(transform["translation"][1]);
	status.pos_.y_ = +static_cast<float>(transform["translation"][2]);
	status.pos_.z_ = -static_cast<float>(transform["translation"][0]);

	// 回転
	status.rota_.x_ = -static_cast<float>(transform["rotation"][1]);
	status.rota_.y_ = -static_cast<float>(transform["rotation"][2]);
	status.rota_.z_ = +static_cast<float>(transform["rotation"][0]);

	// 大きさ
	status.scale_.x_ = static_cast<float>(transform["scaling"][1]);
	status.scale_.y_ = static_cast<float>(transform["scaling"][2]);
	status.scale_.z_ = static_cast<float>(transform["scaling"][0]);

	// オブジェクトに入れる
	objSet->pObjs_.reset(Model::Object::Create(status));

	// 子を読み込む
	if (object.contains("children"))
	{
		// 子の数だけ
		for (size_t i = 0; i < object["children"].size(); i++)
		{
			// 子オブジェクト生成
			std::unique_ptr<Level::ObjectSet> newChildObjSet = std::make_unique<Level::ObjectSet>();

			// 子オブジェクト読み込み
			if (LoadObject(object["children"][i], newChildObjSet.get(), objSet))
			{
				// 子を挿入
				objSet->child_.swap(newChildObjSet);
			}
		}
	}

	// 親があるなら
	if (pParent)
	{
		// 行列を親子関係に
		objSet->pObjs_->parent_ = &pParent->pObjs_->m_;
	}

	// オブジェクトを返す
	return true;
}

Level* Level::LoadJson(const std::string& fileName)
{
	// 動的レベルデータ生成
	std::unique_ptr<Level> newLevel = std::make_unique<Level>();

	// フルパス
	const std::string fullpath = "Resources/LevelData/" + fileName;

	// ファイルストリーム
	std::ifstream file;

	// ファイル開く
	file.open(fullpath);
	
	// ファイルオープン失敗かチェック
	assert(file.fail() == false);


	// json文字列から解凍したデータ
	nlohmann::json deserialized;
	
	// 解凍
	file >> deserialized;

	// 正しいレベルデータかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	// "name" を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	
	// 正しいレベルデータかチェック
	assert(name.compare("scene") == 0);

	// "object" 全て走査
	for (nlohmann::json& object : deserialized["objects"])
	{
		// オブジェクト生成
		std::unique_ptr<Level::ObjectSet> newObjSet = std::make_unique<Level::ObjectSet>();

		// オブジェクト読み込み
		if (LoadObject(object, newObjSet.get(), nullptr))
		{
			// オブジェクト読み込み
			newLevel->objSets_.push_back(std::move(newObjSet));
		}
	}

	// 返却用ポインタ
	Level* pLevel = newLevel.get();

	// リストに挿入
	sLevelDatas_.push_back(std::move(newLevel));

	// ポインタを返す
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
	obj->pModel_->SetDrawCommand(obj->pObjs_.get(), DrawLocation::eCenter);
	if (obj->child_)
	{
		DrawObjSet(obj->child_.get());
	}
}

void Level::Update()
{
	// 全モデル
	for (std::unique_ptr<Level::ObjectSet>& objSet : objSets_)
	{
		// 行列更新
		UpdateObjSet(objSet.get());
	}
}

void Level::Draw()
{
	// 全モデル
	for (std::unique_ptr<Level::ObjectSet>& objSet : objSets_)
	{
		// 描画
		DrawObjSet(objSet.get());
	}
}
