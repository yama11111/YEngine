/**
 * @file Skydome.h
 * @brief 天球クラス
 * @author Yamanaka Rui
 * @date 2024/03/12
 */

#pragma once
#include "GameObject.h"

namespace YGame
{
	class Skydome final :
		public GameObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<Skydome> Create(const Transform::Status& status, const std::string& key);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		void Initialize(const Transform::Status& status, const std::string& key);

	public:

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
		/// プレイヤー位置設定
		/// </summary>
		/// <param name="pos"> : プレイヤー位置</param>
		static void SetPlayerPos(const YMath::Vector3& pos);

	public:

		Skydome() = default;

		~Skydome() = default;
	
	private:


	};
}


