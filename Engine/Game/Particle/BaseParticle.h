#pragma once
#include "BaseDrawObject.h"
#include "Ease.h"
#include "BezierEase.h"
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
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw();

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
		/// <param name="status"> : 初期化ステータス</param>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(
			const uint32_t aliveFrame,
			const Transform::Status& status,
			const std::string& shaderTag,
			const uint16_t drawPriority);
		
		/// <summary>
		/// 生命更新
		/// </summary>
		/// <returns> : 生きているか</returns>
		void UpdateLife();

		/// <summary>
		/// オブジェクト設定
		/// </summary>
		/// <param name="obj"> : オブジェクト (動的インスタンス)</param>
		void SetObject(BaseDrawObject* obj);
	};
}
