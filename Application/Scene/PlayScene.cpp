#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"

#pragma region 名前空間宣言

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void PlayScene::Load()
{
	// シングルトン
	pMapChipManager_ = MapChipManager::GetInstance();
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// マップチップ初期化
	pMapChipManager_->Initialize(0, Vector3(), Vector3());

	// ビュープロジェクション初期化
	transferVP_.Initialize();
	transferVP_.eye_ = Vector3(0, +2.5f, -20.0f);

	// ゲームキャラクターマネージャー生成 + 初期化
	gameCharacterManager_.reset(new GameCharacterManager());
	gameCharacterManager_->Initialize();

	// キャラクター
	{
		// プレイヤー
		{
			// プレイヤー生成
			Player* player = new Player();

			// プレイヤー初期化
			player->Initialize({});

			// 挿入
			gameCharacterManager_->PushBack(player);
		}
	}
}
#pragma endregion


#pragma region 終了処理
void PlayScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void PlayScene::Update()
{
	// マップチップ更新
	pMapChipManager_->Update();
	
	// ゲームキャラクター更新
	gameCharacterManager_->Update();

	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region 描画
void PlayScene::Draw()
{
	// マップチップ描画
	pMapChipManager_->Draw();

	// ゲームキャラクター描画
	gameCharacterManager_->Draw();
}
#pragma endregion