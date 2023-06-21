#pragma once
#include "IGameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"
#include "MapChipCollider.h"
#include "BaseCollider.h"

namespace YGame
{
	class IGameCharacter :
		public IGameObject,
		public BaseCollider,
		public MapChipCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="type"> : 種類</param>
		/// <param name="status"> : ステータス</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="acceleration"> : 加速度</param>
		/// <param name="maxSpeed"> : 最大速度</param>
		/// <param name="maxJumpCount"> : </param>
		/// <param name="hp"> : HP</param>
		/// <param name="attack"> : 攻撃力</param>
		/// <param name="invincibleTime"> : 無敵時間</param>
		/// <param name="drawer"> : 描画クラス</param>
		/// <param name="location"> : 描画位置</param>
		void Initialize(
			const uint32_t attribute, const uint32_t mask,
			const Transform::Status& status, 
			const float radius,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
			IDrawer* drawer, const DrawLocation location);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="pPair"> : 相手のキャラクターポインタ</param>
		virtual void OnCollision(IGameCharacter* pPair) = 0;
	
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

		IGameCharacter() = default;

		virtual ~IGameCharacter() = default;

	protected:

		// 移動方向
		YMath::Vector3 moveDirection_;

		// スピード
		YMath::Speed speed_;

		// キャラクターステータス
		CharacterStatus status_;
	};
}
