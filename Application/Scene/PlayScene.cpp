#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Slime.h"

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
	pMapChipManager_ = MapChipManager::GetInstance();

	// �`��N���X
	BaseDrawer::StaticInitialize(&transferVP_);

	// �v���C���[
	Player::StaticInitialize(&scrollCamera_);
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	// �}�b�v�`�b�v������
	pMapChipManager_->Initialize(0, Vector3(-17.0f, +10.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

	// �Q�[���L�����N�^�[�}�l�[�W���[���� + ������
	characterMan_.reset(new CharacterManager());
	characterMan_->Initialize();

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

			// �v���C���[������
			newPlayer->Initialize({ {}, {}, {1.0f,1.0f,1.0f} });

			// �}��
			characterMan_->PushBack(newPlayer);
		}

		// �X���C��
		{
			// �X���C������
			Slime* newSlime = new Slime();

			// �X���C��������
			newSlime->Initialize({ {10.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// �}��
			characterMan_->PushBack(newSlime);
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
	characterMan_->Update();

	// �J�����X�V
	scrollCamera_.Update();

	// �r���[�v���W�F�N�V�������
	transferVP_ = scrollCamera_.GetViewProjection();

	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();

	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
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
	characterMan_->Draw();
}
#pragma endregion