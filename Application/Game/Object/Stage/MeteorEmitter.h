/**
 * @file MeteorEmitter.h
 * @brief 隕石生成クラス
 * @author Yamanaka Rui
 * @date 2024/03/30
 */

#pragma once
#include "GameObject.h"

namespace YGame
{
	class MeteorEmitter final :
		public GameObject
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="status"> : トランスフォーム情報</param>
		/// <param name="key"> : キー</param>
		/// <returns>動的インスタンス</returns>
		static std::unique_ptr<MeteorEmitter> Create(
			const Transform::Status& status, 
			const std::string& key);

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

		MeteorEmitter() = default;

		~MeteorEmitter() = default;

	private:

		// 生成フラグ
		bool isEmit_ = false;
		
		// 生成カウント
		int32_t emitCount_ = 0;
	};
}

