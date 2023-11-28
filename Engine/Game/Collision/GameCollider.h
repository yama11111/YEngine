#pragma once
#include "Attribute.h"
#include "BasePrimitiveCollider.h"
#include "DebugTextAttacher.h"
#include "InfoOnCollision.h"
#include <cstdint>
#include <memory>
#include <list>
#include <queue>

namespace YGame
{
	// ゲーム用コライダークラス
	class GameCollider : 
		public DebugTextAttacher
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="attribute"> : 属性</param>
		static std::unique_ptr<GameCollider> Create(const Attribute& attribute);
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="attribute"> : 属性</param>
		void Initialize(const Attribute& attribute);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="pOther">相手ポインタ</param>
		bool CheckCollision(GameCollider* pOther);

		/// <summary>
		/// コライダー挿入
		/// </summary>
		/// <param name="collider">コライダー (動的インスタンス)</param>
		/// <param name="mask"> : マスク</param>
		void PushBackCollider(
			std::unique_ptr<YMath::BasePrimitiveCollider>&& collider, const Attribute& mask);
	
		/// <summary>
		/// 衝突情報積む
		/// </summary>
		/// <param name="info"> : 衝突情報</param>
		void PushBackCollisionInfo(InfoOnCollision&& info);

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;

	public:

		/// <summary>
		/// 優先度設定
		/// </summary>
		/// <param name="priority"> : 優先度</param>
		void SetPriority(const uint32_t priority) { priority_ = priority; }

		/// <summary>
		/// すり抜けフラグ設定
		/// </summary>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

	public:

		/// <summary>
		/// 属性取得
		/// </summary>
		/// <returns> : 属性</returns>
		Attribute GetAttribute() const { return attribute_; }

		/// <summary>
		/// 優先度取得
		/// </summary>
		/// <returns>優先度</returns>
		size_t Priority() const { return priority_; }

		/// <summary>
		/// すり抜けフラグ取得
		/// </summary>
		/// <returns>すり抜けフラグ</returns>
		bool IsSlip() const { return isSlip_; }

		/// <summary>
		/// 衝突情報キュー取得
		/// </summary>
		/// <returns>衝突情報キュー</returns>
		std::queue<InfoOnCollision> InfoOnCollisionQueue() const;

	public:

		GameCollider() = default;

		virtual ~GameCollider() = default;

	private:

		// 部位ごとのコライダー
		struct PartCollider
		{			
			// プリミティブ
			std::unique_ptr<YMath::BasePrimitiveCollider> primitive_;
			
			// マスク
			Attribute mask_;
		};

	private:

		// 部位コライダーリスト
		std::list<PartCollider> partColliders_;

		// 属性
		Attribute attribute_;

		// 優先度
		uint32_t priority_ = 0;

		// すり抜けフラグ
		bool isSlip_ = false;

		// 衝突情報キュー
		std::queue<InfoOnCollision> infoQueue_;

	private:

		/// <summary>
		/// 衝突情報クリア
		/// </summary>
		void ClearCollisionInfoQueue();
	};
}