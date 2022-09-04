#include "InputManager.h"
#include "Utility/Result.h"

using Input::InputManager;
using DX::Utility::Result;

Input::MyMouseState::MyMouseState() 
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

InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

void InputManager::Init(const HINSTANCE hInstance, const HWND hwnd)
{
	// DirectInput ������
	Result::Check(DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr));
	CreateKeyboard(hwnd);
	CreateMouse(hwnd);
}

void InputManager::CreateKeyboard(const HWND hwnd)
{
	// �L�[�{�[�h�f�o�C�X ����
	Result::Check(directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL));

	// ���̓f�[�^�`���Z�b�g
	Result::Check(keyboard->SetDataFormat(&c_dfDIKeyboard));

	// �r�����䃌�x���Z�b�g
	Result::Check(keyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));
}

void InputManager::CreateMouse(const HWND hwnd)
{
	// �L�[�{�[�h�f�o�C�X ����
	Result::Check(directInput->CreateDevice(GUID_SysMouse, &mouse, NULL));

	// ���̓f�[�^�`���Z�b�g
	Result::Check(mouse->SetDataFormat(&c_dfDIMouse));

	// �r�����䃌�x���Z�b�g
	Result::Check(mouse->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));
}

void InputManager::GetKeyboardState(BYTE keys[256])
{
	if (keys == nullptr) return;
	// �L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();
	// �S�L�[�̓��͏�Ԃ��擾����
	BYTE key[256];
	keyboard->GetDeviceState(sizeof(key), key);
	for (int i = 0; i < 256; i++)
	{
		keys[i] = key[i];
		keys[i] >>= 7;
	}
}

void InputManager::GetMouseState(MyMouseState& mouseState, const HWND hwnd)
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

InputManager::~InputManager()
{
}
