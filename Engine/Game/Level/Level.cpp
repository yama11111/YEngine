#include "Level.h"
#include "MathVector.h"
#include "MathUtil.h"
#include "FileUtil.h"
#include <cassert>
#include <fstream>
#include <sstream>

#include "GameObjectManager.h"
#include "Player.h"
#include "Slime.h"
#include "Coin.h"
#include "Life.h"
#include "Magnet.h"
#include "Block.h"
#include "Gate.h"
#include "Goal.h"

#include "BlockDrawer.h"
#include "SkydomeDrawer.h"
#include "DefaultDrawer.h"

#pragma region 名前空間

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Level;
using YGame::GameObject;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma endregion

#pragma region Static

list<unique_ptr<Level>> Level::sLevelDatas_;

#pragma endregion


Level* Level::LoadJson(const std::string& fileName, const std::string& key)
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
		// データ読み込み
		newLevel->LoadData(key, object);
	}

	// 返却用ポインタ
	Level* pLevel = newLevel.get();

	// リストに挿入
	sLevelDatas_.push_back(std::move(newLevel));

	// ポインタを返す
	return pLevel;
}

void Level::LoadData(const std::string& key, nlohmann::json& object, GameObject* pParent)
{
	// "type" 以外警告
	assert(object.contains("type"));

	// 種別を取得
	std::string type = object["type"].get<std::string>();

	// MESH
	if (type.compare("MESH") == 0)
	{
		// 名前
		std::string name;

		// ファイル名
		if (object.contains("name"))
		{
			name = object["name"];
			name = YFile::ReplaceExtension(name, "");
		}

		// トランスフォームのパラメータ読み込み
		nlohmann::json& transform = object["transform"];

		// 初期化用
		YGame::Transform::Status status{};

		// 位置
		status.pos_.x = +static_cast<float>(transform["translation"][1]);
		status.pos_.y = +static_cast<float>(transform["translation"][2]);
		status.pos_.z = -static_cast<float>(transform["translation"][0]);

		// 回転
		status.rota_.x = -static_cast<float>(transform["rotation"][1]);
		status.rota_.y = -static_cast<float>(transform["rotation"][2]);
		status.rota_.z = +static_cast<float>(transform["rotation"][0]);
		status.rota_ = YMath::ConvertFromDegreeToRadian(status.rota_);

		// 大きさ
		status.scale_.x = static_cast<float>(transform["scaling"][1]);
		status.scale_.y = static_cast<float>(transform["scaling"][2]);
		status.scale_.z = static_cast<float>(transform["scaling"][0]);

		// オブジェクト
		std::unique_ptr<GameObject> newObj = nullptr;
		bool isUpdateSkip = true;
		bool isBackground = false;

		// 初期化
		if (name == "Player.")
		{
			isUpdateSkip = false;

			newObj = Player::Create(status, { key });
		}
		else if (name == "Slime." || name == "Flog." || name == "Bird." || name == "Ogre." || name == "Goblin.")
		{
			newObj = Slime::Create(status, { key });
		}
		else if (name == "Coin.")
		{
			newObj = Coin::Create(status, { key });
		}
		else if (name == "Life.")
		{
			isUpdateSkip = false;

			newObj = Life::Create(status, { key });
		}
		else if (name == "Magnet.")
		{
			isUpdateSkip = false;

			newObj = Magnet::Create(status, { key });
		}
		else if (name == "Block.")
		{
			newObj = Block::Create(status, { key }, pParent);
		}
		else if (name == "Gate.")
		{
			newObj = Gate::Create(status, { key }, pParent);
		}
		else if (name == "Goal.")
		{
			newObj = Goal::Create(status, { key }, pParent);
		}
		else
		{
			newObj = std::make_unique<GameObject>();
			newObj->Initialize(name, status, pParent);
		}
		

		if (name == "Block_B.")
		{
			isBackground = true;
			newObj->SetDrawer(BlockDrawer::Create(nullptr, nullptr, true, 1));
			newObj->SetDrawKeys({});
		}
		else if (name == "Skydome.")
		{
			isBackground = true;
			newObj->SetDrawer(SkydomeDrawer::Create(nullptr, nullptr, 4));
			newObj->SetDrawKeys({});
		}

		// 子を読み込む
		if (object.contains("children"))
		{
			// 子の数だけ
			for (size_t i = 0; i < object["children"].size(); i++)
			{
				// 子オブジェクト読み込み
				LoadData(key, object["children"][i], newObj.get());
			}
		}

		// リストに挿入
		if (isBackground == false)
		{
			GameObjectManager::GetInstance()->PushBack(std::move(newObj), isUpdateSkip);
		}
		else
		{
			GameObjectManager::GetInstance()->PushBackForBackObject(std::move(newObj));
		}
	}
	// それ以外なら弾く
	else
	{
		return;
	}
}


void Level::ClearAllData()
{
	// あるなら
	if (sLevelDatas_.empty() == false)
	{
		// クリア
		sLevelDatas_.clear();
	}
}