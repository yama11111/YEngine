#include "MapChipManager.h"
#include <cassert>
#include "StageManager.h"

using YGame::MapChipManager;

void MapChipManager::Load(const std::string& mapFileName)
{
	// マップデータ生成
	std::unique_ptr<MapData> mapData = std::make_unique<MapData>();
	
	// 挿入
	mapDatas_.push_back(std::move(mapData));
	
	// 読み込み
	Load(static_cast<uint16_t>(mapDatas_.size() - 1), mapFileName);
}

void MapChipManager::Load(const uint16_t mapIndex, const std::string& mapFileName)
{
	// データサイズ超過時弾く
	assert(0 <= mapIndex && mapIndex < mapDatas_.size());
	
	// 読み込み
	mapDatas_[mapIndex]->LoadCSV(mapFileName);
}

void MapChipManager::Initialize(
	const uint16_t mapIndex, 
	const YMath::Vector3& leftTop, 
	const YMath::Vector3& chipScale)
{
	// マップデータ空なら弾く
	if (mapDatas_.empty()) { return; }

	// 現在の番号
	currentIndex_ = mapIndex;
	
	// マップチップ初期化
	map_.Initialize(mapDatas_[currentIndex_].get(), leftTop, chipScale);
}

void MapChipManager::Reset()
{
	// マップリセット
	map_.Reset();
}

void MapChipManager::Update()
{
	// 更新
	map_.Update();

	if(map_.isClear_)
	{
		// ステージクリア
		StageManager::GetInstance()->ClearStage();
	}
}

void MapChipManager::Draw()
{
	// 描画
	map_.Draw();
}

MapChipManager* MapChipManager::GetInstance()
{
	static MapChipManager instance;
	return &instance;
}
