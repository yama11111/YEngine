#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Horse.h"
#include "Slime.h"

#include "StageManager.h"

#pragma region ���O��Ԑ錾

using YGame::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 


#pragma region �ǂݍ���
void PlayScene::Load()
{
	pCharacterMan_ = CharacterManager::GetInstance();
	
	pMapChipManager_ = MapChipManager::GetInstance();

	// �`��N���X
	BaseDrawer::StaticInitialize(&transferVP_);
	
	// �v���C���[
	Player::StaticInitialize(&scrollCamera_);
	
	// �y�b�g
	IPet::StaticInitialize(&scrollCamera_);
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	StageManager::GetInstance()->Reset();

	pLevel_ = Level::LoadJson("levelData.json");

	// �}�b�v�`�b�v������
	pMapChipManager_->Initialize(StageManager::GetInstance()->CurrentStageIndex() + 1, Vector3(-17.0f, +10.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

	// �Q�[���L�����N�^�[�}�l�[�W���[������
	pCharacterMan_->Initialize();

	// �J����������
	scrollCamera_.Initialize(Vector3(-15.0f, +10.0f, -30.0f), nullptr, Vector3());

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();

	// �L�����N�^�[
	{
		// �v���C���[
		{
			// �v���C���[����
			Player* newPlayer = new Player();
			
			// �y�b�g(�E�})����
			Horse* newHorse = new Horse();

			// �y�b�g������
			newHorse->Initialize({ {}, {}, {1.0f,1.0f,1.0f} });

			// �v���C���[������
			newPlayer->Initialize(
				{ {-100.0f,-100.0f,-100.0f}, {}, {1.0f,1.0f,1.0f} },
				newHorse
			);

			// �}��
			pCharacterMan_->PushBack(newHorse);
			pCharacterMan_->PushBack(newPlayer);
		}

		// �X���C��
		{
			// �X���C������
			Slime* newSlime = new Slime();

			// �X���C��������
			newSlime->Initialize({ {10.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// �}��
			pCharacterMan_->PushBack(newSlime);
		}

		// �X���C��
		{
			// �X���C������
			Slime* newSlime = new Slime();

			// �X���C��������
			newSlime->Initialize({ {40.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// �}��
			pCharacterMan_->PushBack(newSlime);
		}

		// �X���C��
		{
			// �X���C������
			Slime* newSlime = new Slime();

			// �X���C��������
			newSlime->Initialize({ {80.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// �}��
			pCharacterMan_->PushBack(newSlime);
		}

		// �X���C��
		{
			// �X���C������
			Slime* newSlime = new Slime();

			// �X���C��������
			newSlime->Initialize({ {120.0f,20.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// �}��
			pCharacterMan_->PushBack(newSlime);
		}
	}

	// UI
	uiMan_.Initialize();

	
	// �J�n���o�^�C�}�[
	startTimer_.Initialize(120, true);

	// �}�b�v�̑傫���ŃI�t�Z�b�g�l�ς���
	Vector3 offset = { pMapChipManager_->CurrentMapPointer()->Size().x_, pMapChipManager_->CurrentMapPointer()->Size().y_, 0.0f };
	cameraOffset_.Initialize(offset, {}, 2.0f);

	isStart_ = false;

	isStop_ = false;

	pause_.Initialize();
}
#pragma endregion


#pragma region �I������
void PlayScene::Finalize()
{
}
#pragma endregion


#pragma region �X�V
void PlayScene::Update()
{
	bool isReset = false;

	ImGui::Begin("Game");
	ImGui::Checkbox("isStop", &isStop_);
	isReset = ImGui::Button("Reset");
	ImGui::End();

	pause_.Update();

	if (isStop_ == false &&
		pause_.IsPause() == false)
	{
		startTimer_.Update();

		// �J�n���o�I����
		if (startTimer_.IsEnd() && isStart_ == false)
		{
			uiMan_.PlayStartAnimation();

			isStart_ = true;
		}

		uiMan_.Update();

		pLevel_->Update();

		pMapChipManager_->Update();

		// �J�n���o���X�V���Ȃ�
		pCharacterMan_->Update(isStart_);

		scrollCamera_.Update({ cameraOffset_.InOut(startTimer_.Ratio(), 0.4f) });
		transferVP_ = scrollCamera_.GetViewProjection();
	}
	
	transferVP_.UpdateMatrix();

	pCharacterMan_->DrawDebugText();

	// ���Z�b�g
	if (isReset || spKeys_->IsTrigger(DIK_R) || spPad_->IsTrigger(PadButton::XIP_DOWN))
	{
		SceneManager::GetInstance()->Change("PLAY");
	}


	StageManager::GetInstance()->Update();
}
#pragma endregion


#pragma region �`��
void PlayScene::Draw()
{
	pLevel_->Draw();

	pMapChipManager_->Draw();

	pCharacterMan_->Draw();

	uiMan_.Draw();

	pause_.Draw();
}
#pragma endregion