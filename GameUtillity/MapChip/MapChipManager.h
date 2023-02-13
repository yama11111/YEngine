#pragma once
#include "MapChip.h"

// マップポインタ
class MapChipPointer
{
private:
	// ポインタ
	MapChip* pMapChip_ = nullptr;
public:
	// マップチップとのアタリ判定
	void Collision(MapChipCollider& collider);
	// マップ設定
	void SetMapChip(MapChip* pMapChip) { pMapChip_ = pMapChip; }
};

class MapChipManager
{
private:
	// マップデータ
	std::vector<MapChip> maps_;
	// 現在のマップインデックス
	uint32_t currentIndex_ = 0;
	// 現在マップ (判定用)
	MapChipPointer current_{};
public:
	// ロードステータス
	struct LoadStatus
	{
		YGame::Model* pModel_; // モデルポインタ
		UINT tex_; // テクスチャインデックス
		YGame::Sprite2D* pSprite_; // スプライトポインタ
	};
	// 初期化ステータス
	struct InitStatus
	{
		uint32_t mapIndex_; // マップインデックス
		YMath::Vector3 leftTop_; // 左上([0][0])
		YMath::Vector3 chipSize_; // チップ1個分の大きさ
	};
public:
	// ロード
	void Load(const LoadStatus& state);
	// 初期化
	void Initialize(const InitStatus& state);
	// リセット
	void Reset();
	// 更新
	void Update();
	// 描画
	void Draw(const YGame::ViewProjection& vp);
	// 2D描画
	void Draw2D();
public:
	// 現在マップポインタ
	MapChipPointer* CurrentMapPointer() { return &current_; }
};

