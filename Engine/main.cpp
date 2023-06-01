#include "MyGame.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �Q�[��
	std::unique_ptr<YBase::YFramework> game = nullptr;

	// ����
	game.reset(new YBase::MyGame());

	// ����
	game->Run();
	
	// �J��
	game.reset();

	return 0;
}