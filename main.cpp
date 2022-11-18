#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "RootParameterManager.h"
#include "GameScene.h"
#include "Def.h"

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Game;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows ������
	YWindowsApp window;
	window.Create(L"LE2A_���}�i�J_���C", WIN_SIZE);

	// DirectX ������
	YDirectX::SetFPS(FIX_FPS);
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WIN_SIZE)) { return 0; }

	ID3D12Device* pDev = dx.Device();
	ID3D12GraphicsCommandList* pCmdList = dx.CommandList();

	// �X�N���[���ݒ�
	ScreenDesc::StaticInitialize(pCmdList);
	ScreenDesc screenDesc;
	screenDesc.Initialize({ 0,0 }, WIN_SIZE);

	// Input ������
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

	GPUResource::StaticInitialize(pDev);

	RootParameterManager rpM;

	ConstBuffer<TransformCBData>::StaticInitialize(pCmdList);
	ConstBuffer<TransformCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<ColorCBData>::StaticInitialize(pCmdList);
	ConstBuffer<ColorCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<MaterialCBData>::StaticInitialize(pCmdList);
	ConstBuffer<MaterialCBData>::SetRootParameterIndex(rpM.PushBackCBV());

	SRVHeap::StaticInitialize(pDev, pCmdList);
	SRVHeap srvHeap;
	srvHeap.Create();
	TextureManager::StaticInitialize(pDev, pCmdList, &srvHeap);
	TextureManager texM;
	texM.SetRootParameterIndex(rpM.PushBackTR());

	PipelineSet::StaticInitialize(pDev, pCmdList);

	Vertices<SpriteVData>::StaticInitialize(pCmdList);
	Vertices<ModelVData>::StaticInitialize(pCmdList);

	Sprite::StaticInitialize(&texM, rpM.Get());
	Material::StaticInitialize(&texM);
	Model::StaticInitialize(rpM.Get());

	AudioManager audioM;
	audioM.Initialize();

	GameScene::StaticInitialize(&texM, &audioM);
	GameScene game;
	game.Initialize();

	// �Q�[�����[�v
	while (true)
	{
		// -------------------- Update -------------------- //

		input->Update(); // input�X�V

		game.Update(); // �Q�[���V�[���X�V

		// ------------------------------------------------ //

		// --------------------- Draw --------------------- //

		dx.PreDraw(CLEAR_COLOR); // �`�揀��

		screenDesc.SetDrawCommand(); // �X�N���[���ݒ�Z�b�g

		srvHeap.SetDrawCommand(); // SRV�q�[�v�Z�b�g
		
		game.Draw(); // �Q�[���V�[���`��

		dx.PostDraw(); // �`��㏈��

		// ------------------------------------------------ //

		// ------------------- �I������ ------------------- //

		// �~�{�^���ŏI�����b�Z�[�W
		if (window.CheckMessage()) { break; }

		// ESC�L�[�ŏI��
		if (input->keys_->IsTrigger(DIK_ESCAPE)) { break; }

		// ------------------------------------------------ //
	}

	// �E�B���h�E�N���X��o�^����
	window.FinalProcess();

	return 0;
}