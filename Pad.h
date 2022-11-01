#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <memory>

#pragma comment (lib, "xinput.lib")

namespace Input
{
	// パッド入力
	enum PadInputNumber
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
	};

	class Pad
	{
	private:
		// マウス情報構造体
		struct PadState
		{
		public:
			// 情報
			XINPUT_STATE state_;
			// 振動
			XINPUT_VIBRATION vibration_;
			// パッド番号 (0 ～ 3)
			DWORD index_;
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
	public:
		// 生成 (最初に1回呼ぶ)
		void Create();
		// 入力情報 初期化
		void Initialize();
		// 更新処理
		void Update();
	public:
		// 押している
		bool IsDown(const int button);
		// 押した瞬間
		bool IsTrigger(const int button);
		// 押し続けている
		bool IsLongPress(const int button);
		// 離した瞬間
		bool IsRelease(const int button);
	public:
		// 左
		bool IsLeft();
		// 右
		bool IsRight();
		// 上
		bool IsUp();
		// 下
		bool IsUnder();
		// 左(-1) 右(+1)
		int Horizontal();
		// 上(-1) 下(+1)
		int Vertical();
		// 移動しているか
		bool IsMove();
	public:
		static Pad* GetInstance();
	private:
		Pad() = default;
		~Pad() = default;
		Pad(const Pad&) = delete;
		const Pad& operator=(const Pad&) = delete;
	};
}
