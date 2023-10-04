#include "TitleScene.h"
#include "SceneManager.h"
#include "MathVector.h"
#include "BlockDrawer.h"
#include "SkydomeDrawer.h"
#include "CharacterConfig.h"
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
	BaseDrawer::StaticInitialize(&transferVP_);

	TitleDrawer::LoadResource();
}
#pragma endregion


#pragma region ������
void TitleScene::Initialize()
{
	titleDra_.Initialize();
	titleDra_.OpeningAnimation();
	
	transferVP_.Initialize({ {-2.0f, -0.75f, -10.0f}, {+4.0f,+2.0f,+1.0f}, {0.1f,1.0f,-0.1f} });
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
	if (spKeys_->IsTrigger(DIK_O) || spPad_->IsTrigger(PadButton::XIP_Y))
	{
		titleDra_.OpeningAnimation();
	}
	titleDra_.Update();

	transferVP_.UpdateMatrix();

	// �Q�[���J�n
	if (spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A) && 
		SceneManager::GetInstance()->IsTransition() == false)
	{
		SceneManager::GetInstance()->Transition("SELECT", "WAVE");

		titleDra_.StartAnimation();
	}
	
	// �Q�[���I��
	if (spKeys_->IsTrigger(DIK_ESCAPE) || spPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->SetEnd(true);
	}
}
#pragma endregion


#pragma region �`��
void TitleScene::Draw()
{
	titleDra_.Draw();
}
#pragma endregion