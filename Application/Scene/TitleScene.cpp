#include "TitleScene.h"
#include "SceneManager.h"
#include "MathVector.h"
#include "GameObjectManager.h"
#include "ViewProjectionManager.h"
#include "Level.h"
#include "WorldKey.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "CircleShadowManager.h"

#pragma region 名前空間宣言

using YGame::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void TitleScene::Load()
{
	ViewProjectionManager::GetInstance()->Insert("World", &transferVP_);

	TitleDrawer::LoadResource();
}
#pragma endregion


#pragma region 初期化
void TitleScene::Initialize()
{
	CircleShadowManager::GetInstance()->Intialize();

	GameObjectManager::GetInstance()->Initialize();
	//Level::LoadJson("title.json", WorldKey::eWorldKey);

	titleDra_.Initialize();
	titleDra_.OpeningAnimation();
	
	transferVP_.Initialize({ 
		{ 0.0f, 4.0f, -20.0f },
		{ 0.0f, 4.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f }
	});
}
#pragma endregion


#pragma region 終了処理
void TitleScene::Finalize()
{

}
#pragma endregion


#pragma region 更新
void TitleScene::Update()
{
	if (spKeys_->IsTrigger(DIK_O) || spPad_->IsTrigger(PadButton::XIP_Y))
	{
		titleDra_.OpeningAnimation();
	}
	titleDra_.Update();

	CircleShadowManager::GetInstance()->Reset();
	GameObjectManager::GetInstance()->Prepare(true);
	GameObjectManager::GetInstance()->Update({ WorldKeyStr(WorldKey::eWorldKey) });

	transferVP_.UpdateMatrix();

	// ゲーム開始
	if (spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A) && 
		SceneManager::GetInstance()->IsTransition() == false)
	{
		SceneManager::GetInstance()->Transition("SELECT", "WAVE");

		titleDra_.StartAnimation();
	}
	
	// ゲーム終了
	if (spKeys_->IsTrigger(DIK_ESCAPE) || spPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->SetEnd(true);
	}
}
#pragma endregion


#pragma region 描画
void TitleScene::Draw()
{
	GameObjectManager::GetInstance()->Draw({ WorldKeyStr(WorldKey::eWorldKey) });

	titleDra_.Draw();
}
#pragma endregion