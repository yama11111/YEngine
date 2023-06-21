#pragma once
#include "IGameCharacter.h"
#include "IPet.h"
#include "ScrollCamera.h"

namespace YGame
{
	// プレイヤー
	class Player final :
		public IGameCharacter
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
		/// <param name="pPair"> : 相手のキャラクターポインタ</param>
		void OnCollision(IGameCharacter* pPair) override;

		/// <summary>
		/// ペットポインタ設定
		/// </summary>
		/// <param name="pPet"> : ペットポインタ</param>
		void SetPetPointer(IPet* pPet);

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
		void Jump();

	};
}
