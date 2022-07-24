#pragma once
#include <windows.h>

class YWindows
{
private:
	// �E�B���h�E�N���X�ݒ�
	WNDCLASSEX w{};
	// �E�B���h�E�I�u�W�F�N�g
	HWND hwnd;
	// ���b�Z�[�W
	MSG msg{};
public:
	//�E�B���h�E�v���V�[�W��
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Create(const wchar_t* titleName = L"DirectXGame");
	bool CheckMessage();
	void FinalProcess();
	HWND HandleWindow();
	HINSTANCE HandleWindowInstance();
public:
	static YWindows* GetInstance();
private:
	YWindows() = default;
	~YWindows() = default;
	YWindows(const YWindows&) = delete;
	const YWindows& operator=(const YWindows&) = delete;
};