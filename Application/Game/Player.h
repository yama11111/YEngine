#pragma once
#include "ICharacter.h"
#include "IPet.h"

namespace YGame
{
	// プレイヤー
	class Player final :
		public ICharacter
	{

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
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// 衝突時情報取得
		/// </summary>
		/// <returns>衝突時情報</returns>
		CollisionInfo GetCollisionInfo() override;

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
		/// 静的初期化
		/// </summary>
		/// <param name="pScrollCamera"> : スクロールカメラポインタ</param>
		static void StaticInitialize(ScrollCamera* pScrollCamera);

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
		static ScrollCamera* spScrollCamera_;

	private:
		
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
		/// デバッグテキスト本文
		/// </summary>
		void DrawDebugTextContent() override;

	};
}
