#include "InstructionsDrawer.h"
#include "DrawObjectForSprite3D.h"
#include "Keys.h"
#include "Pad.h"

using YGame::InstructionsDrawer;
using YGame::Sprite3D;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;
using YInput::PadButton;
using YInput::PadStick;

namespace
{
	Sprite3D* pButtonASpr = nullptr;
	Sprite3D* pButtonXSpr = nullptr;

	Keys* pKeys = nullptr;
	Pad* pPad = nullptr;

	const float kDistance = 32.0f;

	const YMath::Vector3 kJumpPos = { +kDistance, -kDistance, 0.0f };
	const YMath::Vector3 kJumpScale = { 288.0f, 64.0f, 1.0f };

	const YMath::Vector3 kAttackPos = { -kDistance, +kDistance, 0.0f };
	const YMath::Vector3 kAttackScale = { 288.0f, 64.0f, 1.0f };

	const std::string kShaderTag = "Sprite3DUI";
}

void InstructionsDrawer::LoadResource()
{
	pButtonASpr = Sprite3D::Create({ { "Texture0", Texture::Load("UI/play/button_jump.png") } });
	pButtonXSpr = Sprite3D::Create({ { "Texture0", Texture::Load("UI/play/button_drop.png") } });

	pKeys = Keys::GetInstance();
	pPad = Pad::GetInstance();
}

InstructionsDrawer* InstructionsDrawer::Create(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	InstructionsDrawer* newDrawer = new InstructionsDrawer();

	newDrawer->Initialize(pParent, pVP);

	return newDrawer;
}

void InstructionsDrawer::Initialize(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	transform_.Initialize();
	transform_.parent_ = pParent;

	// jump
	if (buttonJump_ == nullptr)
	{
		Transform::Status buttonStatus = Transform::Status::Default();
		buttonStatus.pos_ = kJumpPos;
		buttonStatus.scale_ = kJumpScale;

		buttonJump_.reset(UIButton::Create(DrawObjectForSprite3D::Create(buttonStatus, false, false, pVP, pButtonASpr)));
		buttonJump_->SetParent(&transform_.m);
	}

	// attack
	if (buttonAttack_ == nullptr)
	{
		Transform::Status buttonStatus = Transform::Status::Default();
		buttonStatus.pos_ = kAttackPos;
		buttonStatus.scale_ = kAttackScale;

		buttonAttack_.reset(UIButton::Create(DrawObjectForSprite3D::Create(buttonStatus, false, false, pVP, pButtonXSpr)));
		buttonAttack_->SetParent(&transform_.m);
	}
}

void InstructionsDrawer::Update()
{
	transform_.UpdateMatrix();
	
	buttonJump_->Update(pKeys->IsDown(DIK_SPACE) || pPad->IsDown(PadButton::XIP_A));
	buttonAttack_->Update(pKeys->IsDown(DIK_V) || pPad->IsDown(PadButton::XIP_X));
}

void InstructionsDrawer::Draw()
{
	buttonJump_->Draw(kShaderTag, 0);
	buttonAttack_->Draw(kShaderTag, 0);
}
