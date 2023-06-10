#pragma once
#include "IDrawer.h"
#include "GameObjectCollider.h"

namespace YGame
{
	class IGameObject : 
		public GameObjectCollider
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="type"> : 種類</param>
		/// <param name="status"> : 初期化ステータス</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="isSlip"> : すりぬけフラグ</param>
		/// <param name="drawer"> : 描画クラス</param>
		void Initialize(
			const Type type,
			const Transform::Status& status,
			const float radius,
			const bool isSlip = false,
			IDrawer* drawer = nullptr);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
	
	protected:

		/// <summary>
		/// 描画クラス設定
		/// </summary>
		/// <param name="drawer"> : 描画クラス</param>
		void SetDrawer(IDrawer* drawer);

	public:

		IGameObject() = default;
		
		virtual ~IGameObject() = default;
	
	protected:

		// トランスフォーム
		std::unique_ptr<Transform> transform_;

		// 描画クラス
		std::unique_ptr<IDrawer> drawer_;
	};
}
