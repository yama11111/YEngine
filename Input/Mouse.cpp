#include "Mouse.h"
#include "YAssert.h"

using Input::Mouse;

Mouse* Mouse::GetInstance()
{
	static Mouse instance;
	return &instance;
}

void Mouse::MouseState::Initialize()
{
	state_.lX = state_.lY = state_.lZ = 0;

	for (size_t i = 0; i < 4; i++) { state_.rgbButtons[i] = 0; }

	pos_ = { 0,0 };
}

void Mouse::Create(const HWND hwnd, IDirectInput8* directInput)
{
	// 生成
	mouse_ = std::make_unique<MouseState>();
	elderMouse_ = std::make_unique<MouseState>();

	// マウスデバイス 生成
	DX::Result(directInput->CreateDevice(GUID_SysMouse, &device_, NULL));

	// 入力データ形式セット
	DX::Result(device_->SetDataFormat(&c_dfDIMouse));

	// 排他制御レベルセット
	DX::Result(device_->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));

	Initialize();
}

void Mouse::Initialize()
{
	mouse_->Initialize();
	elderMouse_->Initialize();
}

void Mouse::Update(const HWND hwnd)
{
	// 1フレーム前の情報を保存
	*elderMouse_ = *mouse_;

	// 最新の情報を取得
	device_->Acquire();
	device_->Poll();

	// 入力状態を取得
	device_->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_->state_);

	// 位置を取得
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hwnd, &pos);

	mouse_->pos_ = { static_cast<float>(pos.x), static_cast<float>(pos.y) };
}

bool Mouse::IsDown(const int button)
{
	return mouse_->state_.rgbButtons[button];
}
bool Mouse::IsTrigger(const int button)
{
	return	(mouse_->state_.rgbButtons[button] && 
			!elderMouse_->state_.rgbButtons[button]);
}
bool Mouse::IsLongPress(const int button)
{
	return	(mouse_->state_.rgbButtons[button] &&
			elderMouse_->state_.rgbButtons[button]);
}
bool Mouse::IsRelease(const int button)
{
	return	(!mouse_->state_.rgbButtons[button] &&
			elderMouse_->state_.rgbButtons[button]);
}