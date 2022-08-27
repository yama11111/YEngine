#pragma once
#include "DInput.h"

class Keys
{
public:
	unsigned char* keys;
	unsigned char* elderKeys;
	DInput* input;
public:
	void Update();
	bool IsDown(const int key);
	bool IsTrigger(const int key);
	bool IsLongPress(const int key);
	bool IsRelease(const int key);
	int Horizontal();
	int Vertical();
public:
	static Keys* GetInstance();
private:
	Keys();
	~Keys();
	Keys(const Keys&) = delete;
	const Keys& operator=(const Keys&) = delete;
};