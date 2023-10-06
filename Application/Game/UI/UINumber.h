#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "BaseConstBuffer.h"

namespace YGame
{
	class UINumber
	{

	public:

		/// <summary>
		/// 動的インスタンス生成
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="maxDigits"> : 最大桁数</param>
		/// <param name="interval"> : 間隔</param>
		/// <param name="shouldShowZero"> : ゼロを表示するか</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>動的インスタンス</returns>
		static UINumber* Create2D(
			const uint32_t num, 
			const size_t maxDigits, 
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isClearWhenTransition = true);

		/// <summary>
		/// 動的インスタンス生成
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="maxDigits"> : 最大桁数</param>
		/// <param name="interval"> : 間隔</param>
		/// <param name="shouldShowZero"> : ゼロを表示するか</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>動的インスタンス</returns>
		static UINumber* Create3D(
			const uint32_t num, 
			const size_t maxDigits, 
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="maxDigits"> : 最大桁数</param>
		/// <param name="shouldShowZero"> : ゼロを表示するか</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize2D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isClearWhenTransition = true) = 0;
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="maxDigits"> : 最大桁数</param>
		/// <param name="shouldShowZero"> : ゼロを表示するか</param>
		/// <param name="pParent"> : 親行列ポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize3D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update(const Transform::Status& status = {}) = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="priority"> : 描画優先度</param>
		virtual void Draw(const std::string& shaderTag, const uint16_t priority) = 0;

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
		/// 間隔設定
		/// </summary>
		/// <param name="interval"> : 間隔</param>
		virtual void SetInterval(const float interval) = 0;

		/// <summary>
		/// 桁ごとのオフセット設定
		/// </summary>
		/// <param name="digitIndex"> : 桁番号</param>
		/// <param name="offset"> : オフセット値</param>
		virtual void SetDigitOffset(const size_t digitIndex, const YMath::Vector3& offset) = 0;

		/// <summary>
		/// ゼロ表示設定
		/// </summary>
		/// <param name="shouldShowZero"> : ゼロを表示するか</param>
		virtual void SetShowZero(const bool shouldShowZero) = 0;

		/// <summary>
		/// アニメーション更新
		/// </summary>
		/// <param name="digitIndex"> : 桁番号</param>
		/// <param name="status"> : アニメーションステータス</param>
		virtual void SetAnimationStatus(const size_t digitIndex, const Transform::Status& status) = 0;

	public:

		UINumber() = default;

		virtual ~UINumber() = default;

	};
}
