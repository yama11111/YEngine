#pragma once
#include "BaseDrawer.h"
#include "GameCollider.h"

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
			const std::string& name, 
			const Transform::Status& status,
			GameObject* pParent = nullptr);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		virtual void UpdateBeforeCollision();
		
		/// <summary>
		/// 衝突後更新
		/// </summary>
		virtual void UpdateAfterCollision();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	public:

		/// <summary>
		/// トランスフォームポインタ取得
		/// </summary>
		/// <returns>トランスフォームポインタ</returns>
		inline Transform* TransformPtr() const { return transform_.get(); }

		/// <summary>
		/// コライダーポインタ取得
		/// </summary>
		/// <returns>コライダーポインタ</returns>
		inline GameCollider* ColliderPtr() const { return collider_.get(); }
		
		/// <summary>
		/// 描画クラスポインタ
		/// </summary>
		/// <returns>描画クラスポインタ</returns>
		inline BaseDrawer* DrawerPtr() const { return drawer_.get(); }

		/// <summary>
		/// 補助描画クラスポインタ
		/// </summary>
		/// <param name="tag"> : タグ</param>
		/// <returns>描画クラスポインタ</returns>
		inline BaseDrawer* SubDrawerPtr(const std::string& tag) { return subDrawer_[tag].get(); }

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		virtual InfoOnCollision GetInfoOnCollision();

		/// <summary>
		/// 存在フラグ取得
		/// </summary>
		/// <returns>存在フラグ</returns>
		inline bool IsExist() const { return isExist_; }
	
	public:
		
		/// <summary>
		/// 親子関係設定
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		void SetParent(GameObject* pParent);

		/// <summary>
		/// コライダー設定
		/// </summary>
		/// <param name="collider"> : コライダーインスタンス (動的)</param>
		void SetCollider(std::unique_ptr<GameCollider>&& collider);

		/// <summary>
		/// 描画クラス設定
		/// </summary>
		/// <param name="drawer"> : 描画インスタンス (動的)</param>
		void SetDrawer(std::unique_ptr<BaseDrawer>&& drawer);

		/// <summary>
		/// その他の描画クラス設定
		/// </summary>
		/// <param name="tag"> : タグ</param>
		/// <param name="drawer"> : 描画インスタンス (動的)</param>
		void InsertSubDrawer(const std::string& tag, std::unique_ptr<BaseDrawer>&& drawer);

		/// <summary>
		/// 更新フラグ設定
		/// </summary>
		/// <param name="isUpdate"> : 更新フラグ</param>
		inline void SetIsControlUpdate(const bool isControlUpdate) { isControlUpdate_ = isControlUpdate; }
	
	public:

		GameObject() = default;
		
		virtual ~GameObject() = default;
	
	protected:

		// トランスフォーム
		std::unique_ptr<Transform> transform_;
		
		// コライダークラス
		std::unique_ptr<GameCollider> collider_;

		// 描画クラス
		std::unique_ptr<BaseDrawer> drawer_;
		
		// 補助描画クラス
		std::unordered_map<std::string, std::unique_ptr<BaseDrawer>> subDrawer_;

		// 親ポインタ
		GameObject* pParent_ = nullptr;

		// 存在フラグ
		bool isExist_ = true;

		// 操縦更新フラグ
		bool isControlUpdate_ = true;

	protected:

		/// <summary>
		/// 操縦更新
		/// </summary>
		virtual void UpdateControl();

		/// <summary>
		/// 衝突更新
		/// </summary>
		void UpdateCollision();

		/// <summary>
		/// 衝突時処理
		/// </summary>
		/// <param name="info"> : 衝突情報</param>
		virtual void OnCollision(const InfoOnCollision& info);

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;
	};
}
