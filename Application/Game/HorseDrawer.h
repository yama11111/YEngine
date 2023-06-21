#pragma once
#include "IDrawer.h"

namespace YGame
{
	class HorseDrawer :
		public IDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		void Initialize(Transform* pParent) override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="location"> : 場所</param>
		void Draw(const DrawLocation location) override;

	public:

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="index"> : アニメーション番号</param>
		/// <param name="frame"> : 再生フレーム</param>
		void PlayAnimation(const uint16_t index, const uint16_t frame) override;

	public:

		HorseDrawer() = default;

		~HorseDrawer() = default;

	private:

	};
}
