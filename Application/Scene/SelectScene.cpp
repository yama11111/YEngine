#include "SelectScene.h"
#include "SceneExecutive.h"
#include "MathVector.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾

using YGame::SelectScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 


#pragma region �ǂݍ���
void SelectScene::Load()
{
	pLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_logo.png")} });

	pStartSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });
	
	pNumberSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });
	
	pStickSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });

	pButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });

}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	// �E�B���h�E�T�C�Y �� 3�����x�N�g���ɂ��Ă���
	Vector3 win = ConvertToVector3(WinSize);


	Vector3 logoPos = (win / 2.0f) - Vector3(0.0f, 32.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos }, pLogoSpr_));

	Vector3 startPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	startObj_.reset(DrawObjectForSprite2D::Create({ startPos }, pStartSpr_));
		
	Vector3 numberPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	numberObj_.reset(DrawObjectForSprite2D::Create({ numberPos }, pNumberSpr_));

	Vector3 stickPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	stickObj_.reset(DrawObjectForSprite2D::Create({ stickPos }, pStickSpr_));
	
	Vector3 buttonPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	buttonObj_.reset(DrawObjectForSprite2D::Create({ buttonPos }, pButtonSpr_));
	
	transferVP_.Initialize();
}
#pragma endregion


#pragma region �I������
void SelectScene::Finalize()
{
}
#pragma endregion


#pragma region �X�V
void SelectScene::Update()
{
	logoObj_->Update();
	startObj_->Update();
	numberObj_->Update();
	stickObj_->Update();
	buttonObj_->Update();

	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();


	// SPACE �ŃQ�[���J�n
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 2, 10);
	}

	// ESC �Ń^�C�g���ɖ߂�
	if (spKeys_->IsTrigger(DIK_ESCAPE))
	{
		SceneExecutive::GetInstance()->Change("TITLE", "BLACKOUT", 20, 10);
	}
}
#pragma endregion


#pragma region �`��

void SelectScene::Draw()
{
	logoObj_->Draw("Sprite2DDefault", 0);
	startObj_->Draw("Sprite2DDefault", 0);
	numberObj_->Draw("Sprite2DDefault", 0);
	stickObj_->Draw("Sprite2DDefault", 0);
	buttonObj_->Draw("Sprite2DDefault", 0);
}
#pragma endregion