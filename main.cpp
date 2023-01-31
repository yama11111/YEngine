#include "MyGame.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ÉQÅ[ÉÄ
	std::unique_ptr<YBase::YFramework> game = nullptr;

	// ê∂ê¨
	game.reset(new YBase::MyGame());

	// èàóù
	game->Run();

	// äJï˙
	game.reset();

	return 0;
}