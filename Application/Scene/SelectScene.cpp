#include "SelectScene.h"
#include "SceneExecutive.h"
#include "MathVector.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言

using YGame::SelectScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void SelectScene::Load()
{
	pLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_logo.png")} });

	pStartSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });
	
	pNumberSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });
	
	pStickSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("winHalf.png")} });

	pButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });

}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	// ウィンドウサイズ を 3次元ベクトルにしておく
	Vector3 win = ConvertToVector3(WinSize);


	Vector3 logoPos = (win / 2.0f) - Vector3(0.0f, 32.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, pLogoSpr_));

	Vector3 startPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	startObj_.reset(DrawObjectForSprite2D::Create({ startPos, {}, {1.0f,1.0f,1.0f} }, pStartSpr_));
		
	Vector3 numberPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	numberObj_.reset(DrawObjectForSprite2D::Create({ numberPos, {}, {1.0f,1.0f,1.0f} }, pNumberSpr_));

	Vector3 stickPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	stickObj_.reset(DrawObjectForSprite2D::Create({ stickPos, {}, {1.0f,1.0f,1.0f} }, pStickSpr_));
	
	Vector3 buttonPos = (win / 2.0f) + Vector3(0.0f, 32.0f, 0.0f);
	buttonObj_.reset(DrawObjectForSprite2D::Create({ buttonPos, {}, {1.0f,1.0f,1.0f} }, pButtonSpr_));
	
	num.Initialize();
	num.pos_ = win / 2.0f;
	//num.scale_ = ;

	uiDigit_.reset(UIDigit::Create(8, &num.m_));
	uiNumber_.reset(UINumber::Create(42037, 10, 64.0f, false, &num.m_));

	transferVP_.Initialize();
}
#pragma endregion


#pragma region 終了処理
void SelectScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void SelectScene::Update()
{
	logoObj_->Update();
	startObj_->Update();
	numberObj_->Update();
	stickObj_->Update();
	buttonObj_->Update();

	num.UpdateMatrix();
	uiDigit_->Update();
	uiNumber_->Update();

	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();


	// SPACE でゲーム開始
	if (spKeys_->IsTrigger(DIK_SPACE))
	{
		SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 2, 10);
	}

	// ESC でタイトルに戻る
	if (spKeys_->IsTrigger(DIK_ESCAPE))
	{
		SceneExecutive::GetInstance()->Change("TITLE", "BLACKOUT", 20, 10);
	}
}
#pragma endregion


#pragma region 描画

void SelectScene::Draw()
{
	//logoObj_->Draw("Sprite2DDefault", 2);
	//startObj_->Draw("Sprite2DDefault", 2);
	//numberObj_->Draw("Sprite2DDefault", 2);
	//buttonObj_->Draw("Sprite2DDefault", 2);
	stickObj_->Draw("Sprite2DDefault", 5);

	//uiDigit_->Draw("Sprite2DDefault", 1);
	uiNumber_->Draw("Sprite2DDefault", 2);
}
#pragma endregion