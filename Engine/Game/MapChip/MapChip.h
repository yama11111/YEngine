#pragma once
#include "Sprite2D.h"
#include "MapChipCollider.h"
#include <memory>

namespace YGame
{
	// マップ情報
	struct MapData
	{
	public:
		// マップチップ番号
		std::vector<std::vector<int>> chipNums_;
		// マップチップアタリ判定
		std::vector<std::vector<bool>> chipColls_;

		// ロード済みか
		bool isLoaded_ = false;
	public:
		// csv読み込み
		void Load(const std::string fileName);
		// 消去
		void Clear();
		// コリジョンリセット
		void CollReset();
	};

	// マップチップ
	class MapChip
	{
	private:
		// チップ1つの情報
		struct Chip
		{
			std::unique_ptr<Transform> transform_; // トランスフォーム
		};
	private:
		// マップチップ
		std::vector<std::unique_ptr<Chip>> chips_;
		
		// マップデータポインタ
		MapData* pMapData_ = nullptr;
		
		// チップ1個分の大きさ
		YMath::Vector3 chipScale_;
		// 左上([0][0])
		YMath::Vector3 leftTop_;
	public:
		// 初期化 (マップデータ初期化ver)
		void Initialize(MapData* pMapData, const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		// 初期化
		void Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		// リセット
		void Reset();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		// 衝突時処理
		void PerfectPixelCollision(MapChipCollider& collider);
		// 大きさ (矩形)
		YMath::Vector2 Size();
	private:
		// 仮移動後のチップごとのアタリ判定
		bool CollisionTemporaryMap(const YMath::Vector3& pos, const YMath::Vector3 scale, const YMath::Vector3& spd);
		// チップごとのアタリ判定
		bool CollisionMap(const float left, const float right, const float top, const float bottom);
		// チップごとのアタリ判定
		bool CollisionChip(const int x, const int y);
	};

	// マップチップ2D表示用
	class MapChip2DDisplayer
	{
	private:
		// チップ1つの情報
		struct Chip
		{
			std::unique_ptr<Sprite2D::Object> obj_; // 定数バッファ
			std::unique_ptr<CBColor> color_;
		};
	private:
		// マップチップ2D
		std::vector<std::vector<std::unique_ptr<Chip>>> chips_;

		// マップデータポインタ
		MapData* pMapData_ = nullptr;
	public:
		// 初期化
		void Initialize(MapData* pMapData);
		// 更新
		void Update();
		// 描画
		void Draw();
	};
}
