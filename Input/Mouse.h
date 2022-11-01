#pragma once
#include <dinput.h>
#include <memory>
#include "Vec2.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace Input
{
	enum MouseInputNumber
	{
		DIM_LEFT = 0,
		DIM_RIGHT = 1,
		DIM_MIDDLE = 2,
	};

	class Mouse
	{
	private:
		struct MouseState
		{
			DIMOUSESTATE state;
			Math::Vec2 pos;
			void Initialize();
		};
	public:
		IDirectInputDevice8* mouseDevice = nullptr;
		std::unique_ptr<MouseState> mouse;
		std::unique_ptr<MouseState> elderMouse;
	public:
		void Create(const HWND hwnd, IDirectInput8* directInput);
		void Initialize();
		void Update(const HWND hwnd);
	public:
		bool IsDown(const int button);
		bool IsTrigger(const int button);
		bool IsLongPress(const int button);
		bool IsRelease(const int button);
		Math::Vec2 Pos() { return mouse->pos; }
	public:
		static Mouse* GetInstance();
	private:
		Mouse() = default;
		~Mouse() = default;
		Mouse(const Mouse&) = delete;
		const Mouse& operator=(const Mouse&) = delete;
	};
}

