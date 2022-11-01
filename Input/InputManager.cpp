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
	keys_ = Keys::GetInstance();
	mouse_ = Mouse::GetInstance();
	pad_ = Pad::GetInstance();

	// DirectInput ¶¬
	DX::Result(DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput_, nullptr));

	keys_->Create(hwnd, directInput_.Get());
	mouse_->Create(hwnd, directInput_.Get());
	pad_->Create();
}

void InputManager::Initialize()
{
	keys_->Initialize();
	mouse_->Initialize();
	pad_->Initialize();
}

void InputManager::Update(const HWND hwnd)
{
	keys_->Update();
	mouse_->Update(hwnd);
	pad_->Update();
}
