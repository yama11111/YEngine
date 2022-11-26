#pragma once
#include <windows.h>
#include "Vec2.h"

class YWindowsApp
{
private:
	// �E�B���h�E�N���X�ݒ�
	WNDCLASSEX wDesc_{};
	// �E�B���h�E�I�u�W�F�N�g
	HWND hwnd_;
	// ���b�Z�[�W
	MSG msg_{};
public:
	// �E�B���h�E�v���V�[�W��
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	// �E�B���h�E����
	void Create(const wchar_t* titleName = L"DirectXGame", const float width = 1280.0f, const float height = 720);
	// ���b�Z�[�W�m�F
	bool CheckMessage();
	// �I������
	void FinalProcess();
public:
	// HWND getter
	HWND HandleWindow() { return hwnd_; }
	// pHWND getter
	HWND* PointerHandleWindow() { return &hwnd_; }
	// HINSTANCE getter
	HINSTANCE HandleWindowInstance() { return wDesc_.hInstance; }
};

