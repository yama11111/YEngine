#include "TestScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

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

using YGame::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���
void TestScene::Load()
{
	// ���N���X
	BaseDrawer::StaticInitialize(&vp_);

	// �f�t�H���g
	DefaultDrawer::StaticInitialize();

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

	// �S�[��
	GoalDrawer::StaticInitialize();

	// �V��
	SkydomeDrawer::StaticInitialize();

	// �_
	CloudDrawer::StaticInitialize();
}
#pragma endregion


#pragma region ������
void TestScene::Initialize()
{
	transform_.Initialize();
	
	vp_.Initialize();

	std::unique_ptr<PlayerDrawer> player;
	player->Initialize(&transform_, 1);
	drawers_.push_back(std::move(player));

	std::unique_ptr<SlimeDrawer> slime;
	slime->Initialize(&transform_, 1);
	drawers_.push_back(std::move(slime));

	std::unique_ptr<HorseDrawer> horse;
	horse->Initialize(&transform_, 1);
	drawers_.push_back(std::move(horse));
}
#pragma endregion


#pragma region �I������
void TestScene::Finalize()
{
}
#pragma endregion


#pragma region �X�V
void TestScene::Update()
{
	for (std::unique_ptr<BaseDrawer>& drawer : drawers_)
	{
		uint16_t animeBit = 0;

		drawer->PlayAnimation(animeBit, 10);
		drawer->Update();
	}
}
#pragma endregion


#pragma region �`��
void TestScene::Draw()
{
	for (std::unique_ptr<BaseDrawer>& drawer : drawers_)
	{
		drawer->Draw();
	}
}
#pragma endregion