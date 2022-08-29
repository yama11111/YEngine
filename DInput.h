#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>
#include "Vec2.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

struct MyMouseState 
{
	DIMOUSESTATE state;
	Vec2 pos;
	MyMouseState() 
	{
		state.lX = 0;
		state.lY = 0;
		state.lZ = 0;
		for (size_t i = 0; i < 4; i++)
		{
			state.rgbButtons[i] = 0;
		}
		pos = Vec2(0, 0);
	}
};

class DInput
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;
	IDirectInputDevice8* mouse = nullptr;
public:
	static DInput* GetInstance();
	void Init(const HINSTANCE hInstance, const HWND hwnd);
	void GetKeyboardState(BYTE key[256]);
	void GetMouseState(MyMouseState& mouseState, const HWND hwnd);
private:
	DInput() = default;
	~DInput();
	DInput(const DInput&) = delete;
	const DInput& operator=(const DInput&) = delete;
	void CreateKeyboard(const HWND hwnd);
	void CreateMouse(const HWND hwnd);
};

