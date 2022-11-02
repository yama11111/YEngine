#pragma once
#define DIRECTINPUT_VERSION 0x0800 // DirectInput�̃o�[�W�����w��
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"

namespace Input
{
	class InputManager
	{
	private:
		Microsoft::WRL::ComPtr<IDirectInput8> directInput_ = nullptr;
		HWND* pHwnd = nullptr;
	public:
		Keys* keys_ = nullptr;
		Mouse* mouse_ = nullptr;
		Pad* pad_ = nullptr;
	public:
		// ���� (�ŏ���1��Ă�)
		void Create(const HINSTANCE hInstance, HWND* hwnd);
		// ���͏�� ������
		void Initialize();
		// �X�V����
		void Update();
	public:
		static InputManager* GetInstance();
	private:
		InputManager() = default;
		~InputManager() = default;
		InputManager(const InputManager&) = delete;
		const InputManager& operator=(const InputManager&) = delete;
	};
}

