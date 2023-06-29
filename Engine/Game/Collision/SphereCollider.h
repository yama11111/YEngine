#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

namespace YGame
{
	// 球コライダークラス
	class SphereCollider final:
		public BaseCollider,
		public Sphere
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius, 
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Transform* pParent, const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius, 
			const bool isSlip = false);

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

	public:

		SphereCollider() = default;
		
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		SphereCollider(
			const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius,
			const bool isSlip = false);
		
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親トランスフォームポインタ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		SphereCollider(
			Transform* pParent, const YMath::Vector3& offset,
			const AttributeType attribute, const AttributeType mask,
			const float radius,
			const bool isSlip = false);
		
		~SphereCollider() = default;

	};
}
