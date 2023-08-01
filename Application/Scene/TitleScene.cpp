#include "TitleScene.h"
#include "SceneExecutive.h"
#include "MathVector.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾

using YGame::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 


#pragma region �ǂݍ���
void TitleScene::Load()
{
	pLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_logo.png")} });
	
	pStartSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });
	
	pButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });

}
#pragma endregion


#pragma region ������
void TitleScene::Initialize()
{
	transferVP_.Initialize();

	// �E�B���h�E�T�C�Y �� 3�����x�N�g���ɂ��Ă���
	Vector3 win = ConvertToVector3(WinSize);

	Vector3 logoPos = (win / 2.0f) - Vector3(0.0f, 32.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos }, pLogoSpr_));
	
	Vector3 startPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	startObj_.reset(DrawObjectForSprite2D::Create({ startPos }, pStartSpr_));

	Vector3 buttonPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	buttonObj_.reset(DrawObjectForSprite2D::Create({ buttonPos }, pButtonSpr_));

}
#pragma endregion


#pragma region �I������
void TitleScene::Finalize()
{

}
#pragma endregion


#pragma region �X�V
void TitleScene::Update()
{
	logoObj_->Update();
	startObj_->Update();
	buttonObj_->Update();

	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();


	// SPACE �ŃQ�[���J�n
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 2, 10);
	}
	
	// ESC �ŃQ�[���I��
	if (spKeys_->IsTrigger(DIK_ESCAPE))
	{
		SceneManager::GetInstance()->SetEnd(true);
	}
}
#pragma endregion


#pragma region �`��
void TitleScene::Draw()
{
	logoObj_->Draw("Sprite2DDefault", 0);
	startObj_->Draw("Sprite2DDefault", 0);
	buttonObj_->Draw("Sprite2DDefault", 0);
}
#pragma endregion