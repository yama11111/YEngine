#pragma once
#include "MapChip.h"

namespace YGame
{
	class MapChipManager
	{
	
	public:

		/// <summary>
		/// マップデータ読み込み (csv)
		/// </summary>
		/// <param name="mapFileName"> : マップファイル名</param>
		void Load(const std::string& mapFileName);
		
		/// <summary>
		/// マップデータ読み込み (csv)
		/// </summary>
		/// <param name="mapIndex"> : マップ番号</param>
		/// <param name="mapFileName"> : マップファイル名</param>
		void Load(const uint32_t mapIndex, const std::string& mapFileName);
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="mapIndex"> : マップ番号</param>
		/// <param name="leftTop"> : 左上座標</param>
		/// <param name="chipScale"> : チップ1つの大きさ</param>
		void Initialize(
			const uint32_t mapIndex,
			const YMath::Vector3& leftTop,
			const YMath::Vector3& chipScale);
		
		/// <summary>
		/// リセット
		/// </summary>
		void Reset();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// マップチップポインタ取得
		/// </summary>
		/// <returns>マップチップポインタ</returns>
		MapChip* CurrentMapPointer() { return &map_; }
	
	public:
		
		/// <summary>
		/// インスタンスポインタ取得
		/// </summary>
		/// <returns>インスタンスポインタ</returns>
		static MapChipManager* GetInstance();

	private:

		// デフォルトコンストラクタ
		MapChipManager() = default;
		// デフォルトデストラクタ
		~MapChipManager() = default;
		// 代入コンストラクタ削除
		MapChipManager(const MapChipManager&) = delete;
		// 代入削除
		const MapChipManager& operator=(const MapChipManager&) = delete;

	private:
		
		// マップデータ
		std::vector<std::unique_ptr<MapData>> mapDatas_;
		
		// 現在のマップデータインデックス
		uint32_t currentIndex_ = 0;
		
		// マップ
		MapChip map_;
	};
}

