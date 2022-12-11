#include "MapChip.h"
#include <cassert>
#include <fstream>
#include "YMath.h"

void MapChipInfo::LoadData(const std::string fileName)
{
	// vector�N���A
	chipNums_.clear();

	FILE* fp = nullptr;
	errno_t err;

	// �ǂݍ��ݗp�t�@�C�����J��
	const std::string& directoryPath = "MapChip/Data/";
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

	isLoaded_ = true;
}

void MapChip::Load(const LoadStatus& state)
{
	assert(state.pModel_);
	assert(state.pSprite_);

	LoadData(state.mapFileName_);
	pModel_ = state.pModel_;
	tex_ = state.tex_;
	pSprite_ = state.pSprite_;
}

void MapChip::Initialize(const InitStatus& state)
{
	assert(isLoaded_);

	chipSize_ = state.chipSize_;

	Reset(state.leftTop_);
}

void MapChip::Reset(const Math::Vec3& leftTop)
{
	// 3D
	chips_.clear();
	chips_.resize(chipNums_.size());
	for (size_t i = 0; i < chips_.size(); i++)
	{
		chips_[i].resize(chipNums_[i].size());
	}

	float posZ = 0.0f, posY = 0.0f, scale = chipSize_;
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			posZ = +(scale * 2.0f) * x + scale + leftTop.z_;
			posY = -(scale * 2.0f) * y - scale + leftTop.y_;

			chips_[y][x].Initialize({ {leftTop.x_,posY,posZ},{},{scale,scale,scale} }, { 1.0f,1.0f,1.0f,0.5f });
		}
	}
	rect_ = Math::Vec2(chipSize_ * chipNums_[0].size(), chipSize_ * chipNums_.size());

	leftTop_ = leftTop;

	// 2D
	chip2Ds_.clear();
	chip2Ds_.resize(chipNums_.size());
	for (size_t i = 0; i < chip2Ds_.size(); i++)
	{
		chip2Ds_[i].resize(chipNums_[i].size());
	}

	float pos2DX = 0.0f, pos2DY = 0.0f, scale2D = 1.0f;
	for (size_t y = 0; y < chip2Ds_.size(); y++)
	{
		for (size_t x = 0; x < chip2Ds_[y].size(); x++)
		{
			pos2DX = +(scale2D * pSprite_->Size().x_) * x;
			pos2DY = +(scale2D * pSprite_->Size().y_) * y;

			Math::Vec4 color = { 0.5f,0.5f,0.5f,1.0f };
			if (chipNums_[y][x] == 0) { color = { 0.5f,0.5f,1.0f,0.5f }; }

			chip2Ds_[y][x].Initialize({ {pos2DX,pos2DY,0.0f},{},{scale2D,scale2D,scale2D} }, color);
		}
	}
}

void MapChip::Update()
{
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			chips_[y][x].Update();
		}
	}

	for (size_t y = 0; y < chip2Ds_.size(); y++)
	{
		for (size_t x = 0; x < chip2Ds_[y].size(); x++)
		{
			chip2Ds_[y][x].color_.r_ = 0.5f;
			chip2Ds_[y][x].Update();
		}
	}
}

void MapChip::PerfectPixelCollision(MapChipCollider& collider)
{
	Math::Vec3& posRef = collider.PosRef();
	Math::Vec3 scale = collider.Scale();
	Math::Vec3& speedRef = collider.SpeedRef();

	// �Ԃ����Ă��邩
	bool isCollY = CollisionTemporaryMap(posRef, scale, { 0,speedRef.y_,0 }); // y
	bool isCollZ = CollisionTemporaryMap(posRef, scale, { 0,0,speedRef.z_ }); // z

	// �n�ʃt���O�ݒ� (Y�����Ƀ}�b�v�`�b�v && �X�s�[�h�� -)
	collider.SetIsLanding((isCollY && speedRef.y_ <= 0.0f));

	// �Ԃ����Ă��Ȃ��Ȃ�X�L�b�v
	if (isCollY == false && isCollZ == false) { return; }

	// �߂Â��ړ���
	Math::Vec3 approach = speedRef / 100.0f;

	// �����߂�����
	while (true)
	{
		// �Ԃ����Ă��邩 (���ړ�)
		bool isCollTempY = CollisionTemporaryMap(posRef, scale, { 0,approach.y_,0 }); // y
		bool isCollTempZ = CollisionTemporaryMap(posRef, scale, { 0,0,approach.z_ }); // z

		// �Ԃ����Ă���Ȃ烋�[�v������
		if (isCollTempY || isCollTempZ) { break; }

		// �����Â߂Â���
		if (isCollY) { posRef.y_ += approach.y_; }
		if (isCollZ) { posRef.z_ += approach.z_; }
	}

	// ���x���Z�b�g
	if (isCollY) { speedRef.y_ = 0.0f; }
	if (isCollZ) { speedRef.z_ = 0.0f; }
}

bool MapChip::CollisionTemporaryMap(const Math::Vec3& pos, const Math::Vec3 scale, const Math::Vec3& spd)
{
	// ���ړ����W
	Math::Vec3 temporary = pos + spd - leftTop_;

	float left   = +(temporary.z_ - scale.z_); // ��
	float right  = +(temporary.z_ + scale.z_); // �E
	float top    = -(temporary.y_ + scale.y_); // ��
	float bottom = -(temporary.y_ - scale.y_); // ��

	return CollisionMap(left, right, top, bottom);
}

bool MapChip::CollisionMap(const float left, const float right, const float top, const float bottom)
{
	if (chipNums_.empty()) { return false; }

	// �㉺���E�̃}�b�v�`�b�v�ł̈ʒu
	int leftNum   = static_cast<int>(left   / (chipSize_ * 2.0f)); // ��
	int rightNum  = static_cast<int>(right  / (chipSize_ * 2.0f)); // �E
	int topNum    = static_cast<int>(top    / (chipSize_ * 2.0f)); // ��
	int bottomNum = static_cast<int>(bottom / (chipSize_ * 2.0f)); // ��

	// �㉺���E�͈͓��ɂ��邩
	bool L = (0 <= leftNum   && leftNum   < chipNums_[0].size()); // ��
	bool R = (0 <= rightNum  && rightNum  < chipNums_[0].size()); // �E
	bool T = (0 <= topNum    && topNum    < chipNums_.size());    // ��
	bool B = (0 <= bottomNum && bottomNum < chipNums_.size());    // ��

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
	// �F�ւ�
	chip2Ds_[y][x].color_.r_ = 1.0f;

	if (chipNums_[y][x] == 1) { return true; }
	return false;
}

void MapChip::Draw(const Game::ViewProjection& vp)
{
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			DrawChip(x, y, vp);
		}
	}
}

void MapChip::DrawChip(const size_t x, const size_t y, const Game::ViewProjection& vp)
{
	if (chipNums_[y][x] == 0) { return; }
	if (chipNums_[y][x] == 1) { pModel_->Draw(chips_[y][x], vp, tex_); }

}

void MapChip::Draw2D()
{
	for (size_t y = 0; y < chip2Ds_.size(); y++)
	{
		for (size_t x = 0; x < chip2Ds_[y].size(); x++)
		{
			pSprite_->Draw(chip2Ds_[y][x]);
		}
	}
}
