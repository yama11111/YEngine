#include "SelectScene.h"
#include "SceneManager.h"
#include "MathVector.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "BlockDrawer.h"
#include "SkydomeDrawer.h"

#include "StageManager.h"

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
	BaseDrawer::StaticInitialize(&transferVP_);
}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	selectDra_.Initialize();

	stageIndex_ = StageManager::GetInstance()->CurrentStageIndex();

	transferVP_.Initialize();
	camera_.Initialize({ +4.0f,+31.0f,-15.0f }, { -PI / 15.0f,-PI / 30.0f,-PI / 45.0f });
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
	if (spKeys_->IsTrigger(DIK_LEFT) || spKeys_->IsTrigger(DIK_A))
	{
		stageIndex_--;
	}
	if (spKeys_->IsTrigger(DIK_RIGHT) || spKeys_->IsTrigger(DIK_D))
	{
		stageIndex_++;
	}

	if (stageIndex_ <= 0) { stageIndex_ = 0; }
	if (9 <= stageIndex_) { stageIndex_ = 9; }

	selectDra_.SetStageIndex(static_cast<int32_t>(stageIndex_));
	selectDra_.Update();

	// �r���[�v���W�F�N�V�����X�V
	camera_.Update();
	transferVP_ = camera_.GetViewProjection();
	transferVP_.UpdateMatrix();

	// SPACE �ŃQ�[���J�n
	if (spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A))
	{
		SceneManager::GetInstance()->Transition("PLAY", "WAVE");

		StageManager::GetInstance()->SetStageIndex(stageIndex_);
	}

	// ESC �Ń^�C�g���ɖ߂�
	if (spKeys_->IsTrigger(DIK_ESCAPE))
	{
		SceneManager::GetInstance()->Transition("TITLE", "WAVE_REV");
	}
}
#pragma endregion


#pragma region �`��

void SelectScene::Draw()
{
	selectDra_.Draw();
}
#pragma endregion