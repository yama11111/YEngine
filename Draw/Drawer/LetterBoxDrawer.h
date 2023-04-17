#pragma once
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	class LetterBoxDrawerCommon
	{
	protected:
		// 静的スプライト
		static YGame::Sprite2D* spSpr_;
	public:
		// 静的初期化
		static void StaticInitialize();
	public:
		virtual ~LetterBoxDrawerCommon() = default;
	};

	class LetterBoxDrawer : private LetterBoxDrawerCommon
	{
	private:
		// スプライトオブジェクト
		std::array<std::unique_ptr<YGame::Sprite2DObject>, 2> sprObjs_;
		// 色
		std::unique_ptr<YGame::Color> color_;

		// 高さ (上)
		float topHeight_ = 0.0f;
		// 高さ (下)
		float bottomHeight_ = 0.0f;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="topHeight"> : 上側の高さ</param>
		/// <param name="bottoomHeight"> : 下側の高さ</param>
		void Initialize(const float topHeight, const float bottomHeight);
		// リセット (中身だけ初期化)
		void Reset();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		~LetterBoxDrawer() = default;
	};
}