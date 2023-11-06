#include "PauseDrawer.h"
#include "ColorConfig.h"
#include "Lerp.h"
#include "Def.h"
#include <cassert>

using YGame::PauseDrawer;
using YMath::Vector3;

YGame::Sprite2D* PauseDrawer::spPauseLogo_ = nullptr;
std::array<YGame::Sprite2D*, PauseDrawer::kSelectionNum> PauseDrawer::spSelectionSprites_{};
YGame::Sprite2D* PauseDrawer::spBorder_ = nullptr;
YGame::Sprite2D* PauseDrawer::spCurten_ = nullptr;

namespace
{
	const size_t kResumeIndex	 = static_cast<size_t>(PauseDrawer::Selection::Resume); // 戻る
	const size_t kReStartIndex	 = static_cast<size_t>(PauseDrawer::Selection::ReStart); // リスタート
	const size_t kChangeIndex	 = static_cast<size_t>(PauseDrawer::Selection::Change); // 遷移

	const YMath::Vector4 kOnColor	 = { 1.0f,1.0f,1.0f,1.0f };
	const YMath::Vector4 kOffColor	 = { 0.3f,0.3f,0.3f,1.0f };
}

void PauseDrawer::LoadResource()
{
	spPauseLogo_ = Sprite2D::Create({ {"Texture0", Texture::Load("pause/pause.png")} });

	spSelectionSprites_[kResumeIndex] = Sprite2D::Create({ {"Texture0", Texture::Load("pause/restart.png")} });
	spSelectionSprites_[kReStartIndex] = Sprite2D::Create({ {"Texture0", Texture::Load("pause/reset.png")} });
	spSelectionSprites_[kChangeIndex] = Sprite2D::Create({ {"Texture0", Texture::Load("pause/select.png")} });
	
	spBorder_ = Sprite2D::Create({ {"Texture0", Texture::Load("white1x1.png")} });

	spCurten_ = Sprite2D::Create({ {"Texture0", Texture::Load("white1x1.png")} });
}

void PauseDrawer::Initialize()
{
	if (pauseLogo_ == nullptr)
	{
		pauseLogo_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spPauseLogo_));
	}
	
	for (size_t i = 0; i < selectionObjs_.size(); i++)
	{
		if(selectionObjs_[i].obj_ == nullptr)
		{
			selectionObjs_[i].obj_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spSelectionSprites_[i]));
		}
		if (selectionObjs_[i].color_ == nullptr)
		{
			selectionObjs_[i].color_.reset(ConstBufferObject<CBColor>::Create());
		}
		selectionObjs_[i].obj_->InsertConstBuffer(selectionObjs_[i].color_.get());
	}
	
	if (border_ == nullptr)
	{
		border_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spBorder_));
	}
	if (borderColor_ == nullptr)
	{
		borderColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	border_->InsertConstBuffer(borderColor_.get());

	if (curten_ == nullptr)
	{
		curten_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spCurten_));
	}
	if (curtenColor_ == nullptr)
	{
		curtenColor_.reset(ConstBufferObject<CBColor>::Create());
	}

	Reset();
}

void PauseDrawer::Reset()
{
	selection_ = Selection::Resume;
	
	isAct_ = false;
	animePow_.Initialize(20);

	pauseLogo_->transform_.Initialize({ {0.0f,128.0f,0.0f}, {}, {1.0f,1.0f,0.0f} });
	pauseLogoPosXEas_.Initialize(-256.0f, +256.0f, 3.0f);
	
	for (size_t i = 0; i < selectionObjs_.size(); i++)
	{
		selectionObjs_[i].obj_->transform_.Initialize(
			{
				{0.0f,320.0f + 128.0f * static_cast<float>(i),0.0f},
				{},
				{1.0f,1.0f,0.0f}
			}
		);
		selectionObjs_[i].isActPos_ = false;
		selectionObjs_[i].posXPow_.Initialize(20);
		selectionObjs_[i].posXEas_.Initialize(-512.0f, +512.0f - 32.0f * static_cast<float>(i), 3.0f);
		selectionObjs_[i].scalePow_.Initialize(8);
	}
	selectScaleEas_.Initialize({ -0.2f,-0.2f,0.0f }, {}, 3.0f);

	border_->transform_.Initialize(
		{
			{128.0f,-16.0f,0.0f},
			{0.0f,0.0f,+kPI / 16.0f},
			{288.0f,0.0f,0.0f}
		}
	);
	borderColor_->data_.baseColor = ColorConfig::skTurquoise[4];
	borderScaleYEas_.Initialize(0.0f, 2048.0f, 3.0f);
	
	curten_->transform_.Initialize({ Vector3(WinSize.x_, WinSize.y_, 0.0f) / 2.0f, {}, { WinSize.x_, WinSize.y_, 0.0f } });
	curten_->InsertConstBuffer(curtenColor_.get());
	curtenAlphaPow_.Initialize(20);
	curtenAlphaEas_.Initialize(0.0f, 0.6f, 3.0f);

	curtenAlphaPow_.Reset();
}

void PauseDrawer::SetSelection(const Selection select)
{
	assert(selection_ != Selection::End);

	selection_ = select;
}

void PauseDrawer::BootAnimation()
{
	isAct_ = true;

	selectionObjs_[0].isActPos_ = true;
}

void PauseDrawer::ShutdownAnimation()
{
	isAct_ = false;

	selectionObjs_[selectionObjs_.size() - 1].isActPos_ = false;
}

void PauseDrawer::Update()
{
	animePow_.Update(isAct_);

	pauseLogo_->Update({ {pauseLogoPosXEas_.InOut(animePow_.Ratio()),0.0f,0.0f} });
	
	for (size_t i = 0; i < selectionObjs_.size(); i++)
	{
		Transform::Status animeStatus;
		
		if (isAct_ && 0.2f <= selectionObjs_[i].posXPow_.Ratio())
		{
			PropagateSelection(i + 1);
		}
		if (isAct_ == false && selectionObjs_[i].posXPow_.Ratio() <= 0.8f)
		{
			PropagateSelection(i - 1);
		}
		selectionObjs_[i].posXPow_.Update(selectionObjs_[i].isActPos_);
		animeStatus.pos_.x_ = selectionObjs_[i].posXEas_.InOut(selectionObjs_[i].posXPow_.Ratio());
		
		bool isSelected = (selection_ == static_cast<Selection>(i));
		selectionObjs_[i].scalePow_.Update(isSelected);
		animeStatus.scale_ = selectScaleEas_.In(selectionObjs_[i].scalePow_.Ratio());
		
		selectionObjs_[i].obj_->Update(animeStatus);
		selectionObjs_[i].color_->data_.baseColor = isSelected ? kOnColor : kOffColor;
	}

	border_->Update({ {},{},{0.0f,borderScaleYEas_.InOut(animePow_.Ratio()),0.0f} });
	
	curten_->Update();
	curtenAlphaPow_.Update(isAct_);
	float alpha = curtenAlphaEas_.Out(curtenAlphaPow_.Ratio());
	curtenColor_->data_.baseColor = { 0.0f,0.0f,0.0f,alpha };
}


void PauseDrawer::PropagateSelection(const size_t index)
{
	if (index < 0 || selectionObjs_.size() <= index) { return; }

	selectionObjs_[index].isActPos_ = isAct_;
}

void PauseDrawer::Draw()
{
	curten_->Draw("Sprite2DDefault", 2);

	border_->Draw("Sprite2DDefault", 2);

	pauseLogo_->Draw("Sprite2DDefault", 1);
	
	for (size_t i = 0; i < selectionObjs_.size(); i++)
	{
		selectionObjs_[i].obj_->Draw("Sprite2DDefault", 1);
	}
}
