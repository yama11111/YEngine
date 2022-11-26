#pragma once
#include <windows.h>
#include "Vec2.h"

class YWindowsApp
{
private:
	// ウィンドウクラス設定
	WNDCLASSEX wDesc_{};
	// ウィンドウオブジェクト
	HWND hwnd_;
	// メッセージ
	MSG msg_{};
public:
	// ウィンドウプロシージャ
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	// ウィンドウ生成
	void Create(const wchar_t* titleName = L"DirectXGame", const float width = 1280.0f, const float height = 720);
	// メッセージ確認
	bool CheckMessage();
	// 終了処理
	void FinalProcess();
public:
	// HWND getter
	HWND HandleWindow() { return hwnd_; }
	// pHWND getter
	HWND* PointerHandleWindow() { return &hwnd_; }
	// HINSTANCE getter
	HINSTANCE HandleWindowInstance() { return wDesc_.hInstance; }
};

