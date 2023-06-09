#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"

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
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	// �}�b�v�`�b�v������
	pMapChipManager_->Initialize(0, Vector3(), Vector3());

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();
	transferVP_.eye_ = Vector3(0, +2.5f, -20.0f);

	// �Q�[���L�����N�^�[�}�l�[�W���[���� + ������
	gameCharacterManager_.reset(new GameCharacterManager());
	gameCharacterManager_->Initialize();

	// �L�����N�^�[
	{
		// �v���C���[
		{
			// �v���C���[����
			Player* player = new Player();

			// �v���C���[������
			player->Initialize({});

			// �}��
			gameCharacterManager_->PushBack(player);
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
	gameCharacterManager_->Update();

	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void PlayScene::Draw()
{
	// �}�b�v�`�b�v�`��
	pMapChipManager_->Draw();

	// �Q�[���L�����N�^�[�`��
	gameCharacterManager_->Draw();
}
#pragma endregion