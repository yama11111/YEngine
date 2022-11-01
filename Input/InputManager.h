#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include "Keys.h"
#include "Mouse.h"

namespace Input
{
	class InputManager
	{
	private:
		IDirectInput8* directInput = nullptr;
	public:
		Keys* keys = nullptr;
		Mouse* mouse = nullptr;
	public:
		void Create(const HINSTANCE hInstance, const HWND hwnd);
		void Initialize();
		void Update(const HWND hwnd);
	public:
		static InputManager* GetInstance();
	private:
		InputManager() = default;
		~InputManager() = default;
		InputManager(const InputManager&) = delete;
		const InputManager& operator=(const InputManager&) = delete;
	};
}

