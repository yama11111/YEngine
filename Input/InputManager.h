#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"

namespace Input
{
	class InputManager
	{
	private:
		Microsoft::WRL::ComPtr<IDirectInput8> directInput_ = nullptr;
		HWND* pHwnd = nullptr;
	public:
		Keys* keys_ = nullptr;
		Mouse* mouse_ = nullptr;
		Pad* pad_ = nullptr;
	public:
		// 生成 (最初に1回呼ぶ)
		void Create(const HINSTANCE hInstance, HWND* hwnd);
		// 入力情報 初期化
		void Initialize();
		// 更新処理
		void Update();
	public:
		static InputManager* GetInstance();
	private:
		InputManager() = default;
		~InputManager() = default;
		InputManager(const InputManager&) = delete;
		const InputManager& operator=(const InputManager&) = delete;
	};
}

