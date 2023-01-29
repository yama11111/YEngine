#include "MapChip.h"
#include <cassert>
#include <fstream>
#include "YMath.h"

using YMath::Vec2;
using YMath::Vec3;
using YMath::Vec4;
using YGame::ObjectModel;

void MapChipInfo::LoadData(const std::string fileName)
{
	// vectorクリア
	chipNums_.clear();

	FILE* fp = nullptr;
	errno_t err;

	// 読み込み用ファイルを開く
	const std::string& directoryPath = "Resources/MapData/";
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

	leftTop_ = state.leftTop_;
	chipSize_ = state.chipSize_;

	Reset();
}

void MapChip::Reset()
{
	// 3D
	chips_.clear();
	
	for (size_t y = 0; y < chipNums_.size(); y++)
	{
		for (size_t z = 0; z < chipNums_[y].size(); z++)
		{
			if (chipNums_[y][z] == 1)
			{
				std::unique_ptr<ObjectModel> newChip = std::make_unique<ObjectModel>();

				float posZ = +(chipSize_.z_ * 2.0f) * z + chipSize_.z_ + leftTop_.z_;
				float posY = -(chipSize_.y_ * 2.0f) * y - chipSize_.y_ + leftTop_.y_;

				newChip->Initialize({ {leftTop_.x_,posY,posZ},{},chipSize_ });
				chips_.push_back(std::move(newChip));
			}
		}
	}

	rect_ = Vec2(chipSize_.z_ * chipNums_[0].size(), chipSize_.y_ * chipNums_.size());

	// 2D
	//chip2Ds_.clear();
	//chip2Ds_.resize(chipNums_.size());
	//for (size_t i = 0; i < chip2Ds_.size(); i++)
	//{
	//	chip2Ds_[i].resize(chipNums_[i].size());
	//}

	//float pos2DX = 0.0f, pos2DY = 0.0f, scale2D = 1.0f;
	//for (size_t y = 0; y < chip2Ds_.size(); y++)
	//{
	//	for (size_t x = 0; x < chip2Ds_[y].size(); x++)
	//	{
	//		pos2DX = +(scale2D * pSprite_->Size().x_) * x;
	//		pos2DY = +(scale2D * pSprite_->Size().y_) * y;

	//		Vec4 color = { 0.5f,0.5f,0.5f,1.0f };
	//		if (chipNums_[y][x] == 0) { color = { 0.5f,0.5f,1.0f,0.5f }; }

	//		chip2Ds_[y][x].Initialize({ {pos2DX,pos2DY,0.0f},{},{scale2D,scale2D,scale2D} }, color);
	//	}
	//}
}

void MapChip::Update()
{
	for (size_t i = 0; i < chips_.size(); i++)
	{
		chips_[i]->UpdateMatrix();
	}

	//for (size_t y = 0; y < chip2Ds_.size(); y++)
	//{
	//	for (size_t x = 0; x < chip2Ds_[y].size(); x++)
	//	{
	//		chip2Ds_[y][x].color_.r_ = 0.5f;
	//		chip2Ds_[y][x].Update();
	//	}
	//}
}

void MapChip::PerfectPixelCollision(MapChipCollider& collider)
{
	Vec3& posRef = collider.PosRef();
	Vec3 scale = collider.Scale();
	Vec3& speedRef = collider.SpeedRef();

	// ぶつかっているか
	bool isCollY = CollisionTemporaryMap(posRef, scale, { 0,speedRef.y_,0 }); // y
	bool isCollZ = CollisionTemporaryMap(posRef, scale, { 0,0,speedRef.z_ }); // z

	// 過去地面フラグ設定
	collider.SetIsElderLanding(collider.IsLanding());
	// 地面フラグ設定 (Y方向にマップチップ && スピードが -)
	collider.SetIsLanding((isCollY && speedRef.y_ <= 0.0f));

	// ぶつかっていないならスキップ
	if (isCollY == false && isCollZ == false) { return; }

	// 近づく移動量
	YMath::Vec3 approach = speedRef / 100.0f;

	// 押し戻し処理
	while (true)
	{
		// ぶつかっているか (仮移動)
		bool isCollTempY = CollisionTemporaryMap(posRef, scale, { 0,approach.y_,0 }); // y
		bool isCollTempZ = CollisionTemporaryMap(posRef, scale, { 0,0,approach.z_ }); // z

		// ぶつかっているならループ抜ける
		if (isCollTempY || isCollTempZ) { break; }

		// 少しづつ近づける
		if (isCollY) { posRef.y_ += approach.y_; }
		if (isCollZ) { posRef.z_ += approach.z_; }
	}

	// 速度リセット
	if (isCollY) { speedRef.y_ = 0.0f; }
	if (isCollZ) { speedRef.z_ = 0.0f; }
}

bool MapChip::CollisionTemporaryMap(const Vec3& pos, const Vec3 scale, const Vec3& spd)
{
	// 仮移動座標
	Vec3 temporary = pos + spd - leftTop_;

	float left   = +(temporary.z_ - scale.z_); // 左
	float right  = +(temporary.z_ + scale.z_); // 右
	float top    = -(temporary.y_ + scale.y_); // 上
	float bottom = -(temporary.y_ - scale.y_); // 下

	return CollisionMap(left, right, top, bottom);
}

bool MapChip::CollisionMap(const float left, const float right, const float top, const float bottom)
{
	if (chipNums_.empty()) { return false; }

	// 上下左右のマップチップでの位置
	int leftNum   = static_cast<int>(left   / (chipSize_.z_ * 2.0f)); // 左
	int rightNum  = static_cast<int>(right  / (chipSize_.z_ * 2.0f)); // 右
	int topNum    = static_cast<int>(top    / (chipSize_.y_ * 2.0f)); // 上
	int bottomNum = static_cast<int>(bottom / (chipSize_.y_ * 2.0f)); // 下

	// 上下左右範囲内にいるか
	bool L = (0 <= leftNum   && leftNum   < chipNums_[0].size()); // 左
	bool R = (0 <= rightNum  && rightNum  < chipNums_[0].size()); // 右
	bool T = (0 <= topNum    && topNum    < chipNums_.size());    // 上
	bool B = (0 <= bottomNum && bottomNum < chipNums_.size());    // 下

	// 当たっているか
	bool isCollTL = false, isCollTR = false, isCollBL = false, isCollBR = false;
	if (T && L) { isCollTL = CollisionChip(leftNum , topNum); }    // 左上
	if (T && R) { isCollTR = CollisionChip(rightNum, topNum); }    // 右上
	if (B && L) { isCollBL = CollisionChip(leftNum , bottomNum); } // 左下
	if (B && R) { isCollBR = CollisionChip(rightNum, bottomNum); } // 右下

	return (isCollTL || isCollTR || isCollBL || isCollBR);
}

bool MapChip::CollisionChip(const int x, const int y)
{
	// 色替え
	/*chip2Ds_[y][x].color_.r_ = 1.0f;*/

	if (chipNums_[y][x] == 1) { return true; }
	return false;
}

void MapChip::Draw(const YGame::ViewProjection& vp)
{
	for (size_t i = 0; i < chips_.size(); i++)
	{
		//pModel_->Draw(*chips_[i], vp, tex_);
	}
}

void MapChip::Draw2D()
{
	//for (size_t y = 0; y < chip2Ds_.size(); y++)
	//{
	//	for (size_t x = 0; x < chip2Ds_[y].size(); x++)
	//	{
	//		pSprite_->Draw(chip2Ds_[y][x]);
	//	}
	//}
}
