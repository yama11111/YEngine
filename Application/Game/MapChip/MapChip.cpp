#include "MapChip.h"
#include "BlockDrawer.h"
#include "GoalDrawer.h"
#include <cassert>

using YGame::MapChip;
using YMath::Vector3;

void MapChip::Reset()
{
	// nullチェック
	assert(pMapData_);

	// 全消去
	chips_.clear();

	// 番号
	std::vector<std::vector<uint16_t>> nums = pMapData_->chipNums_;

	// ひとつずつ設定 + 生成
	for (size_t y = 0; y < nums.size(); y++)
	{
		for (size_t x = 0; x < nums[y].size(); x++)
		{
			// 0なら弾く
			if (nums[y][x] == 0) { continue; }

			// チップ生成
			std::unique_ptr<ChipData> chip = std::make_unique<ChipData>();

			// 位置
			float posX = +(chipScale_.x_ * 2.0f) * x + chipScale_.x_;
			float posY = -(chipScale_.y_ * 2.0f) * y - chipScale_.y_;

			Vector3 pos = Vector3(posX, posY, 0.0f) + leftTop_;

			// 初期化
			chip->transform_.Initialize({ pos,{},chipScale_ });

			if (nums[y][x] == 1)
			{
				// 描画クラス
				chip->drawer_.reset(BlockDrawer::Create(&chip->transform_, 1));
			}
			if (nums[y][x] == 2)
			{
				// 描画クラス
				chip->drawer_.reset(GoalDrawer::Create(&chip->transform_, 1));
			}

			// 1番後ろに挿入
			chips_.push_back(std::move(chip));
		}
	}

	isClear_ = false;
}

void MapChip::Update()
{
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// 更新
	for (std::unique_ptr<ChipData>& chip : chips_)
	{
		chip->transform_.UpdateMatrix();
		chip->drawer_->Update();
	}
}

void MapChip::Draw()
{
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// 描画
	for (std::unique_ptr<ChipData>& chip : chips_)
	{
		chip->drawer_->Draw();
	}
}

bool MapChip::CollisionChip(const int x, const int y)
{
	if (pMapData_->chipNums_[y][x] == 1) { return true; }
	
	if (pMapData_->chipNums_[y][x] == 2) { isClear_ = true; }

	return false;
}
