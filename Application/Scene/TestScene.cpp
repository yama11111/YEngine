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

#pragma region 名前空間宣言

using YGame::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static関連

#pragma endregion 


#pragma region 読み込み
void TestScene::Load()
{
	// 基底クラス
	BaseDrawer::StaticInitialize(&vp_);

	// デフォルト
	DefaultDrawer::StaticInitialize();

	// プレイヤー
	PlayerDrawer::StaticInitialize();

	// ウマ
	HorseDrawer::StaticInitialize();

	// スライム
	SlimeDrawer::StaticInitialize();

	// 斬撃攻撃
	SlashAttackDrawer::StaticInitialize();

	// 鼻息攻撃
	SnortAttackDrawer::StaticInitialize();

	// ブロック
	BlockDrawer::StaticInitialize();

	// ゴール
	GoalDrawer::StaticInitialize();

	// 天球
	SkydomeDrawer::StaticInitialize();

	// 雲
	CloudDrawer::StaticInitialize();
}
#pragma endregion


#pragma region 初期化
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


#pragma region 終了処理
void TestScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
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


#pragma region 描画
void TestScene::Draw()
{
	for (std::unique_ptr<BaseDrawer>& drawer : drawers_)
	{
		drawer->Draw();
	}
}
#pragma endregion