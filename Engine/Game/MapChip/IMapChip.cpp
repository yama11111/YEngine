#include "IMapChip.h"
#include <cassert>
#include <fstream>
#include "YMath.h"

using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YGame::MapData;
using YGame::IMapChip;

#pragma region MapData

void MapData::LoadCSV(const std::string& mapFileName)
{
	// �N���A
	Clear();

	// �t�@�C��
	FILE* fp = nullptr;

	// �p�X
	static const std::string& directoryPath = "Resources/MapData/";
	std::string filePath = directoryPath + mapFileName;
	
	// �ǂݍ��ݗp�t�@�C�����J��
	errno_t err = fopen_s(&fp, filePath.c_str(), "r");
	
	// �t�@�C���������Ȃ�G���[
	assert(err == 0);

	// �ۑ��p
	std::vector<uint16_t> column;
	
	// �t�@�C���I�[�܂œǂݍ���
	while (true)
	{
		// �����擾
		int16_t c = fgetc(fp);

		// ��
		if (c == ',') 
		{
			// �������
			continue; 
		}
		// �s
		if (c == '\n')
		{
			// �{�̂ɑ}��
			chipNums_.push_back(column);
			
			// �ۑ��p�N���A
			column.clear();
			
			// �������
			continue;
		}
		// �I�[
		if (c == EOF) 
		{
			// �{�̂ɑ}��
			chipNums_.push_back(column);
			
			// �I��
			break; 
		}

		// �ۑ��p�ɑ}��
		column.push_back(static_cast<uint16_t>(c - 48));
	}

	// �t�@�C�������
	fclose(fp);
}

void MapData::Clear()
{
	if (chipNums_.empty() == false) 
	{
		chipNums_.clear(); 
	}
}

#pragma endregion


#pragma region IMapChip

void IMapChip::Initialize(MapData* pMapData, const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	// null�`�F�b�N
	assert(pMapData);
	// ���
	pMapData_ = pMapData;

	// ���
	leftTop_ = leftTop;
	chipScale_ = chipScale;

	// ���Z�b�g
	Reset();
}

void IMapChip::Initialize(MapData* pMapData)
{
	// null�`�F�b�N
	assert(pMapData);
	// ���
	pMapData_ = pMapData;

	// ���Z�b�g
	Reset();
}

void IMapChip::Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	// ���
	leftTop_ = leftTop;
	chipScale_ = chipScale;

	// ���Z�b�g
	Reset();
}

void IMapChip::PerfectPixelCollision(MapChipCollider& collider)
{
	// �}�b�v�f�[�^��null�Ȃ�e��
	if (pMapData_ == nullptr) { return; }

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

bool IMapChip::CollisionTemporaryMap(const Vector3& pos, const Vector3& scale, const Vector3& spd)
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

bool IMapChip::CollisionMap(const float left, const float right, const float top, const float bottom)
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

bool IMapChip::CollisionChip(const int x, const int y)
{
	// 0�Ȃ�e��
	if (pMapData_->chipNums_[y][x] == 0) { return false; }

	// �A�^��
	return true;
}

YMath::Vector2 IMapChip::Size()
{
	return Vector2(
		chipScale_.x_ * pMapData_->chipNums_[0].size(), 
		chipScale_.y_ * pMapData_->chipNums_.size()
	);
}

#pragma endregion