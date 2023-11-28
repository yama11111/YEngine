#pragma once
#include "BaseCharacter.h"
#include "GameCamera.h"

namespace YGame
{
	class IPet :
		public BaseCharacter
	{

	public:

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
		/// 攻撃
		/// </summary>
		virtual void Attack() = 0;

		/// <summary>
		/// ジャンプ
		/// </summary>
		/// <param name="isJumpCount"> : カウントするか</param>
		virtual void Jump(const bool isJumpCount = true);

		/// <summary>
		/// 乗られる
		/// </summary>
		virtual void Rideen();
		
		/// <summary>
		/// 降りられる
		/// </summary>
		virtual void GotOff();
		
	public:

		/// <summary>
		/// 乗る位置の高さ取得
		/// </summary>
		/// <returns>乗る位置の高さ</returns>
		virtual YMath::Vector3 RidingPosHeight() = 0;
		
		/// <summary>
		/// 当たったか取得
		/// </summary>
		/// <returns>当たったか</returns>
		inline bool IsHit() { return isHit_; }

	public:

		IPet() = default;

		~IPet() = default;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pCamera"> : カメラポインタ</param>
		static void StaticInitialize(GameCamera* pCamera);


		static void StaticSetPetPointer(IPet* pPet);
		static IPet* StaticGetPetPointer();

	protected:

		// 当たった
		bool isHit_ = false;

		// 乗られているフラグ
		bool isRidden_ = false;

		// ジャンプカウンター
		uint16_t jumpCounter_ = 0;

		// 最大ジャンプ回数
		uint16_t maxJumpCount_ = 0;

		// 静的スクロールカメラポインタ
		static GameCamera* spCamera_;
	
	protected:

		/// <summary>
		/// 操縦更新
		/// </summary>
		virtual void UpdateControl() override;

		/// <summary>
		/// 衝突時処理
		/// </summary>
		/// <param name="info"></param>
		virtual void OnCollision(const InfoOnCollision& info) override;

		/// <summary>
		/// 衝突時処理
		/// </summary>
		virtual void Hit();

		/// <summary>
		/// 画面外処理
		/// </summary>
		void OffScreenProcess() override;

	};
}
