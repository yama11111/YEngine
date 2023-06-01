#include "MapChip.h"
#include <cassert>
#include <fstream>
#include "YMath.h"

using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YGame::MapData;
using YGame::MapChip;
using YGame::MapChip2DDisplayer;

#pragma region MapData

void MapData::Load(const std::string fileName)
{
	// �N���A
	Clear();

	FILE* fp = nullptr;
	errno_t err;

	// �ǂݍ��ݗp�t�@�C�����J��
	const std::string& directoryPath = "Resources/MapData/";
	std::string filePath = directoryPath + fileName;
	err = fopen_s(&fp, filePath.c_str(), "r");

	// �t�@�C���������Ȃ�G���[
	if (err != 0)
	{
		assert(false);
		return;
	}

	// �t�@�C���I�[�܂œǂݍ���
	int c = 0;
	std::vector<int> column;
	while (true)
	{
		// �����擾
		c = fgetc(fp);

		// ��
		if (c == ',') { continue; }
		// �s
		if (c == '\n')
		{
			chipNums_.push_back(column);
			column.clear();
			continue;
		}
		// �I�[
		if (c == EOF) 
		{
			chipNums_.push_back(column);
			break; 
		}

		// �}��
		column.push_back(c - 48);
	}

	// �t�@�C�������
	fclose(fp);

	chipColls_.clear();
	chipColls_.resize(chipNums_.size());
	for (size_t i = 0; i < chipColls_.size(); i++)
	{
		chipColls_[i].resize(chipNums_[i].size());
	}

	// �ǂݍ��݊���
	isLoaded_ = true;
}

void MapData::Clear()
{
	if (chipNums_.empty() == false) { chipNums_.clear(); }
	if (chipColls_.empty() == false) { chipColls_.clear(); }
}

void MapData::CollReset()
{
	for (size_t y = 0; y < chipColls_.size(); y++)
	{
		for (size_t x = 0; x < chipColls_[y].size(); x++)
		{
			chipColls_[y][x] = false;
		}
	}
}

#pragma endregion


#pragma region MapChip

void MapChip::Initialize(MapData* pMapData, const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	// null�`�F�b�N
	assert(pMapData);
	// ���
	pMapData_ = pMapData;

	// ������
	Initialize(leftTop, chipScale);
}
void MapChip::Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	// ���
	leftTop_ = leftTop;
	chipScale_ = chipScale;

	// ���Z�b�g
	Reset();
}
void MapChip::Reset()
{
	// null�`�F�b�N
	assert(pMapData_);
	
	// �ԍ�
	std::vector<std::vector<int>> nums = pMapData_->chipNums_;

	// �S���� + ���T�C�Y
	chips_.clear();

	// �ЂƂ��ݒ� + ����
	for (size_t y = 0; y < nums.size(); y++)
	{
		for (size_t x = 0; x < nums[y].size(); x++)
		{
			// ������Ȃ��Ȃ�
			if (nums[y][x] != 0)
			{
				std::unique_ptr<Chip> chip = nullptr;
				chip.reset(new Chip());

				// �I�u�W�F�N�g
				float posX = +(chipScale_.x_ * 2.0f) * x + chipScale_.x_;
				float posY = -(chipScale_.y_ * 2.0f) * y - chipScale_.y_;

				chip->transform_.reset(new Transform());
				chip->transform_->Initialize({ {posX,posY,0.0f},{},chipScale_ });
				chip->transform_->pos_ += leftTop_;

				// 1�Ԍ��ɑ}��
				chips_.push_back(std::move(chip));
			}
		}
	}
}

void MapChip::Update()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �}�b�v�f�[�^�����[�h����Ă��Ȃ��Ȃ�e��
	if (pMapData_->isLoaded_ == false) { return; }

	// �X�V
	for (size_t i = 0; i < chips_.size(); i++)
	{
		chips_[i]->transform_->UpdateMatrix();
	}
}

void MapChip::PerfectPixelCollision(MapChipCollider& collider)
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �}�b�v�f�[�^�����[�h����Ă��Ȃ��Ȃ�e��
	if (pMapData_->isLoaded_ == false) { return; }

	// ���
	Vector3& posRef = collider.PosRef();
	Vector3 scale = collider.Scale();
	Vector3& speedRef = collider.SpeedRef();

	// �Ԃ����Ă��邩
	bool isCollX = CollisionTemporaryMap(posRef, scale, { speedRef.x_,0,0 }); // x
	bool isCollY = CollisionTemporaryMap(posRef, scale, { 0,speedRef.y_,0 }); // y

	// �ߋ��n�ʃt���O�ݒ�
	collider.SetIsElderLanding(collider.IsLanding());
	// �n�ʃt���O�ݒ� (Y�����Ƀ}�b�v�`�b�v && �X�s�[�h�� -)
	collider.SetIsLanding((isCollY && speedRef.y_ <= 0.0f));

	// �Ԃ����Ă��Ȃ��Ȃ�X�L�b�v
	if (isCollX == false && isCollY == false) { return; }

	// �߂Â��ړ���
	YMath::Vector3 approach = speedRef / 100.0f;

	// �����߂�����
	while (true)
	{
		// �Ԃ����Ă��邩 (���ړ�)
		bool isCollTempX = CollisionTemporaryMap(posRef, scale, { approach.x_,0,0 }); // x
		bool isCollTempY = CollisionTemporaryMap(posRef, scale, { 0,approach.y_,0 }); // y

		// �Ԃ����Ă���Ȃ烋�[�v������
		if (isCollTempX || isCollTempY) { break; }

		// �����Â߂Â���
		if (isCollX) { posRef.x_ += approach.x_; }
		if (isCollY) { posRef.y_ += approach.y_; }
	}

	// ���x���Z�b�g
	if (isCollX) { speedRef.x_ = 0.0f; }
	if (isCollY) { speedRef.y_ = 0.0f; }
}
bool MapChip::CollisionTemporaryMap(const Vector3& pos, const Vector3 scale, const Vector3& spd)
{
	// ���ړ����W
	Vector3 temporary = pos + spd - leftTop_;

	float left   = +(temporary.x_ - scale.x_); // ��
	float right  = +(temporary.x_ + scale.x_); // �E
	float top    = -(temporary.y_ + scale.y_); // ��
	float bottom = -(temporary.y_ - scale.y_); // ��

	// ���ړ����W�ŃA�^������
	return CollisionMap(left, right, top, bottom);
}
bool MapChip::CollisionMap(const float left, const float right, const float top, const float bottom)
{
	// �㉺���E�̃}�b�v�`�b�v�ł̈ʒu
	int leftNum   = static_cast<int>(left   / (chipScale_.x_ * 2.0f)); // ��
	int rightNum  = static_cast<int>(right  / (chipScale_.x_ * 2.0f)); // �E
	int topNum    = static_cast<int>(top    / (chipScale_.y_ * 2.0f)); // ��
	int bottomNum = static_cast<int>(bottom / (chipScale_.y_ * 2.0f)); // ��

	// �㉺���E�͈͓��ɂ��邩
	bool L = (0 <= leftNum   && leftNum   < pMapData_->chipNums_[0].size()); // ��
	bool R = (0 <= rightNum  && rightNum  < pMapData_->chipNums_[0].size()); // �E
	bool T = (0 <= topNum    && topNum    < pMapData_->chipNums_.size());    // ��
	bool B = (0 <= bottomNum && bottomNum < pMapData_->chipNums_.size());    // ��

	// �������Ă��邩
	bool isCollTL = false, isCollTR = false, isCollBL = false, isCollBR = false;
	if (T && L) { isCollTL = CollisionChip(leftNum , topNum); }    // ����
	if (T && R) { isCollTR = CollisionChip(rightNum, topNum); }    // �E��
	if (B && L) { isCollBL = CollisionChip(leftNum , bottomNum); } // ����
	if (B && R) { isCollBR = CollisionChip(rightNum, bottomNum); } // �E��

	return (isCollTL || isCollTR || isCollBL || isCollBR);
}
bool MapChip::CollisionChip(const int x, const int y)
{
	// �A�^��
	if (pMapData_->chipNums_[y][x] == 1)
	{
		pMapData_->chipColls_[y][x] = true;
		return true; 
	}
	if (pMapData_->chipNums_[y][x] == 2)
	{
		pMapData_->chipColls_[y][x] = true;
		return true;
	}

	// �n�Y��
	pMapData_->chipColls_[y][x] = false;
	return false;
}

void MapChip::Draw()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �}�b�v�f�[�^�����[�h����Ă��Ȃ��Ȃ�e��
	if (pMapData_->isLoaded_ == false) { return; }

	// �`��
	for (size_t i = 0; i < chips_.size(); i++)
	{
	}
}

YMath::Vector2 MapChip::Size()
{
	return Vector2(
		chipScale_.x_ * pMapData_->chipNums_[0].size(), 
		chipScale_.y_ * pMapData_->chipNums_.size()
	);
}

#pragma endregion


#pragma region MapChip2DDisplayer

void MapChip2DDisplayer::Initialize(MapData* pMapData)
{
	// null�`�F�b�N
	assert(pMapData);
	// ���
	pMapData_ = pMapData;

	std::vector<std::vector<int>> nums = pMapData_->chipNums_;

	// ----- �I�u�W�F�N�g + �F----- //
	// �S���� + ���T�C�Y
	chips_.clear();
	chips_.resize(nums.size());

	// �ЂƂ��ݒ� + ����
	float posX = 0.0f, posY = 0.0f, scale = 1.0f;
	for (size_t y = 0; y < nums.size(); y++)
	{
		for (size_t x = 0; x < nums[y].size(); x++)
		{
			std::unique_ptr<Chip> chip = nullptr;
			chip.reset(new Chip());

			// �I�u�W�F�N�g
			//posX = +(scale * pMapData_->pSprites_[nums[y][x]]->Size().x_) * x;
			//posY = +(scale * pMapData_->pSprites_[nums[y][x]]->Size().y_) * y;

			chip->obj_.reset(Sprite2D::Object::Create({ {posX,posY,0.0f},{},{scale,scale,1.0f} }));

			// �F
			chip->color_.reset(CBColor::Create());

			// 1�Ԍ��ɑ}��
			chips_[y].push_back(std::move(chip));
		}
	}
}

void MapChip2DDisplayer::Update()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �}�b�v�f�[�^�����[�h����Ă��Ȃ��Ȃ�e��
	if (pMapData_->isLoaded_ == false) { return; }

	// �X�V
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			chips_[y][x]->obj_->UpdateMatrix();
		}
	}
}

void MapChip2DDisplayer::Draw()
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

	// �}�b�v�f�[�^�����[�h����Ă��Ȃ��Ȃ�e��
	if (pMapData_->isLoaded_ == false) { return; }

	// �`��
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			// �}�b�v�ԍ��ɑΉ�����X�v���C�g�ŕ`��
			int idx = pMapData_->chipNums_[y][x] - 1;
			//pMapData_->pSprites_[idx]->Draw(chips_[y][x]->obj_.get());
		}
	}
}

#pragma endregion