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
	class SpeedLevelDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>コインカウンタ描画クラスポインタ (動的インスタンス)</returns>
		static SpeedLevelDrawer* Create(
			YMath::Matrix4* pParent, 
			const std::string& shaderTag, 
			const size_t drawPriority);

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
		/// スピード変更アニメーション
		/// </summary>
		/// <param name="speed"> : スピードレベル</param>
		void ChangeSpeedAnimation(const uint32_t speed);

	private:

		// 現在スピード
		uint32_t currentSpeed_ = 0;

		// 過去スピード
		uint32_t elderSpeed_ = 0;

		// アニメーション用
		uint32_t coinForAnimation_ = 0;


		// 親トランスフォーム
		Transform transform_;

		// 数
		Transform numTrfm_;

		// UI
		std::unique_ptr<UINumber> uiNum_;
		std::array<std::unique_ptr<ConstBufferObject<CBColor>>, 2> uiColors_;

		// アニメーション用
		std::array<Transform::Status, 2> digitAnimeStatuses_;

		// UI
		std::unique_ptr<DrawObjectForSprite2D> uiSpeed_;


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
