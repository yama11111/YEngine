#pragma once
#include "BaseDrawObject.h"
#include "ViewProjection.h"
#include "ConstBufferObject.h"
#include "CBSprite3DTransform.h"
#include "Sprite3D.h"

namespace YGame
{
	class DrawObjectForSprite3D :
		public BaseDrawObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォームステータス</param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードフラグ</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードフラグ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pSprite3D"> : スプライト3Dポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>オブジェクトポインタ (動的インスタンス)</returns>
		static DrawObjectForSprite3D* Create(
			const Transform::Status& status,
			const bool isXAxisBillboard, const bool isYAxisBillboard, 
			ViewProjection* pVP,
			Sprite3D* pSprite3D, 
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
		/// ビルボード設定
		/// </summary>
		/// <param name="isXAxisBillbord"> : X軸ビルボードフラグ</param>
		/// <param name="isYAxisBillbord"> : Y軸ビルボードフラグ</param>
		void SetBillboardFrag(const bool isXAxisBillbord, const bool isYAxisBillbord);

		/// <summary>
		/// ビュープロジェクションを設定
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// スプライト3Dを設定
		/// </summary>
		/// <param name="pSprite3D"> : スプライト3Dポインタ</param>
		void SetSprite3D(Sprite3D* pSprite3D);

	public:

		~DrawObjectForSprite3D() = default;

	private:

		// X軸ビルボードフラグ
		bool isXAxisBillboard_ = false;
		
		// Y軸ビルボードフラグ
		bool isYAxisBillboard_ = false;

		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;

		// スプライト3D用トランスフォーム定数バッファ
		std::unique_ptr<ConstBufferObject<CBSprite3DTransform>> cbTransform_;

	private:

		// 宣言、代入を禁止
		DrawObjectForSprite3D() = default;

		DrawObjectForSprite3D(const DrawObjectForSprite3D&) = delete;

		const DrawObjectForSprite3D& operator=(const DrawObjectForSprite3D&) = delete;

	};
}
