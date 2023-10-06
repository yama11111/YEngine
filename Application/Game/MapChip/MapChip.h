#pragma once
#include "IMapChip.h"
#include "BaseDrawer.h"

namespace YGame
{
	class MapChip :
		public IMapChip
	{

	public:

		/// <summary>
		/// リセット
		/// </summary>
		void Reset() override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	private:

		// チップごとのアタリ判定
		bool CollisionChip(const int x, const int y) override;

	private:

		// チップデータ
		struct ChipData
		{
			// トランスフォーム
			Transform transform_;

			// 描画クラス
			std::unique_ptr<BaseDrawer> drawer_;

			// アタリ判定ポインタ
			bool* pIsColl_ = nullptr;
		};

	private:

		// チップリスト
		std::list<std::unique_ptr<ChipData>> chips_;

	public:

		bool isClear_ = false;

	};
}
