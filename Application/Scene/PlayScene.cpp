#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Horse.h"
#include "Slime.h"

#include "DefaultDrawer.h"
#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "SlimeDrawer.h"
#include "SlashAttackDrawer.h"
#include "SnortAttackDrawer.h"
#include "BlockDrawer.h"
#include "GoalDrawer.h"
#include "CloudDrawer.h"
#include "SkydomeDrawer.h"

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
	pMapChipManager_->Load("demo.csv");

	// �`��N���X
	{
		BaseDrawer::StaticInitialize(&transferVP_);

		DefaultDrawer::StaticInitialize();

		PlayerDrawer::StaticInitialize();
		
		HorseDrawer::StaticInitialize();

		SlimeDrawer::StaticInitialize();
		
		SlashAttackDrawer::StaticInitialize();
		
		SnortAttackDrawer::StaticInitialize();

		BlockDrawer::StaticInitialize();

		GoalDrawer::StaticInitialize();

		SkydomeDrawer::StaticInitialize();

		CloudDrawer::StaticInitialize();
	}

	// �v���C���[
	Player::StaticInitialize(&scrollCamera_);
	
	// �y�b�g
	IPet::StaticInitialize(&scrollCamera_);
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	pLevel_ = Level::LoadJson("levelData.json");

	// �}�b�v�`�b�v������
	pMapChipManager_->Initialize(0, Vector3(-17.0f, +10.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

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
	pLevel_->Update();

	pMapChipManager_->Update();
	
	pCharacterMan_->Update();

	scrollCamera_.Update();
	transferVP_ = scrollCamera_.GetViewProjection();
	transferVP_.UpdateMatrix();

	pCharacterMan_->DrawDebugText();
	
	// ���Z�b�g
	if (spKeys_->IsTrigger(DIK_R) || spPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->Change("PLAY");
	}
}
#pragma endregion


#pragma region �`��
void PlayScene::Draw()
{
	pLevel_->Draw();

	pMapChipManager_->Draw();

	pCharacterMan_->Draw();
}
#pragma endregion