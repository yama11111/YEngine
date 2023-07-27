#pragma once
#include "BaseDrawObject.h"
#include "ViewProjection.h"
#include "ConstBufferObject.h"
#include "CBModelTransform.h"
#include "Model.h"

namespace YGame
{
	class DrawObjectForModel final:
		public BaseDrawObject
	{
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pModel"> : モデルポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>オブジェクトポインタ (動的インスタンス)</returns>
		static DrawObjectForModel* Create(
			const Transform::Status& status, 
			ViewProjection* pVP, 
			Model* pModel,
			const bool isClearWhenTransition = true);
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		void Initialize(
			const Transform::Status& status = Transform::Status::Default(),
			const bool isClearWhenTransition = true) override;

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		void Update(const Transform::Status& status = {}) override;

	public:

		/// <summary>
		/// ビュープロジェクションを設定
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// モデルを設定
		/// </summary>
		/// <param name="pModel"> : モデルポインタ</param>
		void SetModel(Model* pModel);
	
	public:

		~DrawObjectForModel() = default;

	private:

		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;

		// モデル用トランスフォーム定数バッファ
		std::unique_ptr<ConstBufferObject<CBModelTransform>> cbTransform_;

	private:

		// 宣言、代入を禁止
		DrawObjectForModel() = default;

		DrawObjectForModel(const DrawObjectForModel&) = delete;

		const DrawObjectForModel& operator=(const DrawObjectForModel&) = delete;
	};
}
