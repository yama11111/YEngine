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

void MapData::Load(const std::string fileName, const std::vector<Model*>& pModels, const std::vector<Sprite2D*>& pSprites)
{
	assert(pModels.size() > 0);
	assert(pSprites.size() > 0);

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

	// モデル
	pModels_ = pModels;
	// スプライト
	pSprites_ = pSprites;

	// 読み込み完了
	isLoaded_ = true;
}

void MapData::Clear()
{
	chipNums_.clear();
	chipColls_.clear();
	pModels_.clear();
	pSprites_.clear();
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


void MapChip::Initialize(MapData* pMapData, const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	assert(pMapData);
	pMapData_ = pMapData;

	Initialize(leftTop, chipScale);
}
void MapChip::Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale)
{
	leftTop_ = leftTop;
	chipScale_ = chipScale;

	Reset();
}
void MapChip::Reset()
{
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

				chip->obj_.reset(ObjectModel::Create({ {posX,posY,0.0f},{},chipScale_ }));
				chip->obj_->pos_ += leftTop_;
				
				// 色
				chip->color_.reset(Color::Create());
				
				// 番号
				chip->number_ = nums[y][x];

				// 1番後ろに挿入
				chips_.push_back(std::move(chip));
			}
		}
	}
}

void MapChip::Update()
{
	if (pMapData_ == nullptr) { return; }
	if (pMapData_->isLoaded_ == false) { return; }

	for (size_t i = 0; i < chips_.size(); i++)
	{
		chips_[i]->obj_->UpdateMatrix();
	}
}

void MapChip::PerfectPixelCollision(MapChipCollider& collider)
{
	if (pMapData_ == nullptr) { return; }
	if (pMapData_->isLoaded_ == false) { return; }

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

	// ハズレ
	pMapData_->chipColls_[y][x] = false;
	return false;
}

void MapChip::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* pLightGroup, const UINT texIndex)
{
	if (pMapData_ == nullptr) { return; }
	if (pMapData_->isLoaded_ == false) { return; }

	for (size_t i = 0; i < chips_.size(); i++)
	{
		int idx = chips_[i]->number_ - 1;
		pMapData_->pModels_[idx]->Draw(chips_[i]->obj_.get(), vp, pLightGroup, chips_[i]->color_.get(), texIndex);
	}
}

YMath::Vector2 MapChip::Size()
{
	return Vector2(
		chipScale_.x_ * pMapData_->chipNums_[0].size(), 
		chipScale_.y_ * pMapData_->chipNums_.size()
	);
}


void MapChip2DDisplayer::Initialize(MapData* pMapData)
{
	assert(pMapData);
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
			posX = +(scale * pMapData_->pSprites_[nums[y][x]]->Size().x_) * x;
			posY = +(scale * pMapData_->pSprites_[nums[y][x]]->Size().y_) * y;

			chip->obj_.reset(ObjectSprite2D::Create({ {posX,posY,0.0f},{},{scale,scale,1.0f} }));

			// 色
			chip->color_.reset(Color::Create());

			// 1番後ろに挿入
			chips_[y].push_back(std::move(chip));
		}
	}
}

void MapChip2DDisplayer::Update()
{
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			//chips_[y][x]->color_->SetRGBA({ 1.0f,1.0f,1.0f,1.0f });
			chips_[y][x]->obj_->UpdateMatrix();
		}
	}
}

void MapChip2DDisplayer::Draw()
{
	for (size_t y = 0; y < chips_.size(); y++)
	{
		for (size_t x = 0; x < chips_[y].size(); x++)
		{
			int idx = pMapData_->chipNums_[y][x] - 1;
			pMapData_->pSprites_[idx]->Draw(chips_[y][x]->obj_.get(), chips_[y][x]->color_.get());
		}
	}
}
