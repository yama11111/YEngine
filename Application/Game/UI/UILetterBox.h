#pragma once
#include "DrawObjectForSprite2D.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Ease.h"
#include "Timer.h"
#include <array>

namespace YGame
{
	class UILetterBox final
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="winSize"> : ウィンドウサイズ</param>
		/// <param name="topHeight"> : 上の高さ</param>
		/// <param name="bottomHeight"> : 下の高さ</param>
		void Initialize(const YMath::Vector2& winSize, const float topHeight, const float bottomHeight);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// おろす
		/// </summary>
		/// <param name="frame"></param>
		/// <param name="exponent"></param>
		void Drop(const uint32_t frame, const float exponent);

		/// <summary>
		/// しまう
		/// </summary>
		/// <param name="frame"></param>
		/// <param name="exponent"></param>
		void Close(const uint32_t frame, const float exponent);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="priority"> : 描画優先度</param>
		void Draw(const std::string& shaderTag, const uint16_t priority);
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();
	
	private:

		// 状態
		enum class State
		{
			None, // 何もしていない

			Drop, // おろしている

			Close,  // しまっている
		};
	
	private:

		// スプライトオブジェクト
		std::array<std::unique_ptr<DrawObjectForSprite2D>, 2> objs_;

		// 色
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// 高さイージング用タイマー
		YMath::Timer heightEasTimer_;

		// 高さイージング
		std::array<YMath::Ease<YMath::Vector3>, 2> heightEas_;

		// 現在の状態
		State state = State::None;

	private:

		// 静的スプライト
		static Sprite2D* spSpr_;

	private:

		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();
	};
}
