#pragma once
#include "Model.h"

namespace YGame
{
	class IGameObject
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : 初期化ステータス</param>
		void Initialize(const Transform::Status& status);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

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

		// 核
		std::unique_ptr<Transform> core_;

		// 3D用オブジェクト
		std::unique_ptr<Model::Object> obj_;

		// モデルポインタ
		Model* pModel_ = nullptr;
	};
}

