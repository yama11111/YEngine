#pragma once
#include "BaseCharacter.h"
#include "IPet.h"

namespace YGame
{
	// プレイヤー
	class Player final :
		public BaseCharacter
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="pPet"> : ペットポインタ</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Player>Create(
			const Transform::Status& status, 
			IPet* pPet = nullptr);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="pPet"> : ペットポインタ</param>
		void Initialize(
			const Transform::Status& status, 
			IPet* pPet = nullptr);

		/// <summary>
		/// 衝突前更新
		/// </summary>
		void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		void UpdateAfterCollision() override;

	public:

		/// <summary>
		/// ペットに乗る
		/// </summary>
		/// <param name="pPet"> : ペットポインタ</param>
		void RideOnPet(IPet* pPet);
		
		/// <summary>
		/// ペットから降りる
		/// </summary>
		void GetOffPet();

	public:

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		InfoOnCollision GetInfoOnCollision() override;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pCamera"> : カメラポインタ</param>
		static void StaticInitialize(GameCamera* pCamera);

	public:

		Player() = default;

		~Player() = default;

	private:

		// ジャンプカウンター
		uint16_t jumpCounter_ = 0;

		// 最大ジャンプ回数
		uint16_t maxJumpCount_ = 0;

		// 鎧を着ているか
		bool isArmed_ = false;

		// ペットポインタ
		IPet* pPet_ = nullptr;

	private:

		// 静的スクロールカメラポインタ
		static GameCamera* spCamera_;

	private:

		/// <summary>
		/// 操縦更新
		/// </summary>
		void UpdateControl() override;
		
		/// <summary>
		/// ジャンプ
		/// </summary>
		/// <param name="isJumpCount"> : カウントするか</param>
		void Jump(const bool isJumpCount = true);

		/// <summary>
		/// 攻撃
		/// </summary>
		void Attack();

		/// <summary>
		/// 画面外処理
		/// </summary>
		void OffScreenProcess() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		void OnCollision(const InfoOnCollision & info) override;
		
		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		void DrawDebugTextContent() override;

	};
}
