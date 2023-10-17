#pragma once
#include "BaseDrawObject.h"
#include "ConstBufferObject.h"
#include "CBSprite2DTransform.h"
#include "Sprite2D.h"

namespace YGame
{
	class DrawObjectForSprite2D final:
		public BaseDrawObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		/// <param name="pSprite2D"> : スプライト2Dポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>オブジェクトポインタ (動的インスタンス)</returns>
		static DrawObjectForSprite2D* Create(
			const Transform::Status& status,
			Sprite2D* pSprite2D, 
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
		/// スプライト2Dを設定
		/// </summary>
		/// <param name="pSprite2D"> : スプライト2Dポインタ</param>
		void SetSprite2D(Sprite2D* pSprite2D);

		/// <summary>
		/// グラフィック設定
		/// </summary>
		/// <param name="pGraphic"> : グラフィックポインタ</param>
		void SetGraphic(BaseGraphic* pGraphic) override;

	public:

		~DrawObjectForSprite2D() = default;

	private:

		// モデル用トランスフォーム定数バッファ
		std::unique_ptr<ConstBufferObject<CBSprite2DTransform>> cbTransform_;

	private:

		// 宣言、代入を禁止
		DrawObjectForSprite2D() = default;

		DrawObjectForSprite2D(const DrawObjectForSprite2D&) = delete;

		const DrawObjectForSprite2D& operator=(const DrawObjectForSprite2D&) = delete;
	};
}
