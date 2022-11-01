#include "InputManager.h"
#include "YAssert.h"

using Input::InputManager;

InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

void InputManager::Create(const HINSTANCE hInstance, const HWND hwnd)
{
	keys = Keys::GetInstance();
	mouse = Mouse::GetInstance();

	// DirectInput ¶¬
	DX::Result(DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr));

	keys->Create(hwnd, directInput);
	mouse->Create(hwnd, directInput);
}

void InputManager::Initialize()
{
	keys->Initialize();
	mouse->Initialize();
}

void InputManager::Update(const HWND hwnd)
{
	keys->Update();
	mouse->Update(hwnd);
}
