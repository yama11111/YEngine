#pragma once
#include "GameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"

namespace YGame
{
	struct CollisionInfo;

	class BaseCharacter :
		public GameObject
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="name"> : 名前</param>
		/// <param name="status"> : ステータス</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="acceleration"> : 加速度</param>
		/// <param name="maxSpeed"> : 最大速度</param>
		/// <param name="hp"> : HP</param>
		/// <param name="attack"> : 攻撃力</param>
		/// <param name="invincibleTime"> : 無敵時間</param>
		/// <param name="drawer"> : 描画クラス</param>
		void Initialize(
			const std::string& name,
			const Transform::Status& status,
			const YMath::Vector3& direction,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
			BaseDrawer* drawer);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		virtual void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		virtual void UpdateAfterCollision() override;

	public:
	
		/// <summary>
		/// 衝突判定時処理
		/// </summary>
		/// <param name="collIndex"> : 衝突番号</param>
		void SendCollisionInfo(const size_t collIndex) override;

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		virtual CollisionInfo GetCollisionInfo() = 0;
	
	public:

		/// <summary>
		/// 生存フラグ
		/// </summary>
		/// <returns></returns>
		inline bool IsAlive() const { return status_.IsAlive(); }

		/// <summary>
		/// キャラステータス取得
		/// </summary>
		/// <returns>キャラステータス</returns>
		inline CharacterStatus Status() const { return status_; }

		/// <summary>
		/// 属性取得
		/// </summary>
		/// <returns>属性</returns>
		inline AttributeType Attribute() const { return attribute_; }

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();
	
	public:

		BaseCharacter() = default;

		virtual ~BaseCharacter() = default;

	protected:

		// 向き
		YMath::Vector3 direction_;

		// 移動方向
		YMath::Vector3 moveDirection_;

		// スピード
		YMath::Speed speed_;

		// キャラクターステータス
		CharacterStatus status_;

		// 属性
		AttributeType attribute_ = AttributeType::eNone;

	protected:

		/// <summary>
		/// 画面外処理
		/// </summary>
		virtual void OffScreenProcess();
		
		/// <summary>
		/// 衝突更新
		/// </summary>
		void UpdateCollision();
		
		/// <summary>
		/// 衝突時処理
		/// </summary>
		/// <param name="info"></param>
		virtual void OnCollision(const CollisionInfo& info);

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;
	};
}
