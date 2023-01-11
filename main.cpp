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
using namespace YGame;

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

#pragma region Pipeline

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
	RootParameterManager rpMan;

	// �f�X�N���v�^�[�q�[�v (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize({ pDev, pCmdList });
	DescriptorHeap descHeap;
	descHeap.Initialize();

	// �萔�o�b�t�@�ÓI������
	ConstBufferCommon::StaticInitialize({ pCmdList, &descHeap });
	ConstBuffer<TransformCBData>::StaticSetRootParamIndex(rpMan.PushBackCBV());
	ConstBuffer<ColorCBData>	::StaticSetRootParamIndex(rpMan.PushBackCBV());
	ConstBuffer<MaterialCBData>	::StaticSetRootParamIndex(rpMan.PushBackCBV());
	ConstBuffer<BillboardCBData>::StaticSetRootParamIndex(rpMan.PushBackCBV());

	// �e�N�X�`���}�l�[�W���[
	TextureManager::StaticInitialize({ pDev, pCmdList, &descHeap, rpMan.PushBackTexRegister() });
	TextureManager texMan;

	// �p�C�v���C���ÓI������
	PipelineSet::StaticInitialize(pDev, pCmdList);

	// ���_
	Vertices<SpriteCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<ModelCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<BillboardCommon::VData>::StaticInitialize(pCmdList);

	// �R�����N���X�ÓI������
	SpriteCommon	::StaticInitialize({ &texMan, rpMan.Get() });
	Material::StaticInitialize(&texMan);
	ModelCommon		::StaticInitialize({ rpMan.Get() });
	BillboardCommon	::StaticInitialize({ &texMan, rpMan.Get() });

#pragma endregion

#pragma region Game

	AudioManager audioM;
	audioM.Initialize();

	GameScene::StaticInitialize(&texMan, &audioM);
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

		descHeap.SetDrawCommand(); // �f�X�N���v�^�[�q�[�v�Z�b�g
		
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