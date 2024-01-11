#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <memory>

#pragma comment (lib, "xinput.lib")

namespace YInput
{
	// パッド入力
	enum class PadButton
	{
		// 上 (十字キー)
		XIP_UP = XINPUT_GAMEPAD_DPAD_UP,
		// 下 (十字キー)
		XIP_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		// 左 (十字キー)
		XIP_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		// 右 (十字キー)
		XIP_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,

		// メニュー ボタン (三本線)
		XIP_MENU = XINPUT_GAMEPAD_START,
		// バック ボタン (二重四角)
		XIP_BACK = XINPUT_GAMEPAD_BACK,

		// L スティック
		XIP_LSTICK = XINPUT_GAMEPAD_LEFT_THUMB,
		// R スティック
		XIP_RSTICK = XINPUT_GAMEPAD_RIGHT_THUMB,
		// LB ボタン
		XIP_LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
		// RB ボタン
		XIP_RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,

		// A ボタン
		XIP_A = XINPUT_GAMEPAD_A,
		// B ボタン
		XIP_B = XINPUT_GAMEPAD_B,
		// X ボタン
		XIP_X = XINPUT_GAMEPAD_X,
		// Y ボタン
		XIP_Y = XINPUT_GAMEPAD_Y,

		// LT ボタン
		XIP_LT = -1,
		// RT ボタン
		XIP_RT = -2,
	};
	// パッドスティック
	enum class PadStick 
	{
		LStick,
		RStick,
	};

	class Pad
	{
	private:
		// マウス情報構造体
		struct PadState
		{
		public:
			// 情報
			XINPUT_STATE state_{};
			// 振動
			XINPUT_VIBRATION vibration_{};
			// パッド番号 (0 ～ 3)
			DWORD index_ = 0;
			// 接続されているか
			bool isConnect_ = false;
		public:
			// 初期化
			void Initialize();
			// 接続 (番号)
			void Connect(const DWORD index);
		};
	private:
		// 最新
		std::unique_ptr<PadState> pad_ = nullptr;
		// 1F前
		std::unique_ptr<PadState> elderPad_ = nullptr;
		// DeadZone (LStick, RStick, Trigger)
		int dZone_[3]{};
	public:
		// 生成 (最初に1回呼ぶ)
		void Create();
		// 入力情報 初期化
		void Initialize();
		// 更新処理
		void Update();
	public:
		// 押している
		bool IsDown(const PadButton& button);
		// 押した瞬間
		bool IsTrigger(const PadButton& button);
		// 押し続けている
		bool IsLongPress(const PadButton& button);
		// 離した瞬間
		bool IsRelease(const PadButton& button);
	public:
		// 左
		bool IsLeft(const PadStick& stick, const bool isTrigger = false);
		// 右
		bool IsRight(const PadStick& stick, const bool isTrigger = false);
		// 上
		bool IsUp(const PadStick& stick, const bool isTrigger = false);
		// 下
		bool IsUnder(const PadStick& stick, const bool isTrigger = false);
		// 左(-1) 右(+1)
		int Horizontal(const PadStick& stick);
		// 上(-1) 下(+1)
		int Vertical(const PadStick& stick);
		// 移動しているか
		bool IsMove(const PadStick& stick);
	public:
		static Pad* GetInstance();
	private:
		Pad() = default;
		~Pad() = default;
		Pad(const Pad&) = delete;
		const Pad& operator=(const Pad&) = delete;
	};
}
