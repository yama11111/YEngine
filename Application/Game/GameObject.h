#pragma once
#include "BaseDrawer.h"
#include "BaseCollider.h"

namespace YGame
{
	class GameObject : 
		public DebugTextAttacher
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="name"> : 名前</param>
		/// <param name="status"> : 初期化ステータス</param>
		/// <param name="pParent"> : 親ポインタ</param>
		void Initialize(
			const std::string name, 
			const Transform::Status& status,
			GameObject* pParent = nullptr);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// 衝突判定
		/// </summary>
		virtual void OnCollision();

	public:

		/// <summary>
		/// コライダーポインタ取得
		/// </summary>
		/// <returns>コライダーポインタ</returns>
		BaseCollider* ColliderPtr() const { return collider_.get(); }
	
	public:
		
		/// <summary>
		/// コライダー設定
		/// </summary>
		/// <param name="collider"> : コライダークラス (動的)</param>
		void SetCollider(BaseCollider* collider);

		/// <summary>
		/// 描画クラス設定
		/// </summary>
		/// <param name="drawer"> : 描画クラス (動的)</param>
		void SetDrawer(BaseDrawer* drawer);

	public:

		GameObject() = default;
		
		virtual ~GameObject() = default;
	
	protected:

		// トランスフォーム
		std::unique_ptr<Transform> transform_;
		
		// コライダークラス
		std::unique_ptr<BaseCollider> collider_;

		// 描画クラス
		std::unique_ptr<BaseDrawer> drawer_;

		// 親ポインタ
		GameObject* pParent_ = nullptr;

	protected:

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;
	};
}
