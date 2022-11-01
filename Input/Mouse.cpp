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
	state.lX = 0;
	state.lY = 0;
	state.lZ = 0;
	for (size_t i = 0; i < 4; i++)
	{
		state.rgbButtons[i] = 0;
	}
	pos = { 0,0 };
}

void Mouse::Create(const HWND hwnd, IDirectInput8* directInput)
{
	// ����
	mouse = std::make_unique<MouseState>();
	elderMouse = std::make_unique<MouseState>();

	// �L�[�{�[�h�f�o�C�X ����
	DX::Result(directInput->CreateDevice(GUID_SysMouse, &mouseDevice, NULL));

	// ���̓f�[�^�`���Z�b�g
	DX::Result(mouseDevice->SetDataFormat(&c_dfDIMouse));

	// �r�����䃌�x���Z�b�g
	DX::Result(mouseDevice->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));

	Initialize();
}

void Mouse::Initialize()
{
	mouse->Initialize();
	elderMouse->Initialize();
}

void Mouse::Update(const HWND hwnd)
{
	// 1�t���[���O�̏���ۑ�
	*elderMouse = *mouse;

	// �ŐV�̏����擾
	mouseDevice->Acquire();
	mouseDevice->Poll();

	// ���͏�Ԃ��擾
	mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse->state);
	for (int i = 0; i < 4; i++)
	{
		//mouseState.state.rgbButtons[i] >>= 7;
	}

	// �ʒu���擾
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hwnd, &pos);

	mouse->pos = { static_cast<float>(pos.x), static_cast<float>(pos.y) };
}

bool Mouse::IsDown(const int button)
{
	return mouse->state.rgbButtons[button];
}
bool Mouse::IsTrigger(const int button)
{
	return	(mouse->state.rgbButtons[button] && 
			!elderMouse->state.rgbButtons[button]);
}
bool Mouse::IsLongPress(const int button)
{
	return	(mouse->state.rgbButtons[button] &&
			elderMouse->state.rgbButtons[button]);
}
bool Mouse::IsRelease(const int button)
{
	return	(!mouse->state.rgbButtons[button] &&
			elderMouse->state.rgbButtons[button]);
}