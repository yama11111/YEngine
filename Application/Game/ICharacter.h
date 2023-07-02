#pragma once
#include "GameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"

namespace YGame
{
	class ICharacter :
		public GameObject,
		public MapChipCollider
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="name"> : 名前</param>
		/// <param name="status"> : ステータス</param>
		/// <param name="acceleration"> : 加速度</param>
		/// <param name="maxSpeed"> : 最大速度</param>
		/// <param name="hp"> : HP</param>
		/// <param name="attack"> : 攻撃力</param>
		/// <param name="invincibleTime"> : 無敵時間</param>
		/// <param name="collider"> : コライダー</param>
		/// <param name="drawer"> : 描画クラス</param>
		void Initialize(
			const std::string& name,
			const Transform::Status& status,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
			BaseCollider* collider, BaseDrawer* drawer);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override;

	public:

		// 衝突時情報構造体
		struct CollisionInfo
		{
			// 属性
			AttributeType attribute_ = AttributeType::eNone;

			// 位置
			YMath::Vector3 pos_;

			// 半径
			float radius_ = 0.0f;

			// キャラステータスポインタ
			CharacterStatus* pStatus_ = nullptr;

			// ポインタ
			ICharacter* pSelf_ = nullptr;
		};
		
		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		virtual void OnCollision(const CollisionInfo& info) = 0;

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
		/// 位置取得 (参照)
		/// </summary>
		/// <returns></returns>
		inline YMath::Vector3& PosRef() override { return transform_->pos_; }
		
		/// <summary>
		/// スピード取得 (参照)
		/// </summary>
		/// <returns></returns>
		inline YMath::Vector3& SpeedRef() override { return speed_.VelocityRef(); }

	public:

		ICharacter() = default;

		virtual ~ICharacter() = default;

	protected:

		// 移動方向
		YMath::Vector3 moveDirection_;

		// スピード
		YMath::Speed speed_;

		// キャラクターステータス
		CharacterStatus status_;

	protected:

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;
	};
}
