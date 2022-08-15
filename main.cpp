#include "YWindows.h"
#include "YDirectX.h"
#include "DInput.h"
#include "Keys.h"
#include "VertexIndex.h"
#include "ConstBufferManager.h"
#include "TextureManager.h"
#include "DXDrawDesc.h"

#include "MatWorld.h"
#include "MatView.h"
#include "MatProjection.h"
#include "Calc.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Windows ������
	YWindows* win = YWindows::GetInstance();
	win->Create(L"LE2A_���}�i�J_���C_AL3");

	// DirectX ������
	YDirectX* dx = YDirectX::GetInstance();
	if (dx->Init(win->HandleWindow()) == -1) return 0;

	// Input ������
	DInput* input = DInput::GetInstance();
	input->Init(win->HandleWindowInstance(), win->HandleWindow());
	Keys* keys = Keys::GetInstance();

	Vertices vert(
		{
			{{ -0.5f, -0.5f, 0.0f }}, // ����
			{{ -0.5f,  0.5f, 0.0f }}, // ����
			{{  0.5f, -0.5f, 0.0f }}, // �E��
		}
	);
	vert.Init();

	VertexIndex vtIdx(
		{
			// �O
			{{ -5.0f, -5.0f, -5.0f }}, // ����
			{{ -5.0f,  5.0f, -5.0f }}, // ����
			{{  5.0f, -5.0f, -5.0f }}, // �E��
			{{  5.0f,  5.0f, -5.0f }}, // �E��

			// ��
			{{ -5.0f, -5.0f,  5.0f }}, // ����
			{{ -5.0f,  5.0f,  5.0f }}, // ����
			{{  5.0f, -5.0f,  5.0f }}, // �E��
			{{  5.0f,  5.0f,  5.0f }}, // �E��

			// ��
			{{ -5.0f, -5.0f, -5.0f }}, // ����
			{{ -5.0f, -5.0f,  5.0f }}, // ����
			{{ -5.0f,  5.0f, -5.0f }}, // �E��
			{{ -5.0f,  5.0f,  5.0f }}, // �E��

			// �E
			{{  5.0f, -5.0f, -5.0f }}, // ����
			{{  5.0f, -5.0f,  5.0f }}, // ����
			{{  5.0f,  5.0f, -5.0f }}, // �E��
			{{  5.0f,  5.0f,  5.0f }}, // �E��

			// ��
			{{ -5.0f, -5.0f,  5.0f }}, // ����
			{{ -5.0f, -5.0f, -5.0f }}, // ����
			{{  5.0f, -5.0f,  5.0f }}, // �E��
			{{  5.0f, -5.0f, -5.0f }}, // �E��

			// ��
			{{ -5.0f,  5.0f,  5.0f }}, // ����
			{{ -5.0f,  5.0f, -5.0f }}, // ����
			{{  5.0f,  5.0f,  5.0f }}, // �E��
			{{  5.0f,  5.0f, -5.0f }}, // �E��
		},
		{
			// �O
			0, 1, 2, // �O�p�`1��
			2, 1, 3, // �O�p�`2��

			// ��
			6, 7, 4, // �O�p�`1��
			4, 7, 5, // �O�p�`2��

			// ��
			8, 9, 10, // �O�p�`1��
			10, 9, 11, // �O�p�`2��

			// �E
			14, 15, 12, // �O�p�`1��
			12, 15, 13, // �O�p�`2��

			// ��
			16, 17, 18, // �O�p�`1��
			18, 17, 19, // �O�p�`2��

			//// ��
			22, 23, 20, // �O�p�`1��
			20, 23, 21, // �O�p�`2��
		}
	);
	vtIdx.Init();

	VertexIndex vtIdx2(
		//{
		//	// �O
		//	{{   0.0f, 100.0f, 0.0f }, { 0.0f, 1.0f }}, // ����
		//	{{   0.0f,   0.0f, 0.0f }, { 0.0f, 0.0f }}, // ����
		//	{{ 100.0f, 100.0f, 0.0f }, { 1.0f, 1.0f }}, // �E��
		//	{{ 100.0f,   0.0f, 0.0f }, { 1.0f, 0.0f }}, // �E��
		//},
		{
			// �O
			{{ -50.0f, -50.0f, 0.0f }, { 0.0f, 1.0f }}, // ����
			{{ -50.0f,  50.0f, 0.0f }, { 0.0f, 0.0f }}, // ����
			{{  50.0f, -50.0f, 0.0f }, { 1.0f, 1.0f }}, // �E��
			{{  50.0f,  50.0f, 0.0f }, { 1.0f, 0.0f }}, // �E��
		},
		{
			// �O
			0, 1, 2, // �O�p�`1��
			2, 1, 3, // �O�p�`2��
		}
	);
	vtIdx2.Init();

	ConstBufferManager* cbM = ConstBufferManager::GetInstance();
	TextureManager* texM = TextureManager::GetInstance();
	DXSRVHeap* srvH = DXSRVHeap::GetInstance();

	ConstBufferMaterial cb;
	cbM->CreateCB(cb);
	ConstBufferTransform cb2;
	cbM->CreateCB(cb2);

	MatWorld mW;
	MatView mV;
	MatProjection mP(MatProjection::Perspective);

	cb2.cMapTrfm->mat = mW.m * mV.m * mP.m;

	UINT tex = texM->Create();
	UINT tex2 = texM->Load(L"Resources/player.png");

	texM->SetRootParameter();

	DXDrawDesc drawDesc;
	drawDesc.Create();

	// �Q�[�����[�v
	while (true)
	{
		// ----- DirectX ���t���[������ ----- //

		// �L�[�{�[�h
		keys->Update();

		// -------------------- Update -------------------- //



		// ------------------------------------------------ //

		if (dx->PreDraw() == -1) return 0; // �`�揀��

		// --------------------- Draw --------------------- //

		drawDesc.SetCommand();
		srvH->SetCommand();

		vtIdx2.SetCommand();
		cbM->SetCommand(cb);
		cbM->SetCommand(cb2);
		texM->SetCommand(tex);
		texM->SetCommand(tex2);
		vtIdx2.Draw();

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