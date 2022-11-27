#include "Map.h"
#include <cassert>
#include <fstream>
#include "YMath.h"

void MapInfo::Load(const std::string fileName)
{
	// vectorクリア
	chipNums_.clear();

	FILE* fp = nullptr;
	errno_t err;

	// 読み込み用ファイルを開く
	const std::string& directoryPath = "Map/Data/";
	std::string filePath = directoryPath + fileName;
	err = fopen_s(&fp, filePath.c_str(), "r");

	// ファイルが無いならエラー
	if (err != 0)
	{
		assert(false);
		return;
	}

	// ファイル終端まで読み込み
	int c = 0;
	std::vector<int> column;
	while (true)
	{
		// 文字取得
		c = fgetc(fp);

		// 列
		if (c == ',') { continue; }
		// 行
		if (c == '\n')
		{
			chipNums_.push_back(column);
			column.clear();
			continue;
		}
		// 終端
		if (c == EOF) 
		{
			chipNums_.push_back(column);
			break; 
		}

		// 挿入
		column.push_back(c - 48);
	}

	// ファイルを閉じる
	fclose(fp);

	isLoaded_ = true;
}

void Map::Initialize(const InitStatus& state)
{
	assert(isLoaded_);
	assert(state.pModel_);

	chipSize_ = state.chipSize_;
	pModel_ = state.pModel_;
	tex_ = state.tex_;

	Reset(state.leftTop_);
}

void Map::Reset(const Math::Vec3& leftTop)
{
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
			posY = -(scale * 2.0f) * y + scale + leftTop.y_;
			chips_[y][x].Initialize({ {leftTop.x_,posY,posZ},{},{scale,scale,scale} });
		}
	}
	rect_ = Math::Vec2(chipSize_ * chipNums_[0].size(), chipSize_ * chipNums_.size());
}

void Map::Update()
{
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			chips_[y][x].Update();
		}
	}
}

void Map::Draw(const Game::ViewProjection& vp)
{
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			if (chipNums_[y][x] == 1) { pModel_->Draw(chips_[y][x], vp, tex_); }
		}
	}
}

void Map::PerfectPixelCollision(Math::Vec3& pos, const Math::Vec3 scale, Math::Vec2& spd)
{
	// x 方向
	if (TemporaryChipCollision(pos, scale, { spd.x_,0.0f }))
	{
		while (!TemporaryChipCollision(pos, scale, { Math::Sign(spd.x_),0.0f }))
		{
			pos.z_ += Math::Sign(spd.x_) / 10.0f;
		}
		spd.x_ = 0.0f;
	}
	// y 方向
	if (TemporaryChipCollision(pos, scale, { 0.0f, spd.y_ }))
	{
		while (!TemporaryChipCollision(pos, scale, { 0.0f,Math::Sign(spd.y_) }))
		{
			pos.y_ += Math::Sign(spd.y_) / 10.0f;
		}
		spd.y_ = 0.0f;
	}

	// x y 
	if (TemporaryChipCollision(pos, scale, spd))
	{
		while (!TemporaryChipCollision(pos, scale, { Math::Sign(spd.x_),Math::Sign(spd.y_) }))
		{
			pos.z_ += Math::Sign(spd.x_) / 10.0f;
			pos.y_ += Math::Sign(spd.y_) / 10.0f;
		}
		spd.x_ = 0.0f;
		spd.y_ = 0.0f;
	}
}

bool Map::TemporaryChipCollision(Math::Vec3& pos, const Math::Vec3 scale, const Math::Vec2& spd)
{
	float left   = pos.z_ - scale.z_ + spd.x_;
	float right  = pos.z_ + scale.z_ + spd.x_;
	float top    = pos.y_ - scale.y_ + spd.y_;
	float bottom = pos.y_ + scale.y_ + spd.y_;

	return ChipCollision(left, right, top, bottom);
}

bool Map::ChipCollision(const float left, const float right, const float top, const float bottom)
{
	if (chipNums_.empty()) { return false; }

	int leftNum   = static_cast<int>(left   / chipSize_);
	int rightNum  = static_cast<int>(right  / chipSize_);
	int topNum    = static_cast<int>(top    / chipSize_);
	int bottomNum = static_cast<int>(bottom / chipSize_);

	if (chipNums_[topNum   ][leftNum ]) { return true; }
	if (chipNums_[topNum   ][rightNum]) { return true; }
	if (chipNums_[bottomNum][leftNum ]) { return true; }
	if (chipNums_[bottomNum][rightNum]) { return true; }

	return false;
}
