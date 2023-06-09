#pragma once
#include "Model.h"
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
		void Initialize(
			const Type type,
			const Transform::Status& status,
			const float radius,
			const bool isSlip = false);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() = 0;
	
	public:

		/// <summary>
		/// モデル設定
		/// </summary>
		/// <param name="pModel"> : モデルポインタ</param>
		void SetModel(Model* pModel);

	public:

		IGameObject() = default;
		
		virtual ~IGameObject() = default;
	
	protected:

		// トランスフォーム
		std::unique_ptr<Transform> transform_;

		// 3D用オブジェクト
		std::unique_ptr<Model::Object> obj_;

		// モデルポインタ
		Model* pModel_ = nullptr;
	};
}

