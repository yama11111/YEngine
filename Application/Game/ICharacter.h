#pragma once
#include "GameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"
#include "CollisionInfo.h"

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
		/// <param name="status"> : ステータス</param>
		/// <param name="acceleration"> : 加速度</param>
		/// <param name="maxSpeed"> : 最大速度</param>
		/// <param name="hp"> : HP</param>
		/// <param name="attack"> : 攻撃力</param>
		/// <param name="invincibleTime"> : 無敵時間</param>
		/// <param name="collider"> : コライダー</param>
		/// <param name="drawer"> : 描画クラス</param>
		void Initialize(
			const Transform::Status& status,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
			BaseCollider* collider, BaseDrawer* drawer);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		virtual void OnCollision(const CollisionInfo& info) = 0;
	
	public:

		/// <summary>
		/// 生存フラグ
		/// </summary>
		/// <returns></returns>
		bool IsAlive() const;

		/// <summary>
		/// キャラステータス取得
		/// </summary>
		/// <returns>キャラステータス</returns>
		CharacterStatus Status() const;

		/// <summary>
		/// 位置取得 (参照)
		/// </summary>
		/// <returns></returns>
		YMath::Vector3& PosRef() override;
		
		/// <summary>
		/// スピード取得 (参照)
		/// </summary>
		/// <returns></returns>
		YMath::Vector3& SpeedRef() override;

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
	};
}
