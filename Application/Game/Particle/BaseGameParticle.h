/**
 * @file BaseGameParticle.h
 * @brief ゲーム用基底パーティクルクラス
 * @author Yamanaka Rui
 * @date 2024/04/11
 */

#pragma once
#include "BaseParticle.h"
#include "WorldKey.h"

namespace YGame
{
	class BaseGameParticle : 
		public BaseParticle
	{

	public:

		BaseGameParticle() = default;
		
		virtual ~BaseGameParticle() = default;
	
	protected:

		// 今どの世界にいるか
		WorldKey worldKey_{};
	
	protected:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="aliveFrame"> : 生存時間 (F)</param>
		/// <param name="status"> : 初期化ステータス</param>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(
			const WorldKey worldKey,
			const uint32_t aliveFrame,
			const Transform::Status& status,
			const std::string& shaderTag,
			const uint16_t drawPriority);

		/// <summary>
		/// 世界キー設定
		/// </summary>
		/// <param name="worldKey"> : 世界キー</param>
		virtual void SetWorldKey(const WorldKey worldKey);
	
	};
}
