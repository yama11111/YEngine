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
		std::vector<std::vector<uint16_t>> chipNums_;
	
	public:

		/// <summary>
		/// csv読み込み
		/// </summary>
		/// <param name="mapFileName"> : マップファイル名</param>
		void LoadCSV(const std::string& mapFileName);

		/// <summary>
		/// 消去
		/// </summary>
		void Clear();
	
	};

	// マップチップ
	class IMapChip
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pMapData"> : マップデータポインタ</param>
		/// <param name="leftTop"> : 左上</param>
		/// <param name="chipScale"> : チップ1つの大きさ</param>
		void Initialize(MapData* pMapData, const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		
		/// <summary>
		/// 初期化 (マップデータ)
		/// </summary>
		/// <param name="pMapData"> : マップデータポインタ</param>
		void Initialize(MapData* pMapData);

		/// <summary>
		/// 初期化 (左上 + チップサイズ)
		/// </summary>
		/// <param name="leftTop"> : 左上</param>
		/// <param name="chipScale"> : チップ1つの大きさ</param>
		void Initialize(const YMath::Vector3& leftTop, const YMath::Vector3& chipScale);
		
		/// <summary>
		/// リセット
		/// </summary>
		virtual void Reset() = 0;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;
		
		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
	
	public:

		/// <summary>
		/// 衝突時処理
		/// </summary>
		/// <param name="collider"> : コライダー</param>
		void PerfectPixelCollision(MapChipCollider& collider);
		
		/// <summary>
		/// 大きさ (矩形)
		/// </summary>
		/// <returns>大きさ (矩形)</returns>
		YMath::Vector2 Size();
	
	public:

		IMapChip() = default;
		
		virtual ~IMapChip() = default;
	
	protected:	
		
		// チップごとのアタリ判定
		virtual bool CollisionChip(const int x, const int y);
	
	private:
		
		// 仮移動後のチップごとのアタリ判定
		bool CollisionTemporaryMap(const YMath::Vector3& pos, const YMath::Vector3& scale, const YMath::Vector3& spd);
		
		// チップごとのアタリ判定
		bool CollisionMap(const float left, const float right, const float top, const float bottom);
	
	protected:
		
		// マップデータポインタ
		MapData* pMapData_ = nullptr;


		// チップ1個分の大きさ
		YMath::Vector3 chipScale_;
		
		// 左上([0][0])
		YMath::Vector3 leftTop_;
	
	};
}
