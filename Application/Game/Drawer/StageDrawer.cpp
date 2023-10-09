#include "StageDrawer.h"
#include "ColorConfig.h"
#include "Def.h"
#include <cassert>

using YGame::StageDrawer;

YGame::ViewProjection* StageDrawer::spVP_ = nullptr;
YGame::Sprite3D* StageDrawer::spFrameSpr_ = nullptr;
YGame::Sprite3D* StageDrawer::spTutorialSpr_ = nullptr;

void StageDrawer::LoadResource()
{
	spFrameSpr_		 = Sprite3D::Create({ { "Texture0", Texture::Load("select/frame.png")} });
	spTutorialSpr_	 = Sprite3D::Create({ { "Texture0", Texture::Load("select/tutorial_mark.png")} });
}

void StageDrawer::SetViewProjection(ViewProjection* pVP)
{
	assert(pVP);
	spVP_ = pVP;
}

void StageDrawer::Initialize(
	YMath::Matrix4* pParent,
	const uint32_t number, 
	const bool isTutorial, 
	const std::array<bool, 3>& isMissionClear)
{
	assert(spVP_);

	trfm_.Initialize();
	trfm_.parent_ = pParent;

	if (centerFrame_ == nullptr)
	{
		centerFrame_.reset(DrawObjectForSprite3D::Create(Transform::Status::Default(), false, false, spVP_, spFrameSpr_));
	}
	centerFrame_->SetParent(&trfm_.m_);
	if (color_ == nullptr)
	{
		color_.reset(ConstBufferObject<CBColor>::Create());
	}
	centerFrame_->InsertConstBuffer(color_.get());
	
	uiTrfm_.Initialize();
	uiTrfm_.parent_ = &trfm_.m_;
	
	if (uiNum_ == nullptr)
	{
		uiNum_.reset(UINumber::Create3D(number, 3, 0.5f, false, &uiTrfm_.m_, false, false, spVP_));
	}
	uiNum_->SetNumber(number);
	if (uiTutorial_ == nullptr)
	{
		uiTutorial_.reset(DrawObjectForSprite3D::Create(Transform::Status::Default(), false, false, spVP_, spTutorialSpr_));
	}
	uiTutorial_->SetParent(&uiTrfm_.m_);
	isTutorial_ = isTutorial;

	popScalePow_.Initialize(20);
	popScaleEas_.Initialize(0.0f, 1.0f, 3.0f);

	selectScalePow_.Initialize(20);
	selectScaleEas_.Initialize(0.0f, 1.0f, 3.0f);

	for (size_t i = 0; i < missionFrames_.size(); i++)
	{
		missionFrames_[i].isClear = isMissionClear[i];
		
		if (missionFrames_[i].frame == nullptr)
		{
			missionFrames_[i].frame.reset(
				DrawObjectForSprite3D::Create(Transform::Status::Default(), false, false, spVP_, spFrameSpr_));
		}
		missionFrames_[i].frame->SetParent(&trfm_.m_);

		if (missionFrames_[i].color == nullptr)
		{
			missionFrames_[i].color.reset(ConstBufferObject<CBColor>::Create());
		}
		missionFrames_[i].frame->InsertConstBuffer(missionFrames_[i].color.get());
		
		missionFrames_[i].popScalePow.Initialize(10);
		missionFrames_[i].popScaleEas.Initialize(0.0f, 1.0f + (0.25f * (i + 1)), 3.0f);
		
		missionFrames_[i].selectScalePow.Initialize(10);
		missionFrames_[i].selectScaleEas.Initialize(0.0f, 1.0f + (0.25f * (i + 1)), 3.0f);
	}

	Reset();
}

void StageDrawer::Reset()
{
	trfm_.Initialize();
	
	centerFrame_->transform_.Initialize();
	centerFrame_->transform_.scale_ = {};
	centerFrame_->transform_.rota_.z_ = kPI / 4.0f;
	color_->data_.baseColor = ColorConfig::skTurquoise[4];
	
	uiTrfm_.Initialize();
	uiTrfm_.scale_ = {};
	uiTutorial_->transform_.scale_ = { 0.8f, 0.96f, 1.0f };

	isPop_ = false;
	popScalePow_.Reset();

	isSelect_ = false;
	selectScalePow_.Reset();

	for (size_t i = 0; i < missionFrames_.size(); i++)
	{
		missionFrames_[i].frame->transform_.Initialize();
		missionFrames_[i].frame->transform_.scale_ = {};
		missionFrames_[i].frame->transform_.rota_.z_ = kPI / 4.0f;
		
		missionFrames_[i].isSelect = false;
		missionFrames_[i].selectScalePow.Reset();
		
		missionFrames_[i].isPop = false;
		missionFrames_[i].popScalePow.Reset();
	}
	
	missionFrames_[0].color->data_.baseColor = ColorConfig::skTurquoise[3];
	missionFrames_[1].color->data_.baseColor = ColorConfig::skTurquoise[2];
	missionFrames_[2].color->data_.baseColor = ColorConfig::skTurquoise[1];
}

void StageDrawer::PopAnimation()
{
	isPop_ = true;
}

void StageDrawer::SelectAnimation()
{
	isSelect_ = true;
}

void StageDrawer::ReleseAnimation()
{
	isSelect_ = false;

	for (size_t i = 0; i < missionFrames_.size(); i++)
	{
		missionFrames_[i].isSelect = false;
	}
}

void StageDrawer::UpdateActFlag()
{
	if (isPop_ && 0.5f <= popScalePow_.Ratio())
	{
		missionFrames_[0].isPop = true;
	}
	for (size_t i = 0; i < missionFrames_.size() - 1; i++)
	{
		if (missionFrames_[i].isPop && 0.4f <= missionFrames_[i].popScalePow.Ratio())
		{
			missionFrames_[i + 1].isPop = true;
		}
	}

	if (isSelect_)
	{
		if (0.5f <= selectScalePow_.Ratio())
		{
			missionFrames_[0].isSelect = true;
		}
		for (size_t i = 0; i < missionFrames_.size() - 1; i++)
		{
			if (missionFrames_[i].isSelect && 
				0.4f <= missionFrames_[i].selectScalePow.Ratio())
			{
				missionFrames_[i + 1].isSelect = true;
			}
		}
	}
}

void StageDrawer::Update()
{
	UpdateActFlag();

	trfm_.UpdateMatrix();

	float centerScale = 0.0f;

	popScalePow_.Update(isPop_);
	centerScale += popScaleEas_.InOut(popScalePow_.Ratio());

	selectScalePow_.Update(isSelect_);
	centerScale += selectScaleEas_.InOut(selectScalePow_.Ratio());

	centerFrame_->Update({ {}, {}, {centerScale, centerScale, 0.0f} });
	
	uiTrfm_.UpdateMatrix({ {}, {}, {centerScale, centerScale, 0.0f} });
	uiNum_->Update();
	uiTutorial_->Update();

	for (size_t i = 0; i < missionFrames_.size(); i++)
	{
		float missionScale = 0.0f;

		missionFrames_[i].popScalePow.Update(missionFrames_[i].isPop);
		missionScale += missionFrames_[i].popScaleEas.InOut(missionFrames_[i].popScalePow.Ratio());

		missionFrames_[i].selectScalePow.Update(missionFrames_[i].isSelect);
		missionScale += missionFrames_[i].selectScaleEas.InOut(missionFrames_[i].selectScalePow.Ratio());

		missionFrames_[i].frame->Update({ {}, {}, {missionScale, missionScale, 0.0f} });
	}
}

void StageDrawer::Draw()
{
	for (size_t i = 0; i < missionFrames_.size(); i++)
	{
		size_t index = missionFrames_.size() - 1 - i;
		if (missionFrames_[index].isClear)
		{
			missionFrames_[index].frame->Draw("Sprite3DDefault", 0);
		}
	}
	
	centerFrame_->Draw("Sprite3DDefault", 0);

	if (isTutorial_)
	{
		uiTutorial_->Draw("Sprite3DDefault", 0);
	}
	else
	{
		uiNum_->Draw("Sprite3DDefault", 0);
	}
}
