#include "YWindows.h"
#include "YDirectX.h"
#include "DInput.h"
#include "Keys.h"
#include "Object2D.h"
#include "Object3D.h"
#include "DXDrawDesc.h"

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

	TextureManager* texM = TextureManager::GetInstance();
	DXSRVHeap* srvH = DXSRVHeap::GetInstance();
	Model::StaticInit();
	Sprite::StaticInit();

	Sprite s1({ 128.0f, 128.0f });
	Model m1{};

	Object2D obj(&s1);
	Object3D obj2(&m1);
	MatViewProjection vp;

	UINT tex2 = texM->Load(L"Resources/player.png");
	UINT tex = texM->Load(L"Resources/enemy.png");

	srvH->SetRootParameter();

	DXDrawDesc drawDesc;
	drawDesc.Create();

	// �Q�[�����[�v
	while (true)
	{
		// ----- DirectX ���t���[������ ----- //

		// �L�[�{�[�h
		keys->Update();

		// -------------------- Update -------------------- //

		obj2.mW.rota.x += keys->Vertical() * 0.05f;
		obj2.mW.rota.y -= keys->Horizontal() * 0.05f;

		obj.Update();
		obj2.Update();

		// ------------------------------------------------ //

		if (dx->PreDraw() == -1) return 0; // �`�揀��

		// --------------------- Draw --------------------- //

		drawDesc.SetCommand();
		srvH->SetDescriptorHeaps();

		obj.Draw(tex);
		obj2.Draw(vp, tex2);

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