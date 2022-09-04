#include "YWindows.h"
#include "YDirectX/YDirectX.h"
#include "DInput.h"
#include "Game.h"
#include "YDirectX/DrawDesc.h"

using namespace DX;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows ������
	YWindows* win = YWindows::GetInstance();
	win->Create(L"LE2A_���}�i�J_���C_PIT SHOOTING");

	// DirectX ������
	YDirectX* dx = YDirectX::GetInstance();
	if (!dx->Initialize(win->HandleWindow())) return 0;

	// Input ������
	DInput* input = DInput::GetInstance();
	input->Init(win->HandleWindowInstance(), win->HandleWindow());
	Keys* keys = Keys::GetInstance();
	Mouse* mouse = Mouse::GetInstance();

	Sprite::StaticInit();
	Model::StaticInit();
	Object2D::StaticInit();
	Object3D::StaticInit();

	Game game;
	game.Initialize();

	DrawDesc drawDesc;
	drawDesc.Set();

	// �Q�[�����[�v
	while (true)
	{
		// ----- DirectX ���t���[������ ----- //

		// �L�[�{�[�h
		keys->Update();
		// �}�E�X
		mouse->Update(win->HandleWindow());

		// -------------------- Update -------------------- //

		game.Update();

		// ------------------------------------------------ //

		dx->PreDraw(); // �`�揀��

		// --------------------- Draw --------------------- //
		drawDesc.SetCommand();

		game.Draw();

		// ------------------------------------------------ //

		dx->PostDraw(); // �`��㏈��

		// ---------------------------------- //

		// �~�{�^���ŏI�����b�Z�[�W
		if (win->CheckMessage()) break;

		// ESC�L�[�ŏI��
		if (keys->IsTrigger(DIK_ESCAPE)) break;
	}

	// �E�B���h�E�N���X��o�^����
	win->FinalProcess();

	return 0;
}