#pragma once
#include "BaseCharacter.h"
#include "GameCamera.h"

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
		/// <param name="drawKeys"> : 描画キー</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Player>Create(
			const Transform::Status& status,
			const std::vector<std::string>& drawKeys);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		void Initialize(const Transform::Status& status);

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
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		InfoOnCollision GetInfoOnCollision() override;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pGameCamera"> : カメラポインタ</param>
		static void StaticInitialize(GameCamera* pGameCamera);

	public:

		Player() = default;

		~Player() = default;

	private:

		// ジャンプカウンター
		uint16_t jumpCounter_ = 0;

		// 最大ジャンプ回数
		uint16_t maxJumpCount_ = 0;

		// 着地フラグ
		bool isLanding_ = false;
		bool isElderLanding_ = false;

	private:

		/// <summary>
		/// 操縦更新
		/// </summary>
		void UpdateControl() override;
		
		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos() override;
		
		/// <summary>
		/// ジャンプ
		/// </summary>
		/// <param name="isJumpCount"> : カウントするか</param>
		void Jump(const bool isJumpCount = true);

		/// <summary>
		/// ヒップドロップ
		/// </summary>
		void Drop();

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
