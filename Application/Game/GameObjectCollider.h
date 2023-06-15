#pragma once
#include "CollisionPrimitive.h"

namespace YGame
{
	class GameObjectCollider :
		public Sphere
	{

	public:

		// 種類
		enum class Type
		{
			eNone,	 // 無し
			ePlayer, // プレイヤー
			eEnemy,	 // 敵
			eCoin,	 // コイン
			eItem,	 // アイテム
			eGoal,	 // ゴール
			eEnd, // リサイズ用
		};

	public:

		/// <summary>
		/// 衝突時の判定
		/// </summary>
		/// <param name="pPair"> : 衝突した相手のポインタ</param>
		virtual void OnCollision(const GameObjectCollider* pPair);

		/// <summary>
		/// すり抜けフラグ取得
		/// </summary>
		/// <returns>すり抜けフラグ</returns>
		bool IsSlip() const;
		
	protected:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="type"> : 種類</param>
		/// <param name="pPos"> : 位置ポインタ</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="isSlip"> : すりぬけフラグ</param>
		void Initialize(
			const Type type,
			YMath::Vector3* pPos,
			const float radius,
			const bool isSlip = false);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 種類設定
		/// </summary>
		/// <param name="type"> : 種類</param>
		void SetType(const Type type);

		/// <summary>
		/// 位置ポインタ設定
		/// </summary>
		/// <param name="pPos"> : 位置ポインタ</param>
		void SetPosPointer(YMath::Vector3* pPos);

		/// <summary>
		/// すり抜けフラグ設定
		/// </summary>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void SetIsSlip(const bool isSlip);

	private:

		// 種類
		Type type_ = Type::eNone;

		// 位置ポインタ
		YMath::Vector3* pPos_ = nullptr;

		// すり抜けるか
		bool isSlip_ = false;

	};
}
