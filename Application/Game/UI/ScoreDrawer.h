#pragma once
#include "DrawObjectForSprite2D.h"
#include "UINumber.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Ease.h"
#include "Timer.h"
#include "Power.h"
#include <array>
#include <memory>

namespace YGame
{
	class ScoreDrawer
	{
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>スコア描画クラスポインタ (動的インスタンス)</returns>
		static ScoreDrawer* Create(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		void Initialize(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// スコア変更アニメーション
		/// </summary>
		/// <param name="score"> : スコア</param>
		void ChangeScoreAnimation(const uint32_t score);

	private:

		// 現在スコア
		uint32_t currentScore_ = 0;
		
		// 過去スコア
		uint32_t elderScore_ = 0;
		
		// アニメーション用スコア
		uint32_t scoreForAnimation_ = 0;


		// トランスフォーム
		Transform transform_;

		// UI
		std::unique_ptr<UINumber> uiNum_;
		std::array<std::unique_ptr<ConstBufferObject<CBColor>>, 6> uiColors_;
		
		// アニメーション用
		std::array<Transform::Status, 6> digitAnimeStatuses_;

		// 描画優先度
		size_t drawPriority_ = 0;

		// シェーダータグ
		std::string shaderTag_;


		// リールタイマー
		YMath::Timer reelTim_;

	private:

		/// <summary>
		/// 桁ごとの色更新
		/// </summary>
		void UpdateDigitColor();

	};
}
