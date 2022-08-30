#include "YWindows.h"
#include "YDirectX.h"
#include "DInput.h"
#include "Game.h"
#include "DXPipelineSet.h"
#include "DXDrawDesc.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows ������
	YWindows* win = YWindows::GetInstance();
	win->Create(L"LE2A_���}�i�J_���C_PIT SHOOTING");

	// DirectX ������
	YDirectX* dx = YDirectX::GetInstance();
	if (dx->Init(win->HandleWindow()) == -1) return 0;

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

	DXDrawDesc drawDesc;
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

		if (dx->PreDraw() == -1) return 0; // �`�揀��

		// --------------------- Draw --------------------- //
		drawDesc.SetCommand();

		game.Draw();

		// ------------------------------------------------ //

		if (dx->PostDraw() == -1) return 0; // �`��㏈��

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