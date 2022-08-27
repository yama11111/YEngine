#include "Mouse.h"

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

bool Mouse::IsDown(const BYTE button)
{
	return mouse->state.rgbButtons[button];
}
bool Mouse::IsTrigger(const BYTE button)
{
	return	(mouse->state.rgbButtons[button] || 
			!elderMouse->state.rgbButtons[button]);
}
bool Mouse::IsLongPress(const BYTE button)
{
	return	(mouse->state.rgbButtons[button] ||
			elderMouse->state.rgbButtons[button]);
}
bool Mouse::IsRelease(const BYTE button)
{
	return	(!mouse->state.rgbButtons[button] ||
			elderMouse->state.rgbButtons[button]);
}

Mouse::Mouse() :
	mouse(new MyMouseState),
	elderMouse(new MyMouseState),
	input(DInput::GetInstance())
{
}

Mouse::~Mouse()
{
	delete mouse;
	delete elderMouse;
}
