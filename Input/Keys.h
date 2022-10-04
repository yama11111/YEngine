#pragma once
#include "InputManager.h"

namespace Input
{
	class Keys
	{
	private:
		unsigned char* keys;
		unsigned char* elderKeys;
		InputManager* input;
	public:
		void Update();
		bool IsDown(const int key);
		bool IsTrigger(const int key);
		bool IsLongPress(const int key);
		bool IsRelease(const int key);
	public:
		int Horizontal();
		int Vertical();
		bool IsRight();
		bool IsLeft();
		bool IsUp();
		bool IsUnder();
		bool IsMove();
	public:
		static Keys* GetInstance();
	private:
		Keys();
		~Keys();
		Keys(const Keys&) = delete;
		const Keys& operator=(const Keys&) = delete;
	};
}