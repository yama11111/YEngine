#pragma once
#include <windows.h>

class YWindows
{
private:
	// ウィンドウクラス設定
	WNDCLASSEX w{};
	// ウィンドウオブジェクト
	HWND hwnd;
	// メッセージ
	MSG msg{};
public:
	//ウィンドウプロシージャ
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