#include "UIDrawer.h"
#include "ScoreManager.h"
#include "ColorConfig.h"
#include "Def.h"
#include "Keys.h"
#include "Pad.h"

using YGame::UIDrawer;
using YGame::Sprite2D;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;
using YInput::PadButton;
using YInput::PadStick;

namespace
{
	Sprite2D* pButtonASpr_ = nullptr;
	Sprite2D* pButtonXSpr_ = nullptr;
	Sprite2D* pJumpSpr_ = nullptr;
	Sprite2D* pAttackSpr_ = nullptr;
	
	Keys* pKeys = nullptr;
	Pad * pPad = nullptr;

	const std::string kShaderTag = "Sprite2DDefault";
}

void UIDrawer::LoadResource()
{
	pButtonASpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png") } });
	//pButtonXSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_X.png") } });

	pJumpSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/jump.png") } });
	//pAttackSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/jump.png") } });

	pKeys = Keys::GetInstance();
	pPad = Pad::GetInstance();
}

void UIDrawer::Initialize()
{
	letterBox_.reset(new UILetterBox());

	letterBox_->Initialize(WinSize, 96.0f, 96.0f);
	letterBox_->SetColor(YMath::GetColor(2, 38, 32, 255));

	// ジャンプ
	{
		Transform::Status uiStatus;

		uiStatus.scale_ = { 1.0f,1.0f,1.0f };
		uiStatus.pos_ = Vector3(WinSize.x_, WinSize.y_, 0.0f) + Vector3(-160.0f, -160.0f, 0.0f);

		uiJump_.reset(DrawObjectForSprite2D::Create(uiStatus, pJumpSpr_));


		Transform::Status buttonStatus;

		buttonStatus.scale_ = uiStatus.scale_;

		float height = 64.0f * uiStatus.scale_.y_ + 24.0f * buttonStatus.scale_.y_;
		buttonStatus.pos_ = uiStatus.pos_ + Vector3(0.0f, +height, 0.0f);

		buttonJump_.reset(UIButton::Create(DrawObjectForSprite2D::Create(buttonStatus, pButtonASpr_))); 
	}

	// 攻撃
	{
		//Transform::Status uiStatus;

		//uiStatus.scale_ = { 1.0f,1.0f,1.0f };
		//uiStatus.pos_ = Vector3(WinSize.x_, WinSize.y_, 0.0f) + Vector3(-160.0f, -160.0f, 0.0f);

		//uiAttack_.reset(DrawObjectForSprite2D::Create(uiStatus, pAttackSpr_));


		//Transform::Status buttonStatus;

		//buttonStatus.scale_ = uiStatus.scale_;

		//float height = 64.0f * uiStatus.scale_.y_ + 24.0f * buttonStatus.scale_.y_;
		//buttonStatus.pos_ = uiStatus.pos_ + Vector3(0.0f, +height, 0.0f);

		//buttonAttack_.reset(UIButton::Create(DrawObjectForSprite2D::Create(buttonStatus, pButtonXSpr_)));
	}

	// スコア
	{
		Transform::Status scoreStatus;
		scoreStatus.pos_ = { WinSize.x_ - 320.0f, +96.0f, 0.0f };
		scoreStatus.scale_ = { 1.0f,1.0f,1.0f };

		scoreTrfm_.Initialize(scoreStatus);
		scoreDra_.reset(ScoreDrawer::Create(&scoreTrfm_.m_, kShaderTag, 2)); 
	}
}

void UIDrawer::Update()
{
	letterBox_->Update();
	
	bool isJump = (pKeys->IsDown(DIK_SPACE) || pPad->IsDown(PadButton::XIP_A));
	buttonJump_->Update(isJump);
	uiJump_->Update();

	//bool isAttack = (pKeys->IsDown(DIK_RETURN) || pPad->IsDown(PadButton::XIP_X));
	//buttonAttack_->Update(isAttack);
	//uiAttack_->Update();

	scoreTrfm_.UpdateMatrix();
	//scoreDra_->ChangeScoreAnimation(ScoreManager::GetInstance()->);
	scoreDra_->Update();
}

void UIDrawer::PlayStartAnimation()
{
	letterBox_->Close(40, 3.0f);
}

void UIDrawer::Draw()
{
	letterBox_->Draw(kShaderTag, 2);
	
	uiJump_->Draw(kShaderTag, 2);

	buttonJump_->Draw(kShaderTag, 2);

	scoreDra_->Draw();
}
