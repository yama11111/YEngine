#include "TitleScene.h"
#include "SceneExecutive.h"
#include "MathVector.h"
#include "BlockDrawer.h"
#include "SkydomeDrawer.h"
#include "CharacterConfig.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

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

	pLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_logo.png")} });
	
	pStartSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });
	
	pButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });

	BaseDrawer::StaticInitialize(&transferVP_);


	pMapChipManager_ = MapChipManager::GetInstance();


}
#pragma endregion


#pragma region 初期化
void TitleScene::Initialize()
{
	pLevel_ = Level::LoadJson("levelData.json");
	
	// ウィンドウサイズ を 3次元ベクトルにしておく
	Vector3 win = ConvertToVector3(WinSize);

	Vector3 logoPos = (win / 2.0f) - Vector3(0.0f, 256.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, pLogoSpr_));


	Vector3 startPos = (win / 2.0f) + Vector3(0.0f, 128.0f, 0.0f);
	startObj_.reset(DrawObjectForSprite2D::Create({ startPos, {}, {1.0f,1.0f,1.0f} }, pStartSpr_));

	startColor_.reset(ConstBufferObject<CBColor>::Create());
	startObj_->InsertConstBuffer(startColor_.get());

	Vector3 buttonPos = startPos + Vector3(0.0f, 96.0f, 0.0f);
	DrawObjectForSprite2D* newStartButton = DrawObjectForSprite2D::Create({ buttonPos, {}, {1.0f,1.0f,1.0f} }, pButtonSpr_);

	startButton_.reset(UIButton::Create(newStartButton));

	letterBox_.reset(new UILetterBox());

	letterBox_->Initialize(WinSize, 96.0f, 96.0f);


	// マップチップ初期化
	pMapChipManager_->Initialize(0, Vector3(-28.0f, +17.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

	
	horse_.Initialize();
	horseDra_.reset(HorseDrawer::Create(&horse_, 0));
	horseDra_->PlayAnimation(static_cast<uint16_t>(HorseDrawer::AnimationType::eMove), 10, true);

	player_.Initialize();
	player_.pos_ = PetConfig::kRiddenHeight;
	player_.parent_ = &horse_.m_;
	playerDra_.reset(PlayerDrawer::Create(&player_, 0));

	
	transferVP_.Initialize({ {+8.0f, +5.0f, -10.0f}, {0.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f} });
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
	logoObj_->Update();
	startObj_->Update();
	
	startButton_->Update(spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A));

	letterBox_->Update();

	horse_.rota_ = YMath::AdjustAngle({ +1.0f, 0.0f, 0.0f });
	horse_.UpdateMatrix();

	horseDra_->Update();

	player_.UpdateMatrix();
	playerDra_->Update();

	pMapChipManager_->Update();

	pLevel_->Update();

	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();


	// SPACE でゲーム開始
	if (spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A) && 
		TransitionManager::GetInstance()->IsFalling() == false)
	{
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 4, 10);

		startColor_->data_.baseColor = { 1.0f,1.0f,0.0f,1.0f };

		horseDra_->AbortAnimation(static_cast<uint16_t>(HorseDrawer::AnimationType::eMove));
		horseDra_->PlayAnimation(static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding), 8);
	}
	
	// ESC でゲーム終了
	if (spKeys_->IsTrigger(DIK_ESCAPE) || spPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->SetEnd(true);
	}
}
#pragma endregion


#pragma region 描画
void TitleScene::Draw()
{
	pLevel_->Draw();

	pMapChipManager_->Draw();

	horseDra_->Draw();

	playerDra_->Draw();


	logoObj_->Draw("Sprite2DDefault", 1);
	startObj_->Draw("Sprite2DDefault", 1);

	startButton_->Draw("Sprite2DDefault", 1);

	letterBox_->Draw("Sprite2DDefault", 2);
}
#pragma endregion