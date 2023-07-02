#include "IMapChip.h"
#include "MapChipCollisionBitConfig.h"
#include "YMath.h"
#include <cassert>
#include <fstream>

using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YGame::MapData;
using YGame::IMapChip;

#pragma region MapData

void MapData::LoadCSV(const std::string& mapFileName)
{
	// クリア
	Clear();

	// ファイル
	FILE* fp = nullptr;

	// パス
	static const std::string& directoryPath = "Resources/MapData/";
	std::string filePath = directoryPath + mapFileName;
	
	// 読み込み用ファイルを開く
	errno_t err = fopen_s(&fp, filePath.c_str(), "r");
	
	// ファイルが無いならエラー
	assert(err == 0);

	// 保存用
	std::vector<uint16_t> column;
	
	// ファイル終端まで読み込み
	while (true)
	{
		// 文字取得
		int16_t c = fgetc(fp);

		// 列
		if (c == ',') 
		{
			// もう一回
			continue; 
		}
		// 行
		if (c == '\n')
		{
			// 本体に挿入
			chipNums_.push_back(column);
			
			// 保存用クリア
			column.clear();
			
			// もう一回
			continue;
		}
		// 終端
		if (c == EOF) 
		{
			// 本体に挿入
			chipNums_.push_back(column);
			
			// 終了
			break; 
		}

		// 保存用に挿入
		column.push_back(static_cast<uint16_t>(c - 48));
	}

	// ファイルを閉じる
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
	// nullチェック
	assert(pMapData);
	// 代入
	pMapData_ = pMapData;

	// 代入
	leftTop_ = leftTop;
	chipScale_ = chipScale;

	// リセット
	Reset();
}

void IMapChip::Initialize(MapData* pMapData)
{
	// nullチェック
	assert(pMapData);
	// 代入
	pMapData_ = pMapData;

	// リセット
	Reset();
}

void IMapChip::Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	// 代入
	leftTop_ = leftTop;
	chipScale_ = chipScale;

	// リセット
	Reset();
}

void IMapChip::PerfectPixelCollision(MapChipCollider& collider)
{
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// 代入
	Vector3& posRef = collider.PosRef();
	Vector3 scale = collider.Scale();
	Vector3& speedRef = collider.SpeedRef();

	// アタリ判定ビット 1F 前 を記録
	collider.SetCollisionBit(collider.CollisionBit() << 4);

	// ぶつかっているか
	bool isCollX = CollisionTemporaryMap(posRef, scale, { speedRef.x_,0,0 }); // x
	bool isCollY = CollisionTemporaryMap(posRef, scale, { 0,speedRef.y_,0 }); // y

	// ぶつかっていないならスキップ
	if (isCollX == false && isCollY == false) { return; }

	// アタリ判定ビット
	uint8_t colBit = collider.CollisionBit();

	// 跳ね返らないなら
	if (collider.IsBounce() == false) 
	{
		// X軸判定なら
		if (isCollX)
		{
			// ビット更新
			if (speedRef.x_ >= 0.0f) { colBit |= ChipCollisionBit::kRight; }
			if (speedRef.x_ <= 0.0f) { colBit |= ChipCollisionBit::kLeft; }
		}

		// Y軸判定ならs
		if (isCollY)
		{
			// ビット更新
			if (speedRef.y_ >= 0.0f) { colBit |= ChipCollisionBit::kTop; }
			if (speedRef.y_ <= 0.0f) { colBit |= ChipCollisionBit::kBottom; }
		}

		// アタリ判定ビット 現在F を記録
		collider.SetCollisionBit(colBit);

		return;
	}

	// 近づく移動量
	YMath::Vector3 approach = speedRef / 100.0f;

	// 押し戻し処理
	while (true)
	{
		// ぶつかっているか (仮移動)
		bool isCollTempX = CollisionTemporaryMap(posRef, scale, { approach.x_,0,0 }); // x
		bool isCollTempY = CollisionTemporaryMap(posRef, scale, { 0,approach.y_,0 }); // y

		// ぶつかっているならループ抜ける
		if (isCollTempX || isCollTempY) { break; }

		// 少しづつ近づける
		if (isCollX) { posRef.x_ += approach.x_; }
		if (isCollY) { posRef.y_ += approach.y_; }
	}

	// X軸判定なら
	if (isCollX)
	{
		// ビット更新
		if (speedRef.x_ >= 0.0f) { colBit |= ChipCollisionBit::kRight; }
		if (speedRef.x_ <= 0.0f) { colBit |= ChipCollisionBit::kLeft; }

		// 速度リセット
		speedRef.x_ = 0.0f;
	}

	// Y軸判定ならs
	if (isCollY)
	{
		// ビット更新
		if (speedRef.y_ >= 0.0f) { colBit |= ChipCollisionBit::kTop; }
		if (speedRef.y_ <= 0.0f) { colBit |= ChipCollisionBit::kBottom; }

		// 速度リセット
		speedRef.y_ = 0.0f;
	}
	
	// アタリ判定ビット 現在F を記録
	collider.SetCollisionBit(colBit);
}

bool IMapChip::CollisionTemporaryMap(const Vector3& pos, const Vector3& scale, const Vector3& spd)
{
	// 仮移動座標
	Vector3 temporary = pos + spd - leftTop_;

	float left   = +(temporary.x_ - scale.x_); // 左
	float right  = +(temporary.x_ + scale.x_); // 右
	float top    = -(temporary.y_ + scale.y_); // 上
	float bottom = -(temporary.y_ - scale.y_); // 下

	// 仮移動座標でアタリ判定
	return CollisionMap(left, right, top, bottom);
}

bool IMapChip::CollisionMap(const float left, const float right, const float top, const float bottom)
{
	// チップサイズ
	Vector3 chipSize = chipScale_ * 2.0f;

	// 上下左右のマップチップでの位置
	int leftNum   = static_cast<int>(left   / chipSize.x_); // 左
	int rightNum  = static_cast<int>(right  / chipSize.x_); // 右
	int topNum    = static_cast<int>(top    / chipSize.y_); // 上
	int bottomNum = static_cast<int>(bottom / chipSize.y_); // 下

	// 上下左右範囲内にいるか
	bool L = (0 <= leftNum   && leftNum   < pMapData_->chipNums_[0].size()); // 左
	bool R = (0 <= rightNum  && rightNum  < pMapData_->chipNums_[0].size()); // 右
	bool T = (0 <= topNum    && topNum    < pMapData_->chipNums_.size());    // 上
	bool B = (0 <= bottomNum && bottomNum < pMapData_->chipNums_.size());    // 下

	// 当たっているか
	bool isCollTL = false, isCollTR = false, isCollBL = false, isCollBR = false;
	
	if (T && L) { isCollTL = CollisionChip(leftNum , topNum); }    // 左上
	if (T && R) { isCollTR = CollisionChip(rightNum, topNum); }    // 右上
	if (B && L) { isCollBL = CollisionChip(leftNum , bottomNum); } // 左下
	if (B && R) { isCollBR = CollisionChip(rightNum, bottomNum); } // 右下

	return (isCollTL || isCollTR || isCollBL || isCollBR);
}

YMath::Vector2 IMapChip::Size()
{
	return Vector2(
		chipScale_.x_ * pMapData_->chipNums_[0].size(), 
		chipScale_.y_ * pMapData_->chipNums_.size()
	);
}

#pragma endregion