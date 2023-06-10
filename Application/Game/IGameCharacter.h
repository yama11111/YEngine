#pragma once
#include "IGameObject.h"
#include "CharacterStatus.h"
#include "MapChipCollider.h"
#include "Speed.h"

namespace YGame
{
	class IGameCharacter :
		public IGameObject,
		public MapChipCollider
	{

	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override;
	
	public:

		/// <summary>
		/// 生存フラグ
		/// </summary>
		/// <returns></returns>
		bool IsAlive() const;

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
		/// <param name="drawer"> : 描画クラス</param>
		void Initialize(
			const Type type,
			const Transform::Status& status, 
			const float radius,
			const YMath::Vector3& acceleration, const YMath::Vector3& maxSpeed,
			const uint16_t maxJumpCount,
			const uint32_t hp, const uint32_t attack,
			IDrawer* drawer);

		/// <summary>
		/// ジャンプ
		/// </summary>
		void Jump();

	protected:

		// 移動方向
		YMath::Vector3 moveDirection_;

		// スピード
		YMath::Speed speed_;

		// ジャンプカウンター
		uint16_t jumpCounter_ = 0;

		// 最大ジャンプ回数
		uint16_t maxJumpCount_ = 0;

		// 着地フラグ
		bool isLanding_ = false;

		// キャラクターステータス
		CharacterStatus status_;
	};
}
