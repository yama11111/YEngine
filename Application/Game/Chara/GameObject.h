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

		/// <summary>
		/// 衝突判定時処理
		/// </summary>
		/// <param name="collIndex"> : 衝突番号</param>
		virtual void SendCollisionInfo(const size_t collIndex);

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
		/// 衝突判定番号取得
		/// </summary>
		/// <returns>衝突判定番号</returns>
		inline size_t CollisionIndex() const { return collIndex_; }

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
		void SetCollider(GameCollider* collider);

		/// <summary>
		/// 描画クラス設定
		/// </summary>
		/// <param name="drawer"> : 描画インスタンス (動的)</param>
		void SetDrawer(BaseDrawer* drawer);

		/// <summary>
		/// 補助描画クラス設定
		/// </summary>
		/// <param name="tag"> : タグ</param>
		/// <param name="drawer"> : 描画インスタンス (動的)</param>
		void InsertSubDrawer(const std::string& tag, BaseDrawer* drawer);

		/// <summary>
		/// 衝突判定番号設定
		/// </summary>
		/// <param name="collIndex"> : 衝突番号</param>
		void SetCollisionIndex(const size_t collIndex);

		/// <summary>
		/// 更新フラグ設定
		/// </summary>
		/// <param name="isUpdate"> : 更新フラグ</param>
		void SetIsUpdate(const bool isUpdate);

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

		// 衝突判定番号
		size_t collIndex_ = 0;

		// 更新フラグ
		bool isUpdate_ = true;

		// 存在フラグ
		bool isExist_ = true;

	protected:

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;
	};
}
