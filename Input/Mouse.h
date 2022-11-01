#pragma once
#include <dinput.h>
#include <wrl.h>
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
			DIMOUSESTATE state_{};
			// �ʒu
			Math::Vec2 pos_;
			// ������
			void Initialize();
		};
	public:
		// �f�o�C�X
		Microsoft::WRL::ComPtr<IDirectInputDevice8> device_ = nullptr;
		// �ŐV
		std::unique_ptr<MouseState> mouse_ = nullptr;
		// 1F�O
		std::unique_ptr<MouseState> elderMouse_ = nullptr;
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
		// �ʒu
		Math::Vec2 Pos() { return mouse_->pos_; }
	public:
		static Mouse* GetInstance();
	private:
		Mouse() = default;
		~Mouse() = default;
		Mouse(const Mouse&) = delete;
		const Mouse& operator=(const Mouse&) = delete;
	};
}

