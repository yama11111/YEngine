#include "MapChip.h"
#include "BlockDrawer.h"
#include "GoalDrawer.h"
#include <cassert>

using YGame::MapChip;
using YMath::Vector3;

void MapChip::Reset()
{
	// null�`�F�b�N
	assert(pMapData_);

	// �S����
	chips_.clear();

	// �ԍ�
	std::vector<std::vector<uint16_t>> nums = pMapData_->chipNums_;

	// �ЂƂ��ݒ� + ����
	for (size_t y = 0; y < nums.size(); y++)
	{
		for (size_t x = 0; x < nums[y].size(); x++)
		{
			// 0�Ȃ�e��
			if (nums[y][x] == 0) { continue; }

			// �`�b�v����
			std::unique_ptr<ChipData> chip = std::make_unique<ChipData>();

			// �ʒu
			float posX = +(chipScale_.x_ * 2.0f) * x + chipScale_.x_;
			float posY = -(chipScale_.y_ * 2.0f) * y - chipScale_.y_;

			Vector3 pos = Vector3(posX, posY, 0.0f) + leftTop_;

			// ������
			chip->transform_.Initialize({ pos,{},chipScale_ });

			if (nums[y][x] == 1)
			{
				// �`��N���X
				chip->drawer_.reset(BlockDrawer::Create(&chip->transform_, 1));
			}
			if (nums[y][x] == 2)
			{
				// �`��N���X
				chip->drawer_.reset(GoalDrawer::Create(&chip->transform_, 1));
			}

			// 1�Ԍ��ɑ}��
			chips_.push_back(std::move(chip));
		}
	}

	isClear_ = false;
}

void MapChip::Update()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �X�V
	for (std::unique_ptr<ChipData>& chip : chips_)
	{
		chip->transform_.UpdateMatrix();
		chip->drawer_->Update();
	}
}

void MapChip::Draw()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �`��
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
