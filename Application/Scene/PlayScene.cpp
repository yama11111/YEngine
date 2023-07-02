#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Horse.h"
#include "Slime.h"

#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "SlimeDrawer.h"
#include "SlashAttackDrawer.h"
#include "SnortAttackDrawer.h"
#include "BlockDrawer.h"

#pragma region ���O��Ԑ錾

using YScene::PlayScene;
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
	// �V���O���g��
	pCharacterMan_ = CharacterManager::GetInstance();
	pMapChipManager_ = MapChipManager::GetInstance();

	// �`��N���X
	{
		// ���N���X
		BaseDrawer::StaticInitialize(&transferVP_);

		// �v���C���[
		PlayerDrawer::StaticInitialize();
		
		// �E�}
		HorseDrawer::StaticInitialize();

		// �X���C��
		SlimeDrawer::StaticInitialize();
		
		// �a���U��
		SlashAttackDrawer::StaticInitialize();
		
		// �@���U��
		SnortAttackDrawer::StaticInitialize();

		// �u���b�N
		BlockDrawer::StaticInitialize();
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
	// �}�b�v�`�b�v������
	pMapChipManager_->Initialize(0, Vector3(-17.0f, +10.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

	// �Q�[���L�����N�^�[�}�l�[�W���[������
	pCharacterMan_->Initialize();

	// �J����������
	scrollCamera_.Initialize(Vector3(-20.0f, +10.0f, -20.0f), nullptr, Vector3());

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
	// �}�b�v�`�b�v�X�V
	pMapChipManager_->Update();
	
	// �Q�[���L�����N�^�[�X�V
	pCharacterMan_->Update();

	// �J�����X�V
	scrollCamera_.Update();

	// �r���[�v���W�F�N�V�������
	transferVP_ = scrollCamera_.GetViewProjection();

	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();

	// �f�o�b�O�`��
	pCharacterMan_->DrawDebugText();
	
	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R) || sPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->Change("PLAY");
	}
}
#pragma endregion


#pragma region �`��
void PlayScene::Draw()
{
	// �}�b�v�`�b�v�`��
	pMapChipManager_->Draw();

	// �Q�[���L�����N�^�[�`��
	pCharacterMan_->Draw();
}
#pragma endregion