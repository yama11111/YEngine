#pragma once
#include <windows.h>

class WindowsApp
{
private:
	// �E�B���h�E�N���X�ݒ�
	WNDCLASSEX w{};
	// �E�B���h�E�I�u�W�F�N�g
	HWND hwnd;
	// ���b�Z�[�W
	MSG msg{};
public:
	// �E�B���h�E�v���V�[�W��
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	// �E�B���h�E����
	void Create(const wchar_t* titleName = L"DirectXGame", 
				const int width = 1280, const int height = 720);
	// ���b�Z�[�W�m�F
	bool CheckMessage();
	// �I������
	void FinalProcess();
	// HWND getter
	HWND HandleWindow();
	// HINSTANCE getter
	HINSTANCE HandleWindowInstance();
};

