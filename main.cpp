#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "RootParameterManager.h"
#include "GameScene.h"
#include "Def.h"

using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace Game;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#pragma region Base

	// Windows ������
	YWindowsApp window;
	window.Create(WindowTitle, WinSize.x_, WinSize.y_);

	// DirectX ������
	YDirectX::SetFPS(FixFPS);
	YDirectX dx;
	if (!dx.Initialize(window.HandleWindow(), WinSize)) { return 0; }

#pragma endregion

#pragma region Utillity

	// �f�o�C�X�|�C���^
	ID3D12Device* pDev = dx.Device();
	// �R�}���h���X�g�|�C���^
	ID3D12GraphicsCommandList* pCmdList = dx.CommandList();

	// �X�N���[���ݒ�
	ScreenDesc::StaticInitialize(pCmdList);
	ScreenDesc screenDesc;
	screenDesc.Initialize({ 0,0 }, WinSize);

	// Input ������
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

	// GPUResource �ÓI������
	GPUResource::StaticInitialize(pDev);

	// ���[�g�p�����[�^
	RootParameterManager rpM;

	// �萔�o�b�t�@�ÓI������
	ConstBuffer<TransformCBData>::StaticInitialize(pCmdList);
	ConstBuffer<TransformCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<ColorCBData>::StaticInitialize(pCmdList);
	ConstBuffer<ColorCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<MaterialCBData>::StaticInitialize(pCmdList);
	ConstBuffer<MaterialCBData>::SetRootParameterIndex(rpM.PushBackCBV());
	ConstBuffer<BillboardCBData>::StaticInitialize(pCmdList);
	ConstBuffer<BillboardCBData>::SetRootParameterIndex(rpM.PushBackCBV());

	// �V�F�[�_�[���\�[�X�r���[
	SRVHeap::StaticInitialize(pDev, pCmdList);
	SRVHeap srvHeap;
	srvHeap.Create();
	// �e�N�X�`���}�l�[�W���[
	TextureManager::StaticInitialize(pDev, pCmdList, &srvHeap);
	TextureManager texM;
	texM.SetRootParameterIndex(rpM.PushBackTR());

	PipelineSet::StaticInitialize(pDev, pCmdList);

	// ���_
	Vertices<SpriteVData>::StaticInitialize(pCmdList);
	Vertices<ModelVData>::StaticInitialize(pCmdList);
	Vertices<BillboardVData>::StaticInitialize(pCmdList);

	// 
	Sprite::StaticInitialize(&texM, rpM.Get());
	Material::StaticInitialize(&texM);
	Model::StaticInitialize(rpM.Get());
	Billboard::StaticInitialize(&texM, rpM.Get());

	AudioManager audioM;
	audioM.Initialize();

	GameScene::StaticInitialize(&texM, &audioM);
	GameScene game;
	game.Load();
	game.Initialize();

#pragma endregion

	// �Q�[�����[�v
	while (true)
	{
		// -------------------- Update -------------------- //

		input->Update(); // input�X�V

		game.Update(); // �Q�[���V�[���X�V

		// ------------------------------------------------ //

		// --------------------- Draw --------------------- //

		dx.PreDraw(ClearColor); // �`�揀��

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