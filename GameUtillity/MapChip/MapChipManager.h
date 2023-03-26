#pragma once
#include "MapChip.h"

namespace YGame
{
	class MapChipManager
	{
	private:
		// マップデータ
		std::vector<MapData> mapDatas_;
		// 現在のマップデータインデックス
		uint32_t currentIndex_ = 0;
		// マップ
		MapChip map_;
		// マップ表示
		MapChip2DDisplayer mapDisp_;
	public:
		// ロードステータス
		struct LoadStatus
		{
			std::vector<Model*> pModels_; // モデルポインタ
			std::vector<Sprite2D*> pSprites_; // スプライトポインタ
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
		void Load(const LoadStatus& status);
		// 初期化
		void Initialize(const InitStatus& status);
		// リセット
		void Reset();
		// 更新
		void Update();
		// 描画
		void Draw();
		// 2D描画
		void Draw2D();
	public:
		// 現在マップポインタ
		MapChip* CurrentMapPointer() { return &map_; }
	};
}

