#pragma once
#include <dinput.h>
#include <memory>
#include "Vec2.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace Input
{
	// �}�E�X����
	enum MouseInputNumber
	{
		// ���N���b�N
		DIM_LEFT,
		// �E�N���b�N
		DIM_RIGHT,
		// �z�C�[���N���b�N
		DIM_MIDDLE,
	};

	class Mouse
	{
	private:
		// �}�E�X���\����
		struct MouseState
		{
			// ���
			DIMOUSESTATE state;
			// �ʒu
			Math::Vec2 pos;
			// ������
			void Initialize();
		};
	public:
		// �f�o�C�X
		IDirectInputDevice8* mouseDevice = nullptr;
		// �ŐV
		std::unique_ptr<MouseState> mouse;
		// 1F�O
		std::unique_ptr<MouseState> elderMouse;
	public:
		// ���� (�ŏ���1��Ă�)
		void Create(const HWND hwnd, IDirectInput8* directInput);
		// ���͏�� ������
		void Initialize();
		// �X�V����
		void Update(const HWND hwnd);
	public:
		// �����Ă���
		bool IsDown(const int button);
		// �������u��
		bool IsTrigger(const int button);
		// ���������Ă���
		bool IsLongPress(const int button);
		// �������u��
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

