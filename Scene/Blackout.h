#pragma once
#include "Lerp.h"
#include "Power.h"
#include "Timer.h"
#include "Sprite.h"

namespace Transition
{
	class Blackout
	{
	private:
		// 暗転段階
		enum class Step
		{
			Dark, // 暗
			Load, // ロード時間
			Bright, // 明
		};
	private:
		// 段階
		Step boStep_ = Step::Dark;
		// オブジェクト
		Game::Object curten_;
		// タイマー
		int count_ = 0;
		// イージング
		Math::Ease<float> blendE_;
		Math::Power blendP_;

		// 動作中
		bool isAct_ = false;
		// 切り替わりの瞬間
		bool isChangeMoment_ = false;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		// 動作開始
		void Activate();
		// 切り替わりの瞬間
		bool IsChangeMoment() { return isChangeMoment_; }
	private:
		void ChangeUpdate();
		void BlendUpdate();
	public:
		struct StaticInitStatus
		{
			Game::Sprite* curtenSprite_;
		};
	private:
		static Game::Sprite* curtenS_;
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
	};
}
