#include "MapChip.h"
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
			if (nums[y][x] == 0) { break; }

			// �`�b�v����
			std::unique_ptr<ChipData> chip = std::make_unique<ChipData>();

			// �ʒu
			float posX = +(chipScale_.x_ * 2.0f) * x + chipScale_.x_;
			float posY = -(chipScale_.y_ * 2.0f) * y - chipScale_.y_;

			Vector3 pos = Vector3(posX, posY, 0.0f) + leftTop_;

			// ������
			chip->transform_.Initialize({ pos,{},chipScale_ });

			// 1�Ԍ��ɑ}��
			chips_.push_back(std::move(chip));
		}
	}
}

void MapChip::Update()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �X�V
	for (std::unique_ptr<ChipData>& chip : chips_)
	{
		chip->transform_.UpdateMatrix();
	}
}

void MapChip::Draw()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �`��
	for (std::unique_ptr<ChipData>& chip : chips_)
	{
		
	}
}

bool MapChip::CollisionChip(const int x, const int y)
{


	return false;
}
