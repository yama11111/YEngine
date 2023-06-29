#pragma once
#include "AttributeType.h"
#include "Transform.h"
#include "DebugTextAttacher.h"
#include <cstdint>

namespace YGame
{
	// コライダー基底クラス
	class BaseCollider : 
		public DebugTextAttacher
	{

	public:

		// 形状
		enum class ShapeType
		{
			// 未設定
			eUnkown = -1,

			// 球
			eSphere,
		};
	
	public:

		/// <summary>
		/// 初期化 (親ポインタ無し)
		/// </summary>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Transform* pParent, const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const bool isSlip = false);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

	public:

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;

	public:

		/// <summary>
		/// 形状取得
		/// </summary>
		/// <returns>形状</returns>
		inline ShapeType Shape() const { return shapeType_; }
		
		/// <summary>
		/// 属性取得
		/// </summary>
		/// <returns>属性</returns>
		inline AttributeType Attribute() const { return attribute_; }

		/// <summary>
		/// マスク取得
		/// </summary>
		/// <returns>マスク</returns>
		inline AttributeType Mask() const { return mask_; }

		/// <summary>
		/// すり抜けフラグ取得
		/// </summary>
		/// <returns>すり抜けフラグ</returns>
		inline bool IsSlip() const { return isSlip_; };

	public:

		/// <summary>
		/// 親トランスフォーム設定
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		void SetParent(Transform* pParent);

		/// <summary>
		/// オフセット(ずれ)設定
		/// </summary>
		/// <param name="offset">オフセット(ずれ)</param>
		inline void SetOffset(const YMath::Vector3& offset) { offset_ = offset; }

		/// <summary>
		/// 属性設定
		/// </summary>
		/// <param name="attribute"> : 属性</param>
		inline void SetAttribute(const AttributeType attribute) { attribute_ = attribute; }

		/// <summary>
		/// マスク設定
		/// </summary>
		/// <param name="mask"> : マスク</param>
		inline void SetMask(const AttributeType mask) { mask_ = mask; }

		/// <summary>
		/// すり抜けフラグ設定
		/// </summary>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

	public:

		BaseCollider() = default;
		
		/// <summary>
		/// コンストラクタ (親ポインタ無し)
		/// </summary>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		BaseCollider(
			const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		BaseCollider(
			Transform* pParent, const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const bool isSlip = false);

		virtual ~BaseCollider() = default;
	
	protected:

		// 親トランスフォームポインタ
		Transform* pParent_ = nullptr;

		// ずれ
		YMath::Vector3 offset_;

		// 形状
		ShapeType shapeType_ = ShapeType::eUnkown;
		
		// 属性 (自分)
		AttributeType attribute_ = AttributeType::eAll;
		
		// マスク (相手)
		AttributeType mask_ = AttributeType::eAll;

		// すり抜けフラグ
		bool isSlip_ = false;
	};
}
