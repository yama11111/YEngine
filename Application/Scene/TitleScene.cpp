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

	Vector3 logoPos = (win / 2.0f) - Vector3(0.0f, 128.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, pLogoSpr_));

	Vector3 startPos = (win / 2.0f) + Vector3(0.0f, 128.0f, 0.0f);
	startObj_.reset(DrawObjectForSprite2D::Create({ startPos, {}, {1.0f,1.0f,1.0f} }, pStartSpr_));


	Vector3 buttonPos = startPos + Vector3(0.0f, 96.0f, 0.0f);
	DrawObjectForSprite2D* newStartButton = DrawObjectForSprite2D::Create({ buttonPos, {}, {1.0f,1.0f,1.0f} }, pButtonSpr_);

	startButton_.reset(UIButton::Create(newStartButton));

	letterBox_.reset(new UILetterBox());

	letterBox_->Initialize(WinSize, 96.0f, 96.0f);
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
	
	startButton_->Update(spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A));

	letterBox_->Update();

	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();


	// SPACE �ŃQ�[���J�n
	if (spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A))
	{
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 2, 10);
	}
	
	// ESC �ŃQ�[���I��
	if (spKeys_->IsTrigger(DIK_ESCAPE) || spPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->SetEnd(true);
	}
}
#pragma endregion


#pragma region �`��
void TitleScene::Draw()
{
	logoObj_->Draw("Sprite2DDefault", 1);
	startObj_->Draw("Sprite2DDefault", 1);

	startButton_->Draw("Sprite2DDefault", 1);

	letterBox_->Draw("Sprite2DDefault", 1);
}
#pragma endregion