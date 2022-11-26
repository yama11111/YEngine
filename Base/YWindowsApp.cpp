#include "YWindowsApp.h"

#pragma comment(lib, "winmm.lib")

LRESULT YWindowsApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// メッセージ毎にゲーム固有の処理
	switch (msg)
	{
		//ウインドウ破棄時
	case WM_DESTROY:
		//OSにアプリ終了伝達
		PostQuitMessage(0);
		return 0;
	}

	// 標準のメッセージ処理
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void YWindowsApp::Create(const wchar_t* titleName, const float width, const float height)
{
	wDesc_.cbSize = sizeof(WNDCLASSEX);
	wDesc_.lpfnWndProc = (WNDPROC)WindowProc;	  // ウィンドウプロシージャ設定
	wDesc_.lpszClassName = L"DirectXGame";		  // ウィンドウクラス名
	wDesc_.hInstance = GetModuleHandle(nullptr);  // ウィンドウハンドル
	wDesc_.hCursor = LoadCursor(NULL, IDC_ARROW); // カーソル指定
	// ウィンドウクラスをOSに登録
	RegisterClassEx(&wDesc_);
	// ウィンドウサイズ {x, y, width，height}
	RECT wrc = { 0, 0, (LONG)width, (LONG)height };
	// 自動でサイスを補正
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	// ------- ウィンドウ生成 ------- //
	// ウィンドウオブジェクトの生成
	hwnd_ = CreateWindow(
		wDesc_.lpszClassName, // クラス名
		titleName,			  // タイトルバー
		WS_OVERLAPPEDWINDOW,  // 標準的なウィンドウスタイル
		CW_USEDEFAULT,		  // 表示 X 座標 (OSに任せる)
		CW_USEDEFAULT,		  // 表示 Y 座標 (OSに任せる)
		wrc.right - wrc.left, // ウィンドウ横幅
		wrc.bottom - wrc.top, // ウィンドウ縦幅
		nullptr,			  // 親ウィンドウハンドル
		nullptr,			  // メニューハンドル
		wDesc_.hInstance,	  // 呼び出しアプリケーションハンドル
		nullptr);			  // オプション
	// ウィンドウを表示状態にする
	ShowWindow(hwnd_, SW_SHOW);
	// ------------------------------ //
	// システムタイマーの分解能を上げる
	timeBeginPeriod(1);
}

bool YWindowsApp::CheckMessage()
{
	// メッセージがある？
	if (PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg_); // キー入力メッセージの処理
		DispatchMessage(&msg_);  // プロシージャにメッセージを送る
	}

	// ×ボタンで終了メッセージが来たらゲームループを抜ける
	if (msg_.message == WM_QUIT) return true;

	return false;
}

void YWindowsApp::FinalProcess()
{
	// ウィンドウクラスを登録解除
	UnregisterClass(wDesc_.lpszClassName, wDesc_.hInstance);
}