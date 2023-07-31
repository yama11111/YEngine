#include "UIManager.h"
#include "DrawObjectForSprite2D.h"
#include "Keys.h"
#include "Pad.h"
#include "Def.h"

using YGame::UIManager;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;
using YInput::PadButton;
using YInput::PadStick;

void UIManager::Initialize()
{
	if (buttonJump_ == nullptr)
	{
		Sprite2D* spriteUI = Sprite2D::Create({ { "Texture0", Texture::Load("UI/jump.png") } });

		Transform::Status statusUI;

		statusUI.scale_ = { 1.0f,1.0f,1.0f };
		statusUI.pos_ = Vector3(WinSize.x_, WinSize.y_, 0.0f) + Vector3(-160.0f, -160.0f, 0.0f);

		jumpUI_.reset(DrawObjectForSprite2D::Create(statusUI, spriteUI));


		Sprite2D* spriteButton = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png") } });

		Transform::Status statusButton;
		
		statusButton.scale_ = statusUI.scale_;
		
		float height = 64.0f * statusUI.scale_.y_ + 24.0f * statusButton.scale_.y_;
		statusButton.pos_ = statusUI.pos_ + Vector3(0.0f, +height, 0.0f);

		buttonJump_.reset(new UIButton());
		buttonJump_->Initialize(DrawObjectForSprite2D::Create(statusButton, spriteButton));
	}

	if (letterBox_ == nullptr)
	{
		letterBox_.reset(new UILetterBox());
	}

	letterBox_->Initialize(WinSize, 96.0f, 96.0f);


	isStartable_ = false;
}

void UIManager::Update()
{
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) || 
		Pad::GetInstance()->IsTrigger(PadButton::XIP_A))
	{
		buttonJump_->PressTrigger();
	}

	//if (Keys::GetInstance()->IsTrigger(DIK_RETURN) ||
	//	Pad::GetInstance()->IsTrigger(PadButton::XIP_X))
	//{
	//	buttonAttack_->PressTrigger();
	//}

	jumpUI_->Update();

	buttonJump_->Update();

	letterBox_->Update();
}

void UIManager::StartAnimation()
{
	letterBox_->Close(40, 3.0f);
}

void UIManager::Draw()
{
	letterBox_->Draw("Sprite2DDefault", 1);
	
	jumpUI_->Draw("Sprite2DDefault", 1);

	buttonJump_->Draw("Sprite2DDefault", 1);
}

void UIManager::StaticIntialize()
{
	UILetterBox::StaticInitialize();
}
