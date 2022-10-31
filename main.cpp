#include "YWindowsApp.h"
#include "YDirectX.h"
//#include "InputManager.h"
//#include "Game.h"
//#include "ScreenDesc.h"
#include "Def.h"

//using namespace DX;
//using namespace DX::GPUResource;
//using namespace DX::Utility;
//using namespace Input;
//using namespace Math;
//using namespace Object;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows ������
	YWindowsApp window;
	window.Create(L"LE2A_���}�i�J_���C", WIN_SIZE.x, WIN_SIZE.y);

	// DirectX ������
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WIN_SIZE.x, WIN_SIZE.y)) return 0;

	//// Input ������
	//InputManager* input = InputManager::GetInstance();
	//input->Init(win->HandleWindowInstance(), win->HandleWindow());
	//Keys* keys = Keys::GetInstance();
	//Mouse* mouse = Mouse::GetInstance();

	//PipelineState::StaticInit();
	//PipelineSet::StaticInit(dx->GetCommandList());
	//ShaderResourceView::StaticInit(dx->GetCommandList());

	//ConstBufferManager::StaticInit(dx->GetCommandList());
	//TextureManager::StaticInit();
	//Vertices::StaticInit(dx->GetCommandList());
	//Vertices2D::StaticInit(dx->GetCommandList());
	//Vertices3D::StaticInit(dx->GetCommandList());
	//Transform::StaticInit();
	//Sprite::StaticInit();
	//Model::StaticInit();

	//ScissorRect::StaticInit(dx->GetCommandList());
	//Viewport::StaticInit(dx->GetCommandList());
	//ScreenDesc screenDesc;
	//screenDesc.Set();

	//Game game;
	//game.Initialize();

	// �Q�[�����[�v
	while (true)
	{
		// ----- DirectX ���t���[������ ----- //

		//// �L�[�{�[�h
		//keys->Update();
		//// �}�E�X
		//mouse->Update(win->HandleWindow());

		// -------------------- Update -------------------- //

		//game.Update();

		// ------------------------------------------------ //

		dx.PreDraw(CLEAR_COLOR.r, CLEAR_COLOR.g ,CLEAR_COLOR.b ,CLEAR_COLOR.a); // �`�揀��

		// --------------------- Draw --------------------- //
		//screenDesc.SetCommand();

		//game.Draw();

		// ------------------------------------------------ //

		dx.PostDraw(); // �`��㏈��

		// ---------------------------------- //

		// �~�{�^���ŏI�����b�Z�[�W
		if (window.CheckMessage()) break;

		// ESC�L�[�ŏI��
		//if (keys->IsTrigger(DIK_ESCAPE)) break;
	}

	// �E�B���h�E�N���X��o�^����
	window.FinalProcess();

	return 0;
}