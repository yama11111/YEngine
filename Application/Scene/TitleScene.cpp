#include "TitleScene.h"
#include "SceneExecutive.h"
#include "MathVector.h"
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

}
#pragma endregion


#pragma region 初期化
void TitleScene::Initialize()
{
	transferVP_.Initialize();

	// ウィンドウサイズ を 3次元ベクトルにしておく
	Vector3 win = ConvertToVector3(WinSize);

	Vector3 logoPos = (win / 2.0f) - Vector3(0.0f, 32.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos }, pLogoSpr_));
	
	Vector3 startPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	startObj_.reset(DrawObjectForSprite2D::Create({ startPos }, pStartSpr_));

	Vector3 buttonPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	buttonObj_.reset(DrawObjectForSprite2D::Create({ buttonPos }, pButtonSpr_));

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
	buttonObj_->Update();

	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();


	// SPACE でゲーム開始
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		SceneExecutive::GetInstance()->Change("SELECT", "INFECTION", 2, 10);
	}
	
	// ESC でゲーム終了
	if (spKeys_->IsTrigger(DIK_ESCAPE))
	{
		SceneManager::GetInstance()->SetEnd(true);
	}
}
#pragma endregion


#pragma region 描画
void TitleScene::Draw()
{
	logoObj_->Draw("Sprite2DDefault", 0);
	startObj_->Draw("Sprite2DDefault", 0);
	buttonObj_->Draw("Sprite2DDefault", 0);
}
#pragma endregion