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
	// クリア
	Clear();

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

	chipColls_.clear();
	chipColls_.resize(chipNums_.size());
	for (size_t i = 0; i < chipColls_.size(); i++)
	{
		chipColls_[i].resize(chipNums_[i].size());
	}

	// 読み込み完了
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
	// nullチェック
	assert(pMapData);
	// 代入
	pMapData_ = pMapData;

	// 初期化
	Initialize(leftTop, chipScale);
}
void MapChip::Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	// 代入
	leftTop_ = leftTop;
	chipScale_ = chipScale;

	// リセット
	Reset();
}
void MapChip::Reset()
{
	// nullチェック
	assert(pMapData_);
	
	// 番号
	std::vector<std::vector<int>> nums = pMapData_->chipNums_;

	// 全消去 + リサイズ
	chips_.clear();

	// ひとつずつ設定 + 生成
	for (size_t y = 0; y < nums.size(); y++)
	{
		for (size_t x = 0; x < nums[y].size(); x++)
		{
			// 無じゃないなら
			if (nums[y][x] != 0)
			{
				std::unique_ptr<Chip> chip = nullptr;
				chip.reset(new Chip());

				// オブジェクト
				float posX = +(chipScale_.x_ * 2.0f) * x + chipScale_.x_;
				float posY = -(chipScale_.y_ * 2.0f) * y - chipScale_.y_;

				chip->transform_.reset(new Transform());
				chip->transform_->Initialize({ {posX,posY,0.0f},{},chipScale_ });
				chip->transform_->pos_ += leftTop_;

				// 1番後ろに挿入
				chips_.push_back(std::move(chip));
			}
		}
	}
}

void MapChip::Update()
{
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// マップデータがロードされていないなら弾く
	if (pMapData_->isLoaded_ == false) { return; }

	// 更新
	for (size_t i = 0; i < chips_.size(); i++)
	{
		chips_[i]->transform_->UpdateMatrix();
	}
}

void MapChip::PerfectPixelCollision(MapChipCollider& collider)
{
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// マップデータがロードされていないなら弾く
	if (pMapData_->isLoaded_ == false) { return; }

	// 代入
	Vector3& posRef = collider.PosRef();
	Vector3 scale = collider.Scale();
	Vector3& speedRef = collider.SpeedRef();

	// ぶつかっているか
	bool isCollX = CollisionTemporaryMap(posRef, scale, { speedRef.x_,0,0 }); // x
	bool isCollY = CollisionTemporaryMap(posRef, scale, { 0,speedRef.y_,0 }); // y

	// 過去地面フラグ設定
	collider.SetIsElderLanding(collider.IsLanding());
	// 地面フラグ設定 (Y方向にマップチップ && スピードが -)
	collider.SetIsLanding((isCollY && speedRef.y_ <= 0.0f));

	// ぶつかっていないならスキップ
	if (isCollX == false && isCollY == false) { return; }

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

	// 速度リセット
	if (isCollX) { speedRef.x_ = 0.0f; }
	if (isCollY) { speedRef.y_ = 0.0f; }
}
bool MapChip::CollisionTemporaryMap(const Vector3& pos, const Vector3 scale, const Vector3& spd)
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
bool MapChip::CollisionMap(const float left, const float right, const float top, const float bottom)
{
	// 上下左右のマップチップでの位置
	int leftNum   = static_cast<int>(left   / (chipScale_.x_ * 2.0f)); // 左
	int rightNum  = static_cast<int>(right  / (chipScale_.x_ * 2.0f)); // 右
	int topNum    = static_cast<int>(top    / (chipScale_.y_ * 2.0f)); // 上
	int bottomNum = static_cast<int>(bottom / (chipScale_.y_ * 2.0f)); // 下

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
bool MapChip::CollisionChip(const int x, const int y)
{
	// アタリ
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

	// ハズレ
	pMapData_->chipColls_[y][x] = false;
	return false;
}

void MapChip::Draw()
{
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// マップデータがロードされていないなら弾く
	if (pMapData_->isLoaded_ == false) { return; }

	// 描画
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
	// nullチェック
	assert(pMapData);
	// 代入
	pMapData_ = pMapData;

	std::vector<std::vector<int>> nums = pMapData_->chipNums_;

	// ----- オブジェクト + 色----- //
	// 全消去 + リサイズ
	chips_.clear();
	chips_.resize(nums.size());

	// ひとつずつ設定 + 生成
	float posX = 0.0f, posY = 0.0f, scale = 1.0f;
	for (size_t y = 0; y < nums.size(); y++)
	{
		for (size_t x = 0; x < nums[y].size(); x++)
		{
			std::unique_ptr<Chip> chip = nullptr;
			chip.reset(new Chip());

			// オブジェクト
			//posX = +(scale * pMapData_->pSprites_[nums[y][x]]->Size().x_) * x;
			//posY = +(scale * pMapData_->pSprites_[nums[y][x]]->Size().y_) * y;

			chip->obj_.reset(Sprite2D::Object::Create({ {posX,posY,0.0f},{},{scale,scale,1.0f} }));

			// 色
			chip->color_.reset(CBColor::Create());

			// 1番後ろに挿入
			chips_[y].push_back(std::move(chip));
		}
	}
}

void MapChip2DDisplayer::Update()
{
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// マップデータがロードされていないなら弾く
	if (pMapData_->isLoaded_ == false) { return; }

	// 更新
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
	// マップデータがnullなら弾く
	if (pMapData_ == nullptr) { return; }

	// マップデータがロードされていないなら弾く
	if (pMapData_->isLoaded_ == false) { return; }

	// 描画
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			// マップ番号に対応するスプライトで描画
			int idx = pMapData_->chipNums_[y][x] - 1;
			//pMapData_->pSprites_[idx]->Draw(chips_[y][x]->obj_.get());
		}
	}
}

#pragma endregion