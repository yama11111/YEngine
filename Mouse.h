#pragma once
#include "DInput.h"

class Mouse
{
public:
	MyMouseState* mouse;
	MyMouseState* elderMouse;
	DInput* input;
public:
	void Update(const HWND hwnd);
	bool IsDown(const BYTE button);
	bool IsTrigger(const BYTE button);
	bool IsLongPress(const BYTE button);
	bool IsRelease(const BYTE button);
	Vec2 Pos() { return mouse->pos; }
public:
	static Mouse* GetInstance();
private:
	Mouse();
	~Mouse();
	Mouse(const Mouse&) = delete;
	const Mouse& operator=(const Mouse&) = delete;
};

