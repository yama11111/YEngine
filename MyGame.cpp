#include "MyGame.h"
#include "Def.h"
#include "YGameSceneFactory.h"

#pragma region ���O��Ԑ錾
using YBase::MyGame;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YScene;
using namespace YGame;
#pragma endregion 

bool MyGame::Initialize()
{
	// ���N���X����������
	if (YFramework::Initialize() == false) { return false; }

	sceneMan_->SetSceneFactory(new YGameSceneFactory());
	sceneMan_->Change("DEMO");

	return true;
}

void MyGame::Finalize()
{
	// ���N���X�I������
	YFramework::Finalize();
}

void MyGame::Update()
{
	// ���N���X�X�V����
	YFramework::Update();

	// ------------------- �I������ ------------------- //
	// ------------------------------------------------ //
}

void MyGame::Draw()
{
	// �`�揀��
	dx_.PreDraw(ClearColor);

	// �X�N���[���ݒ�Z�b�g
	screenDesc_.SetDrawCommand();

	// �f�X�N���v�^�[�q�[�v�Z�b�g
	descHeap_.SetDrawCommand();

	// �V�[���`��
	sceneMan_->Draw();

	// imgui�`��
	imguiMan_.Draw();

	// �`��㏈��
	dx_.PostDraw();
}
