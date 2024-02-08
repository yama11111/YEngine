#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class CollisionDrawer final :
		public BaseDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		/// <param name="radius"> : 半径</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<CollisionDrawer> Create(const DrawerInitSet& init, const float radius);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// 名前取得
		/// </summary>
		/// <returns>名前</returns>
		static std::string Name();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="init"> : 初期化セット</param>
		void Initialize(const DrawerInitSet& init) override;

		/// <summary>
		/// 半径取得
		/// </summary>
		/// <param name="radius"> : 半径</param>
		void SetRadius(const float radius);

	public:

		CollisionDrawer() = default;

		~CollisionDrawer() = default;

	private:

	private:

		/// <summary>
		/// オブジェクト初期化
		/// </summary>
		void InitializeObjects() override;

	};
}
