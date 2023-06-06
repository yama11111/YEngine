#pragma once
#include "IGameCharacter.h"
#include "IPet.h"

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
		/// <param name="pos"> : 位置</param>
		/// <param name="pPet"> : ペットポインタ</param>
		void Initialize(
			const YMath::Vector3& pos, 
			IPet* pPet = nullptr);

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		/// <summary>
		/// ペットポインタ設定
		/// </summary>
		/// <param name="pPet"> : ペットポインタ</param>
		void SetPointer(IPet* pPet);

	public:

		Player() = default;

		~Player() = default;

	private:

		// 鎧を着ているか
		bool isArmed_ = false;

		// ペットポインタ
		IPet* pPet_ = nullptr;

	};
}
