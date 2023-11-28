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
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>プレイヤー描画クラスポインタ (動的インスタンス)</returns>
		static std::unique_ptr<CollisionDrawer> Create(Transform* pParent, const float radius, const size_t drawPriority);

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
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(Transform* pParent, const size_t drawPriority) override;

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
