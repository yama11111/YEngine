#include "UIManager.h"
#include "Keys.h"
#include "Pad.h"
#include "Def.h"

using YGame::UIManager;
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
}

void UIManager::Initialize()
{
	Transform::Status statusUI;

	statusUI.scale_ = { 1.0f,1.0f,1.0f };
	statusUI.pos_ = Vector3(WinSize.x_, WinSize.y_, 0.0f) + Vector3(-160.0f, -160.0f, 0.0f);

	jumpUI_.reset(DrawObjectForSprite2D::Create(statusUI, pJumpSpr_));


	Transform::Status statusButton;

	statusButton.scale_ = statusUI.scale_;

	float height = 64.0f * statusUI.scale_.y_ + 24.0f * statusButton.scale_.y_;
	statusButton.pos_ = statusUI.pos_ + Vector3(0.0f, +height, 0.0f);

	buttonJump_.reset(UIButton::Create(DrawObjectForSprite2D::Create(statusButton, pButtonASpr_)));

	letterBox_.reset(new UILetterBox());

	letterBox_->Initialize(WinSize, 96.0f, 96.0f);
}

void UIManager::Update()
{
	bool isJump = (pKeys->IsDown(DIK_SPACE) || pPad->IsDown(PadButton::XIP_A));

	bool isAttack = (pKeys->IsDown(DIK_RETURN) || pPad->IsDown(PadButton::XIP_X));


	letterBox_->Update();
	
	buttonJump_->Update(isJump);

	jumpUI_->Update();

	//buttonAttack_->Update(isAttack);

	//attackUI_->Update();
}

void UIManager::PlayStartAnimation()
{
	letterBox_->Close(40, 3.0f);
}

void UIManager::Draw()
{
	letterBox_->Draw("Sprite2DDefault", 2);
	
	jumpUI_->Draw("Sprite2DDefault", 2);

	buttonJump_->Draw("Sprite2DDefault", 2);
}

void UIManager::Load()
{	
	pButtonASpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png") } });
	
	//pButtonXSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_X.png") } });

	pJumpSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/jump.png") } });

	//pAttackSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/jump.png") } });


	pKeys = Keys::GetInstance();

	pPad = Pad::GetInstance();
}
