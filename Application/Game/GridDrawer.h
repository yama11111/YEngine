#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class GridDrawer :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="location"> : 描画位置</param>
		virtual void Initialize(Transform* pParent, const DrawLocation location) override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		void PlayAnimation(const uint16_t index, const uint16_t frame) override;

	public:

		GridDrawer() = default;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="location"> : 描画位置</param>
		GridDrawer(const DrawLocation location);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="location"> : 描画位置</param>
		GridDrawer(Transform* pParent, const DrawLocation location);

		~GridDrawer() = default;

	};
}
