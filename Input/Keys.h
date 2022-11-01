#pragma once
#include <dinput.h>
#include <memory>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace Input
{
	class Keys
	{
	private:
		IDirectInputDevice8* keyDevice = nullptr;
		std::unique_ptr<unsigned char> keys[256];
		std::unique_ptr<unsigned char> elderKeys[256];
	public:
		void Create(const HWND hwnd, IDirectInput8* directInput);
		void Initialize();
		void Update();
	public:
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
		Keys() = default;
		~Keys() = default;
		Keys(const Keys&) = delete;
		const Keys& operator=(const Keys&) = delete;
	};
}