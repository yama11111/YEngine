#include "YWindowsApp.h"
#include "YDirectX.h"
#include "ScreenDesc.h"
#include "InputManager.h"
#include "ImGuiContoroller.h"
#include "GameScene.h"
#include "Def.h"
#include <imgui.h>

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

	// Input ������
	InputManager* input = InputManager::GetInstance();
	input->Create(window.HandleWindowInstance(), window.PointerHandleWindow());

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

	// GPUResource �ÓI������
	GPUResource::StaticInitialize(pDev);

	// �f�X�N���v�^�[�q�[�v (SRV, UAV, CBV)
	DescriptorHeap::StaticInitialize({ pDev, pCmdList });
	DescriptorHeap descHeap;
	descHeap.Initialize();

	// �萔�o�b�t�@�ÓI������
	ConstBufferCommon::StaticInitialize({ pCmdList, &descHeap });

	// �e�N�X�`���}�l�[�W���[
	TextureManager::StaticInitialize({ pDev, pCmdList, &descHeap });
	TextureManager texMan;

	// �p�C�v���C���ÓI������
	PipelineSet::StaticInitialize(pDev, pCmdList);

	// ���_
	Vertices<Sprite2DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<Sprite3DCommon::VData>	::StaticInitialize(pCmdList);
	Vertices<ModelCommon::VData>	::StaticInitialize(pCmdList);

	// �R�����N���X�ÓI������
	Sprite2DCommon	::StaticInitialize({ &texMan });
	Sprite3DCommon	::StaticInitialize({ &texMan });
	ModelCommon		::StaticInitialize({ &texMan });

#pragma endregion

#pragma region Game

	// imgui������
	ImGuiContoroller imguiCon;
	imguiCon.Initialize({ window.PointerHandleWindow(), pDev, dx.BackBufferCount(), pCmdList});

	// �I�[�f�B�I������
	AudioManager audioM;
	audioM.Initialize();

	// �Q�[���V�[��������
	GameScene::StaticInitialize(&texMan, &audioM);
	GameScene game;
	game.Load();
	game.Initialize();

#pragma endregion

	char buf[100]{};
	float f = 0.0f;

	// �Q�[�����[�v
	while (true)
	{
		// -------------------- Update -------------------- //

		input->Update(); // input�X�V

		imguiCon.Begin(); // imgui��t�J�n

		game.Update(); // �Q�[���V�[���X�V

		ImGui::Text("Hello, world %d", 123);
		if (ImGui::Button("Save")) {}
		ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

		imguiCon.End(); // imgui��t�I��

		// ------------------------------------------------ //

		// --------------------- Draw --------------------- //

		dx.PreDraw(ClearColor); // �`�揀��

		screenDesc.SetDrawCommand(); // �X�N���[���ݒ�Z�b�g

		descHeap.SetDrawCommand(); // �f�X�N���v�^�[�q�[�v�Z�b�g
		
		game.Draw(); // �Q�[���V�[���`��

		imguiCon.Draw(); // imgui�`��

		dx.PostDraw(); // �`��㏈��

		// ------------------------------------------------ //

		// ------------------- �I������ ------------------- //

		// �~�{�^���ŏI�����b�Z�[�W
		if (window.CheckMessage()) { break; }

		// ESC�L�[�ŏI��
		if (input->keys_->IsTrigger(DIK_ESCAPE)) { break; }

		// ------------------------------------------------ //
	}

	// imgui���N���[��
	imguiCon.Finalize();

	// �E�B���h�E�N���X��o�^����
	window.FinalProcess();

	return 0;
}