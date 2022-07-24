#include "YWindows.h"
#include "Def.h"
#include <string.h>

YWindows* YWindows::GetInstance()
{
	static YWindows instance;
	return &instance;
}

LRESULT YWindows::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// ���b�Z�[�W���ɃQ�[���ŗL�̏���
	switch (msg)
	{
		//�E�C���h�E�j����
	case WM_DESTROY:
		//OS�ɃA�v���I���`�B
		PostQuitMessage(0);
		return 0;
	}

	// �W���̃��b�Z�[�W����
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void YWindows::Create(const wchar_t* titleName)
{
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;	 // �E�B���h�E�v���V�[�W���ݒ�
	w.lpszClassName = L"DirectXGame";		 // �E�B���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);  // �E�B���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW); // �J�[�\���w��
	// �E�B���h�E�N���X��OS�ɓo�^
	RegisterClassEx(&w);
	// �E�B���h�E�T�C�Y {x, y, width�Cheight}
	RECT wrc = { 0, 0, (LONG)WIN_SIZE.x, (LONG)WIN_SIZE.y };
	// �����ŃT�C�X��␳
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	// ------- �E�B���h�E���� ------- //
	// �E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(
		w.lpszClassName,	  // �N���X��
		titleName,			  // �^�C�g���o�[
		WS_OVERLAPPEDWINDOW,  // �W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,		  // �\�� X ���W (OS�ɔC����)
		CW_USEDEFAULT,		  // �\�� Y ���W (OS�ɔC����)
		wrc.right - wrc.left, // �E�B���h�E����
		wrc.bottom - wrc.top, // �E�B���h�E�c��
		nullptr,			  // �e�E�B���h�E�n���h��
		nullptr,			  // ���j���[�n���h��
		w.hInstance,		  // �Ăяo���A�v���P�[�V�����n���h��
		nullptr);			  // �I�v�V����
	// �E�B���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);
	// ------------------------------ //
}

bool YWindows::CheckMessage()
{
	// ���b�Z�[�W������H
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg); // �L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg); // �v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	// �~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (msg.message == WM_QUIT) return true;

	return false;
}

void YWindows::FinalProcess()
{
	// �E�B���h�E�N���X��o�^����
	UnregisterClass(w.lpszClassName, w.hInstance);
}

HWND YWindows::HandleWindow()
{
	return hwnd;
}

HINSTANCE YWindows::HandleWindowInstance()
{
	return w.hInstance;
}
