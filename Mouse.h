#pragma once
#include "DInput.h"

enum MouseInputNumber
{
	DIM_LEFT = 0,
	DIM_RIGHT = 1,
	DIM_MIDDLE = 2,
};

class Mouse
{
public:
	MyMouseState* mouse;
	MyMouseState* elderMouse;
	DInput* input;
public:
	void Update(const HWND hwnd);
	bool IsDown(const int button);
	bool IsTrigger(const int button);
	bool IsLongPress(const int button);
	bool IsRelease(const int button);
	Vec2 Pos() { return mouse->pos; }
public:
	static Mouse* GetInstance();
private:
	Mouse();
	~Mouse();
	Mouse(const Mouse&) = delete;
	const Mouse& operator=(const Mouse&) = delete;
};

