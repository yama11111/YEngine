#include "StageStatusDrawer.h"
#include "ColorConfig.h"
#include "Lerp.h"
#include <imgui.h>

using YGame::StageStatusDrawer;
using YGame::Sprite2D;
using YMath::Vector3;

namespace
{
	Sprite2D* pStageLogoSpr_ = nullptr;
	Sprite2D* pBandSpr_ = nullptr;
	Sprite2D* pStarSpr_ = nullptr;
	Sprite2D* pStarFrameSpr_ = nullptr;
	Sprite2D* pMissionSpr_ = nullptr;
	Sprite2D* pTutorialLogoSpr_ = nullptr;
	Sprite2D* pTutorialMarkSpr_ = nullptr;
}

void StageStatusDrawer::LoadResource()
{
	pStageLogoSpr_		 = Sprite2D::Create({ { "Texture0", Texture::Load("select/stage_logo.png")} });
	pBandSpr_			 = Sprite2D::Create({ { "Texture0", Texture::Load("select/band.png")} });
	
	pStarSpr_			 = Sprite2D::Create({ { "Texture0", Texture::Load("select/star.png")} });
	pStarFrameSpr_		 = Sprite2D::Create({ { "Texture0", Texture::Load("select/star_frame.png")} });
	
	pMissionSpr_		 = Sprite2D::Create({ { "Texture0", Texture::Load("select/mission_logo.png")} });
	
	pTutorialLogoSpr_	 = Sprite2D::Create({ { "Texture0", Texture::Load("select/tutorial_logo.png")} });
	pTutorialMarkSpr_	 = Sprite2D::Create({ { "Texture0", Texture::Load("select/tutorial_mark.png")} });
}

void StageStatusDrawer::Initialize(const uint32_t number, const bool isTutorial, 
	const std::array<uint32_t, 3>& score, const std::array<bool, 3>& isMissionClear)
{
	// ステージタイトル
	{
		titleTrfm_.Initialize();
		titlePosPow_.Initialize(30);
		titlePosEas_.Initialize(+720.0f, 0.0f, 4.0f);

		for (size_t i = 0; i < bands_.size(); i++)
		{
			if (bands_[i].band == nullptr)
			{
				bands_[i].band.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pBandSpr_));
			}
			if (bands_[i].color == nullptr)
			{
				bands_[i].color.reset(ConstBufferObject<CBColor>::Create());
			}
			bands_[i].band->InsertConstBuffer(bands_[i].color.get());

			bands_[i].posPow.Initialize(20);
		}
		bands_[0].posEas.Initialize(+720.0f, -64.0f, 4.0f);
		bands_[1].posEas.Initialize(+720.0f, 0.0f, 4.0f);

		if (logo_ == nullptr)
		{
			logo_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pStageLogoSpr_));
		}
		logo_->SetParent(&titleTrfm_.m);
		if (number_ == nullptr)
		{
			numberTrfm_.Initialize();
			number_.reset(UINumber::Create2D(number, 3, 0.5f, false, true, &numberTrfm_.m));
		}
		numberTrfm_.parent_ = &titleTrfm_.m;

		if (tutorialLogo_ == nullptr)
		{
			tutorialLogo_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pTutorialLogoSpr_));
		}
		tutorialLogo_->SetParent(&titleTrfm_.m);
		if (tutorialMark_ == nullptr)
		{
			tutorialMark_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pTutorialMarkSpr_));
		}
		tutorialMark_->SetParent(&titleTrfm_.m);

		isTutorial_ = isTutorial;

		if (color_ == nullptr)
		{
			color_.reset(ConstBufferObject<CBColor>::Create());
		}
		logo_->InsertConstBuffer(color_.get());
		number_->InsertConstBuffer(color_.get());
		tutorialLogo_->InsertConstBuffer(color_.get());
		tutorialMark_->InsertConstBuffer(color_.get());
	}

	// ミッション
	{
		for (size_t i = 0; i < missions_.size(); i++)
		{
			missions_[i].trfm.Initialize();
			if (missions_[i].star == nullptr)
			{
				missions_[i].star.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pStarSpr_));
				missions_[i].star->SetParent(&missions_[i].trfm.m);
			}
			if (missions_[i].starFrame == nullptr)
			{
				missions_[i].starFrame.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pStarFrameSpr_));
				missions_[i].starFrame->SetParent(&missions_[i].trfm.m);
			}

			missions_[i].scoreTrfm.Initialize();
			missions_[i].scoreTrfm.parent_ = &missions_[i].trfm.m;
			if (missions_[i].score == nullptr)
			{
				missions_[i].score.reset(UINumber::Create2D(score[i], 7, 80.0f, false, true, &missions_[i].scoreTrfm.m));
			}
			if (missions_[i].mission == nullptr)
			{
				missions_[i].mission.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pMissionSpr_));
				missions_[i].mission->SetParent(&missions_[i].trfm.m);
			}

			if (missions_[i].color == nullptr)
			{
				missions_[i].color.reset(ConstBufferObject<CBColor>::Create());
			}
			missions_[i].star->InsertConstBuffer(missions_[i].color.get());
			missions_[i].starFrame->InsertConstBuffer(missions_[i].color.get());
			missions_[i].score->InsertConstBuffer(missions_[i].color.get());
			missions_[i].mission->InsertConstBuffer(missions_[i].color.get());

			missions_[i].posPow.Initialize(8);

			missions_[i].isClear = isMissionClear[i];
		}

		missionPosEas_.Initialize(+720.0f, 0.0f, 4.0f);

	}
	
	alphaPow_.Initialize(10);

	Reset();
}

void StageStatusDrawer::Reset()
{
	isAct_ = false;
	
	// ステージタイトル
	{
		titleTrfm_.Initialize();
		titleTrfm_.pos_ = { 1024.0f, 144.0f, 0.0f };

		titlePosPow_.Reset();

		for (size_t i = 0; i < bands_.size(); i++)
		{
			bands_[i].band->transform_.Initialize();
			bands_[i].band->transform_.pos_ = { 1024.0f, 144.0f, 0.0f };
			bands_[i].band->transform_.scale_ = { 1.0f, 1.0f, 0.0f };

			bands_[i].isAct = false;
			bands_[i].posPow.Reset();
		}
		bands_[0].color->data_.baseColor = ColorConfig::skTurquoise[4];
		bands_[1].color->data_.baseColor = ColorConfig::skTurquoise[3];

		logo_->transform_.Initialize();
		logo_->transform_.pos_.x = -64.0f;
		logo_->transform_.scale_ = { 0.5f, 0.5f, 0.0f };

		numberTrfm_.Initialize();
		numberTrfm_.pos_.x = +160.0f;
		numberTrfm_.scale_ = { 1.0f, 1.0f, 0.0f };

		tutorialLogo_->transform_.Initialize();
		tutorialLogo_->transform_.pos_.x = -48.0f;
		tutorialLogo_->transform_.scale_ = { 0.4f, 0.4f, 0.0f };

		tutorialMark_->transform_.Initialize();
		tutorialMark_->transform_.pos_.x = +192.0f;
		tutorialMark_->transform_.scale_ = { 1.0f, 1.0f, 0.0f };
	}

	// ミッション
	{
		for (size_t i = 0; i < missions_.size(); i++)
		{
			missions_[i].trfm.Initialize();
			float posY = 128.0f * static_cast<float>(i);
			missions_[i].trfm.pos_ = titleTrfm_.pos_ + Vector3(0.0f, 160.0f + posY, 0.0f);
			missions_[i].trfm.scale_ = { 0.75f,0.75f,0.0f };

			Vector3 starPos = { -432.0f, 0.0f, 0.0f };
			missions_[i].star->transform_.Initialize();
			missions_[i].star->transform_.pos_ = starPos;
			missions_[i].starFrame->transform_.Initialize();
			missions_[i].starFrame->transform_.pos_ = starPos;

			missions_[i].scoreTrfm.Initialize();
			missions_[i].scoreTrfm.pos_ = { -128.0f, 0.0f, 0.0f };
			missions_[i].scoreTrfm.scale_ = { 1.0f, 1.0f, 0.0f };

			missions_[i].mission->transform_.Initialize();
			missions_[i].mission->transform_.pos_ = { +192.0f, 0.0f, 0.0f };
			missions_[i].mission->transform_.scale_ = { 0.5f, 0.5f, 0.0f };

			missions_[i].isAct = false;
			missions_[i].posPow.Reset();

			if (missions_[i].isClear == false)
			{
				missions_[i].color->data_.baseColor = { 0.75f,0.75f,0.75f,0.0f };
			}
		}
	}
}

void StageStatusDrawer::UpdateActFlag()
{
	for (size_t i = 0; i < bands_.size(); i++)
	{
		if (bands_[i].isAct &&
			0.5f <= bands_[i].posPow.Ratio())
		{
			if (i <= 0)
			{
				bands_[i + 1].isAct = true;
			}
			else
			{
				missions_[0].isAct = true;
			}
		}
	}

	for (size_t i = 0; i < missions_.size() - 1; i++)
	{
		if (bands_[bands_.size() - 1].isAct == false) { break; }
		
		if (missions_[i].isAct &&
			0.5f <= missions_[i].posPow.Ratio())
		{
			missions_[i + 1].isAct = true;
		}
	}
}

void StageStatusDrawer::Update()
{
	UpdateActFlag();

	titlePosPow_.Update(isAct_);
	float titlePosX = titlePosEas_.InOut(titlePosPow_.Ratio());

	titleTrfm_.UpdateMatrix({ {titlePosX, 0.0f, 0.0f} });

	alphaPow_.Update(isAct_);
	float alpha = YMath::EaseInOut(0.0f, 1.0f, alphaPow_.Ratio(), 3.0f);
	color_->data_.baseColor.w = alpha;
	
	for (size_t i = 0; i < bands_.size(); i++)
	{
		bands_[i].posPow.Update(bands_[i].isAct);
		float bandPosX = bands_[i].posEas.InOut(bands_[i].posPow.Ratio());

		bands_[i].band->Update({ {bandPosX, 0.0f, 0.0f} });
		bands_[i].color->data_.baseColor.w = alpha;
	}

	if (isTutorial_)
	{
		tutorialLogo_->Update();
		tutorialMark_->Update();
	}
	else
	{
		logo_->Update();
		numberTrfm_.UpdateMatrix();
		number_->Update();
	}

	for (size_t i = 0; i < missions_.size(); i++)
	{
		missions_[i].posPow.Update(missions_[i].isAct);
		float missionPosX = missionPosEas_.InOut(missions_[i].posPow.Ratio());

		missions_[i].trfm.UpdateMatrix({ {missionPosX, 0.0f, 0.0f} });
		
		if (missions_[i].isClear) { missions_[i].star->Update(); }
		missions_[i].starFrame->Update();
		missions_[i].scoreTrfm.UpdateMatrix();
		missions_[i].score->Update();
		missions_[i].mission->Update();

		missions_[i].color->data_.baseColor.w = alpha;
	}
}

void StageStatusDrawer::Draw()
{
	for (size_t i = 0; i < bands_.size(); i++)
	{
		bands_[i].band->Draw("Sprite2DDefault", 2);
	}
	
	if (isTutorial_)
	{
		tutorialLogo_->Draw("Sprite2DDefault", 1);
		tutorialMark_->Draw("Sprite2DDefault", 1);
	}
	else
	{
		logo_->Draw("Sprite2DDefault", 1);
		number_->Draw("Sprite2DDefault", 1);
	}
	
	for (size_t i = 0; i < missions_.size(); i++)
	{
		missions_[i].starFrame->Draw("Sprite2DDefault", 1);
		if (missions_[i].isClear) { missions_[i].star->Draw("Sprite2DDefault", 1); }
		missions_[i].score->Draw("Sprite2DDefault", 1);
		missions_[i].mission->Draw("Sprite2DDefault", 1);
	}
}

void StageStatusDrawer::AppearAnimation()
{
	isAct_ = true;

	bands_[0].isAct = true;
}

void StageStatusDrawer::DisappearAnimation()
{
	isAct_ = false;

	for (size_t i = 0; i < bands_.size(); i++)
	{
		bands_[i].isAct = false;
	}
	for (size_t i = 0; i < missions_.size(); i++)
	{
		missions_[i].isAct = false;
	}
}
