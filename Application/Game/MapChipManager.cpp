#include "MapChipManager.h"
#include <cassert>

using YGame::MapChipManager;

void MapChipManager::Load(const std::string& mapFileName)
{
	// �}�b�v�f�[�^����
	std::unique_ptr<MapData> mapData = std::make_unique<MapData>();
	
	// �}��
	mapDatas_.push_back(std::move(mapData));
	
	// �ǂݍ���
	Load(static_cast<uint16_t>(mapDatas_.size() - 1), mapFileName);
}

void MapChipManager::Load(const uint16_t mapIndex, const std::string& mapFileName)
{
	// �f�[�^�T�C�Y���ߎ��e��
	assert(0 <= mapIndex && mapIndex < mapDatas_.size());
	
	// �ǂݍ���
	mapDatas_[mapIndex]->LoadCSV(mapFileName);
}

void MapChipManager::Initialize(
	const uint16_t mapIndex, 
	const YMath::Vector3& leftTop, 
	const YMath::Vector3& chipScale)
{
	// �}�b�v�f�[�^��Ȃ�e��
	if (mapDatas_.empty()) { return; }

	// ���݂̔ԍ�
	currentIndex_ = mapIndex;
	
	// �}�b�v�`�b�v������
	map_.Initialize(mapDatas_[currentIndex_].get(), leftTop, chipScale);
}

void MapChipManager::Reset()
{
	// �}�b�v���Z�b�g
	map_.Reset();
}

void MapChipManager::Update()
{
	// �X�V
	map_.Update();
}

void MapChipManager::Draw()
{
	// �`��
	map_.Draw();
}

MapChipManager* MapChipManager::GetInstance()
{
	static MapChipManager instance;
	return &instance;
}
