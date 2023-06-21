#pragma once
#include "IDrawer.h"

namespace YGame
{
	class IGameObject
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : 初期化ステータス</param>
		/// <param name="drawer"> : 描画クラス(動的)</param>
		/// <param name="location"> : 描画位置</param>
		void Initialize(
			const Transform::Status& status,
			IDrawer* drawer = nullptr, 
			const DrawLocation location = DrawLocation::eCenter);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw();
	
	protected:

		/// <summary>
		/// 描画クラス設定
		/// </summary>
		/// <param name="drawer"> : 描画クラス(動的)</param>
		void SetDrawer(IDrawer* drawer);

		/// <summary>
		/// 描画位置設定
		/// </summary>
		/// <param name="location"> : 描画位置</param>
		void SetDrawLocation(const DrawLocation location);

	public:

		IGameObject() = default;
		
		virtual ~IGameObject() = default;
	
	protected:

		// トランスフォーム
		std::unique_ptr<Transform> transform_;

		// 描画クラス
		std::unique_ptr<IDrawer> drawer_;

		// 描画位置
		DrawLocation location_;

	};
}
