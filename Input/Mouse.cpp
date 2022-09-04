#include "Mouse.h"

using Input::Mouse;

Mouse* Mouse::GetInstance()
{
	static Mouse instance;
	return &instance;
}

void Mouse::Update(const HWND hwnd)
{
	*elderMouse = *mouse;
	input->GetMouseState(*mouse, hwnd);
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

Mouse::Mouse() :
	mouse(new MyMouseState),
	elderMouse(new MyMouseState),
	input(InputManager::GetInstance())
{
}

Mouse::~Mouse()
{
	delete mouse;
	delete elderMouse;
}
