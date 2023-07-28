#pragma once
#include "BaseDrawObject.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// パーティクル基底クラス
	class BaseParticle
	{
	
	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// 生存フラグ取得
		/// </summary>
		/// <returns>生存フラグ</returns>
		bool IsAlive() const { return isAlive_; }

	public:

		BaseParticle() = default;
		
		virtual ~BaseParticle() = default;
	
	protected:
		
		// 生存フラグ
		bool isAlive_ = false;
		
		// 生存タイマー
		YMath::Timer aliveTimer_;

		// オブジェクト
		std::unique_ptr<BaseDrawObject> obj_;

		// シェーダータグ
		std::string shaderTag_;
		
		// 描画優先度
		uint16_t drawPriority_ = 0;
	
	protected:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="aliveFrame"> : 生存時間 (F)</param>
		/// <param name="obj"> : オブジェクト (動的インスタンス)</param>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(
			const uint32_t aliveFrame,
			BaseDrawObject* obj,
			const std::string& shaderTag,
			const uint16_t drawPriority);

		/// <summary>
		/// 生命更新
		/// </summary>
		/// <returns> : 生きているか</returns>
		void UpdateLife();
	};
}
