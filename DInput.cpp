#include "DInput.h"
#include "YDirectX/Utility/Result.h"

using DX::Utility::Result;

DInput* DInput::GetInstance()
{
	static DInput instance;
	return &instance;
}

void DInput::Init(const HINSTANCE hInstance, const HWND hwnd)
{
	// DirectInput 初期化
	Result::Check(DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr));
	CreateKeyboard(hwnd);
	CreateMouse(hwnd);
}

void DInput::CreateKeyboard(const HWND hwnd)
{
	// キーボードデバイス 生成
	Result::Check(directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL));

	// 入力データ形式セット
	Result::Check(keyboard->SetDataFormat(&c_dfDIKeyboard));

	// 排他制御レベルセット
	Result::Check(keyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));
}

void DInput::CreateMouse(const HWND hwnd)
{
	// キーボードデバイス 生成
	Result::Check(directInput->CreateDevice(GUID_SysMouse, &mouse, NULL));

	// 入力データ形式セット
	Result::Check(mouse->SetDataFormat(&c_dfDIMouse));

	// 排他制御レベルセット
	Result::Check(mouse->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));
}

void DInput::GetKeyboardState(BYTE keys[256])
{
	if (keys == nullptr) return;
	// キーボード情報の取得開始
	keyboard->Acquire();
	// 全キーの入力状態を取得する
	BYTE key[256];
	keyboard->GetDeviceState(sizeof(key), key);
	for (int i = 0; i < 256; i++)
	{
		keys[i] = key[i];
		keys[i] >>= 7;
	}
}

void DInput::GetMouseState(MyMouseState& mouseState, const HWND hwnd)
{
	mouse->Acquire();
	mouse->Poll();
	mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState.state);
	for (int i = 0; i < 4; i++)
	{
		mouseState.state.rgbButtons[i] >>= 7;
	}

	POINT pos;

	GetCursorPos(&pos);
	ScreenToClient(hwnd, &pos);
	mouseState.pos.x = static_cast<float>(pos.x);
	mouseState.pos.y = static_cast<float>(pos.y);
}

DInput::~DInput()
{
}
