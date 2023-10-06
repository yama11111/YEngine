#include "MyGame.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ゲーム
	std::unique_ptr<YBase::YFramework> game = nullptr;

	// 生成
	game.reset(new YBase::MyGame());

	// 処理
	game->Run();
	
	// 開放
	game.reset();

	return 0;
}