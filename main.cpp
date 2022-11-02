#include "YWindowsApp.h"
#include "YDirectX.h"
#include "InputManager.h"
//#include "Game.h"
#include "ScreenDesc.h"
#include "Def.h"

using namespace DX;
using namespace Input;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows ������
	YWindowsApp window;
	window.Create(L"LE2A_���}�i�J_���C", WIN_SIZE);

	// DirectX ������
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WIN_SIZE)) { return 0; }

	// �X�N���[���ݒ�
	ScreenDesc::StaticInitialize(dx.CommandList());
	ScreenDesc screenDesc;
	screenDesc.Initialize({0,0}, WIN_SIZE);

	// Input ������
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

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


	//Game game;
	//game.Initialize();

	// �Q�[�����[�v
	while (true)
	{
		// ----- ���t���[������ ----- //

		input->Update(); // input�X�V

		// -------------------- Update -------------------- //

		//game.Update();

		// ------------------------------------------------ //

		dx.PreDraw(CLEAR_COLOR); // �`�揀��

		screenDesc.SetCommand(); // �X�N���[���ݒ�Z�b�g
		
		// --------------------- Draw --------------------- //

		//game.Draw();

		// ------------------------------------------------ //

		dx.PostDraw(); // �`��㏈��

		// ---------------------------------- //

		// �~�{�^���ŏI�����b�Z�[�W
		if (window.CheckMessage()) { break; }

		// ESC�L�[�ŏI��
		if (input->keys_->IsTrigger(DIK_ESCAPE)) { break; }
	}

	// �E�B���h�E�N���X��o�^����
	window.FinalProcess();

	return 0;
}