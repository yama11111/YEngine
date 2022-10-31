#pragma once
#include <windows.h>

class WindowsApp
{
private:
	// ウィンドウクラス設定
	WNDCLASSEX w{};
	// ウィンドウオブジェクト
	HWND hwnd;
	// メッセージ
	MSG msg{};
public:
	// ウィンドウプロシージャ
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	// ウィンドウ生成
	void Create(const wchar_t* titleName = L"DirectXGame", 
				const int width = 1280, const int height = 720);
	// メッセージ確認
	bool CheckMessage();
	// 終了処理
	void FinalProcess();
	// HWND getter
	HWND HandleWindow();
	// HINSTANCE getter
	HINSTANCE HandleWindowInstance();
};

