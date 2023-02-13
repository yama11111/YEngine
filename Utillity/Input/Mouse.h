#pragma once
#include <dinput.h>
#include <wrl.h>
#include <memory>
#include "Vector2.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace YInput
{
	// マウス入力
	enum class MouseClick
	{
		// 左クリック
		DIM_LEFT,
		// 右クリック
		DIM_RIGHT,
		// ホイールクリック
		DIM_MIDDLE,
	};

	class Mouse
	{
	private:
		// マウス情報構造体
		struct MouseState
		{
			// 情報
			DIMOUSESTATE state_{};
			// 位置
			YMath::Vector2 pos_;
			// 初期化
			void Initialize();
		};
	public:
		// デバイス
		Microsoft::WRL::ComPtr<IDirectInputDevice8> device_ = nullptr;
		// 最新
		std::unique_ptr<MouseState> mouse_ = nullptr;
		// 1F前
		std::unique_ptr<MouseState> elderMouse_ = nullptr;
	public:
		// 生成 (最初に1回呼ぶ)
		void Create(const HWND hwnd, IDirectInput8* directInput);
		// 入力情報 初期化
		void Initialize();
		// 更新処理
		void Update(const HWND hwnd);
	public:
		// 押している
		bool IsDown(const MouseClick& button);
		// 押した瞬間
		bool IsTrigger(const MouseClick& button);
		// 押し続けている
		bool IsLongPress(const MouseClick& button);
		// 離した瞬間
		bool IsRelease(const MouseClick& button);
		// 位置
		YMath::Vector2 Pos() { return mouse_->pos_; }
	public:
		static Mouse* GetInstance();
	private:
		Mouse() = default;
		~Mouse() = default;
		Mouse(const Mouse&) = delete;
		const Mouse& operator=(const Mouse&) = delete;
	};
}

