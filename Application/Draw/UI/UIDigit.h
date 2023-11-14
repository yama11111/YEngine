#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "BaseConstBuffer.h"

namespace YGame
{
	class UIDigit
	{

	public:

		/// <summary>
		/// 動的インスタンス生成
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="offset"> : オフセット値</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>動的インスタンス</returns>
		static UIDigit* Create2D(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset ={},
			const bool isClearWhenTransition = true);

		/// <summary>
		/// 動的インスタンス生成
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードフラグ</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードフラグ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="offset"> : オフセット値</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>動的インスタンス</returns>
		static UIDigit* Create3D(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const YMath::Vector3& offset ={},
			const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="offset"> : オフセット値</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize2D(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードフラグ</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードフラグ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="offset"> : オフセット値</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize3D(
			const uint32_t num,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// トランスフォーム初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		virtual void InitializeTransform(const Transform::Status& status = {}) = 0;

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		virtual void Update(const Transform::Status& status = {}) = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="priority"> : 描画優先度</param>
		virtual void Draw(const std::string& shaderTag, const size_t priority) = 0;

	public:

		/// <summary>
		/// 定数バッファポインタ挿入 
		/// (同じ種類の定数バッファが来たら入れ替える)
		/// </summary>
		/// <param name="pCBuff"> : 定数バッファポインタ</param>
		virtual void InsertConstBuffer(BaseConstBuffer* pCB) = 0;

		/// <summary>
		/// 数字設定
		/// </summary>
		/// <param name="num"> : 数字</param>
		virtual void SetNumber(const uint32_t num) = 0;

		/// <summary>
		/// オフセット設定
		/// </summary>
		/// <param name="offset"> : オフセット値</param>
		virtual void SetOffset(const YMath::Vector3& offset) = 0;

		/// <summary>
		/// 親ポインタ設定
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		virtual void SetParent(YMath::Matrix4* pParent) = 0;

		/// <summary>
		/// ビュープロジェクション設定
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		virtual void SetViewProjection(ViewProjection* pVP) = 0;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();
	
	public:

		UIDigit() = default;

		virtual ~UIDigit() = default;

	};
}
