#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class DInput
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;
public:
	static DInput* GetInstance();
	void Init(const HINSTANCE hInstance, const HWND hwnd);
	void GetKeyboardState(BYTE key[256]);
private:
	DInput() = default;
	~DInput();
	DInput(const DInput&) = delete;
	const DInput& operator=(const DInput&) = delete;
	void CreateKeyboard(const HWND hwnd);
};

