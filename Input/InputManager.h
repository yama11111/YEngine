#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>
#include "Vec2.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace Input
{
	struct MyMouseState
	{
	public:
		DIMOUSESTATE state;
		Math::Vec2 pos;
	public:
		MyMouseState();
	};

	class InputManager
	{
	private:
		IDirectInput8* directInput = nullptr;
		IDirectInputDevice8* keyboard = nullptr;
		IDirectInputDevice8* mouse = nullptr;
	public:
		static InputManager* GetInstance();
		void Init(const HINSTANCE hInstance, const HWND hwnd);
		void GetKeyboardState(BYTE key[256]);
		void GetMouseState(MyMouseState& mouseState, const HWND hwnd);
	private:
		InputManager() = default;
		~InputManager();
		InputManager(const InputManager&) = delete;
		const InputManager& operator=(const InputManager&) = delete;
		void CreateKeyboard(const HWND hwnd);
		void CreateMouse(const HWND hwnd);
	};
}

