#include "BeginingDrawer.h"
#include "StageManager.h"
#include "Lerp.h"
#include "Def.h"
#include "ColorConfig.h"
#include "MathVector.h"
#include <cassert>

using YGame::BeginingDrawer;
using YGame::Sprite2D;
using YMath::Vector3;

namespace
{
	static Sprite2D* pRectSpr = nullptr;
	static Sprite2D* pTutorialSpr = nullptr;
	
	static Sprite2D* pStarSpr = nullptr;
	static Sprite2D* pStarFrameSpr = nullptr;
	static Sprite2D* pMissionSpr = nullptr;
	
	static Sprite2D* pBandSpr = nullptr;
}

void BeginingDrawer::LoadResource()
{
	pRectSpr		 = Sprite2D::Create({ {"Texture0", Texture::Load("select/frame.png") } });
	pTutorialSpr	 = Sprite2D::Create({ {"Texture0", Texture::Load("select/tutorial_mark.png") } });

	pStarSpr		 = Sprite2D::Create({ {"Texture0", Texture::Load("select/star.png") } });
	pStarFrameSpr	 = Sprite2D::Create({ {"Texture0", Texture::Load("select/star_frame.png") } });
	pMissionSpr		 = Sprite2D::Create({ {"Texture0", Texture::Load("select/mission_logo.png") } });

	pBandSpr		 = Sprite2D::Create({ {"Texture0", Texture::Load("white1x1.png") } });
}

void BeginingDrawer::Initialize()
{
	// UI
	{
		if (ui_.num == nullptr)
		{
			ui_.num.reset(UINumber::Create2D(0, 2, 32.0f, false, true, &ui_.trfm.m_));
		}
		ui_.num->SetParent(&ui_.trfm.m_);
		ui_.num->SetNumber(StageManager::GetInstance()->CurrentStageIndex());
		if (ui_.tutorial == nullptr)
		{
			ui_.tutorial.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pTutorialSpr));
		}
		ui_.tutorial->SetParent(&ui_.trfm.m_);
		if (ui_.color == nullptr)
		{
			ui_.color.reset(ConstBufferObject<CBColor>::Create());
		}
		ui_.num->InsertConstBuffer(ui_.color.get());
		ui_.tutorial->InsertConstBuffer(ui_.color.get());

		ui_.isTutorial =
			StageManager::GetInstance()->Status(StageManager::GetInstance()->CurrentStageIndex()).isTutorial;
	}

	// 枠
	{
		if (center_.rect == nullptr)
		{
			center_.rect.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pRectSpr));
		}
		center_.rect->SetParent(&rectTrfm_.m_);
		if (center_.color == nullptr)
		{
			center_.color.reset(ConstBufferObject<CBColor>::Create());
		}
		center_.rect->InsertConstBuffer(center_.color.get());

		for (size_t i = 0; i < missions_.size(); i++)
		{
			if (missions_[i].rect == nullptr)
			{
				missions_[i].rect.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pRectSpr));
			}
			missions_[i].rect->SetParent(&rectTrfm_.m_);
			if (missions_[i].color == nullptr)
			{
				missions_[i].color.reset(ConstBufferObject<CBColor>::Create());
			}
			missions_[i].rect->InsertConstBuffer(missions_[i].color.get());

			missions_[i].isClear =
				StageManager::GetInstance()->Status(StageManager::GetInstance()->CurrentStageIndex()).isMissionClear[i];
		}
	}

	// 帯
	{
		if (band_.band == nullptr)
		{
			band_.band.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pBandSpr));
		}
		if (band_.color == nullptr)
		{
			band_.color.reset(ConstBufferObject<CBColor>::Create());
		}
		band_.band->InsertConstBuffer(band_.color.get());
	}

	// ミッション
	{
		for (size_t i = 0; i < missionUIs_.size(); i++)
		{
			if (missionUIs_[i].star == nullptr)
			{
				missionUIs_[i].star.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pStarSpr));
			}
			missionUIs_[i].star->SetParent(&missionUIs_[i].trfm.m_);
			if (missionUIs_[i].starFrame == nullptr)
			{
				missionUIs_[i].starFrame.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pStarFrameSpr));
			}
			missionUIs_[i].starFrame->SetParent(&missionUIs_[i].trfm.m_);

			missionUIs_[i].scoreTrfm.Initialize();
			missionUIs_[i].scoreTrfm.parent_ = &missionUIs_[i].trfm.m_;
			if (missionUIs_[i].score == nullptr)
			{
				missionUIs_[i].score.reset(UINumber::Create2D(
					StageManager::GetInstance()->Status(StageManager::GetInstance()->CurrentStageIndex()).mission[i],
					7, 80.0f, false, true, &missionUIs_[i].scoreTrfm.m_));
			}
			if (missionUIs_[i].mission == nullptr)
			{
				missionUIs_[i].mission.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pMissionSpr));
			}
			missionUIs_[i].mission->SetParent(&missionUIs_[i].trfm.m_);

			if (missionUIs_[i].color == nullptr)
			{
				missionUIs_[i].color.reset(ConstBufferObject<CBColor>::Create());
			}
			missionUIs_[i].star->InsertConstBuffer(missionUIs_[i].color.get());
			missionUIs_[i].starFrame->InsertConstBuffer(missionUIs_[i].color.get());
			missionUIs_[i].score->InsertConstBuffer(missionUIs_[i].color.get());
			missionUIs_[i].mission->InsertConstBuffer(missionUIs_[i].color.get());

			missionUIs_[i].isClear =
				StageManager::GetInstance()->Status(StageManager::GetInstance()->CurrentStageIndex()).isMissionClear[i];
		}
	}

	Reset();
}

void BeginingDrawer::Reset()
{
	Vector3 winHalfSize = YMath::ConvertToVector3(WinSize) / 2.0f;

	Vector3 titlePos = winHalfSize + Vector3(0, -64.0f, 0);

	// UI
	{
		ui_.trfm.Initialize();
		ui_.trfm.pos_ = titlePos;
		float uiScale = 2.0f;
		ui_.trfm.scale_ = Vector3(uiScale, uiScale, 0.0f);

		ui_.tutorial->transform_.scale_ = Vector3(0.8f, 0.96f, 0.0f);

		ui_.scalePow.Initialize(20);
		ui_.scaleEas.Initialize(-uiScale, 0.0f, 5.0f);
	}

	// 枠
	{
		rectTrfm_.Initialize();
		rectTrfm_.pos_ = titlePos;
		rectTrfm_.rota_.z_ = kPI / 4.0f;
		rectTrfm_.scale_ = Vector3(1.0f, 1.0f, 0.0f);

		center_.rect->transform_.Initialize();
		float centerScale = 1.0f;
		center_.rect->transform_.scale_ = Vector3(centerScale, centerScale, 0.0f);
		
		center_.isAct = false;
		center_.scalePow.Initialize(20);
		center_.scaleEas.Initialize(-centerScale, 0.0f, 3.0f);

		center_.color->data_.baseColor = ColorConfig::skTurquoise[4];

		for (size_t i = 0; i < missions_.size(); i++)
		{
			missions_[i].rect->transform_.Initialize();
			float missionScale = centerScale + (0.25f * (i + 1));
			missions_[i].rect->transform_.scale_ = Vector3(missionScale, missionScale, 0.0f);

			missions_[i].isAct = false;
			missions_[i].scalePow.Initialize(10);
			missions_[i].scaleEas.Initialize(-missionScale, 0.0f, 5.0f);
		}
		missions_[0].color->data_.baseColor = ColorConfig::skTurquoise[3];
		missions_[1].color->data_.baseColor = ColorConfig::skTurquoise[2];
		missions_[2].color->data_.baseColor = ColorConfig::skTurquoise[1];
	}

	// 帯
	{
		band_.band->transform_.Initialize();
		band_.band->transform_.pos_ = titlePos;
		band_.band->transform_.scale_ = Vector3(WinSize.x_, 96.0f, 0);
		band_.color->data_.baseColor = ColorConfig::skTurquoise[5];

		band_.heightPow.Initialize(20);
		band_.heightEas.Initialize(-band_.band->transform_.scale_.y_, 0.0f, 5.0f);
	}

	// ミッション
	{
		for (size_t i = 0; i < missionUIs_.size(); i++)
		{
			missionUIs_[i].trfm.Initialize();
			missionUIs_[i].trfm.pos_ = winHalfSize + Vector3(0, +128.0f + (48.0f * i), 0);
			missionUIs_[i].trfm.scale_ = Vector3(0.25f, 0.25f, 0.25f);

			missionUIs_[i].star->transform_.Initialize();
			missionUIs_[i].star->transform_.pos_ = Vector3(-540.0f, 0, 0);
			missionUIs_[i].starFrame->transform_.Initialize();
			missionUIs_[i].starFrame->transform_.pos_ = Vector3(-540.0f, 0, 0);

			missionUIs_[i].scoreTrfm.Initialize();
			missionUIs_[i].scoreTrfm.pos_ = Vector3(0.0f, 0.0f, 0.0f);
			missionUIs_[i].scoreTrfm.scale_ = Vector3(2.0f, 2.0f, 0.0f);

			missionUIs_[i].mission->transform_.Initialize();
			missionUIs_[i].mission->transform_.pos_ = Vector3(+640.0f, 0, 0);

			missionUIs_[i].animeTim.Initialize(10);
			float edgePos = 256.0f;
			missionUIs_[i].animePosEass[0].Initialize(+edgePos, 0.0f, 5.0f);
			missionUIs_[i].animePosEass[1].Initialize(0.0f, -edgePos, 5.0f);

			if (missionUIs_[i].isClear == false)
			{
				missionUIs_[i].color->data_.baseColor = { 0.75f,0.75f,0.75f,0.0f };
			}
		}
	}

	isAct_ = false;
	isPop_ = false;
	isVanish_ = false;

	remainTim_.Initialize(60);
}

void BeginingDrawer::Update()
{
	// UI
	{
		ui_.scalePow.Update(isPop_ || !isVanish_);

		Transform::Status uiStatus;
		float scaleVal = ui_.scaleEas.InOut(ui_.scalePow.Ratio());
		uiStatus.scale_ = Vector3(scaleVal, scaleVal, 0.0f);
		ui_.trfm.UpdateMatrix(uiStatus);
		ui_.num->Update();
		ui_.tutorial->Update();
	}

	// 枠
	{
		rectTrfm_.UpdateMatrix();
		
		center_.scalePow.Update(center_.isAct);
		if (center_.scalePow.IsMax())
		{
			missions_[0].isAct = true;
			missionUIs_[0].animeTim.SetActive(true);
		}

		Transform::Status centerStatus;
		float centerScale = center_.scaleEas.In(center_.scalePow.Ratio());
		centerStatus.scale_ = Vector3(centerScale, centerScale, 0);
		
		center_.rect->Update(centerStatus);
		
		for (size_t i = 0; i < missions_.size(); i++)
		{
			missions_[i].scalePow.Update(missions_[i].isAct);
			if (0.5f <= missions_[i].scalePow.Ratio() && i < missions_.size() - 1)
			{
				if (isPop_)
				{
					missions_[i + 1].isAct = true;
				}
			}

			Transform::Status missionStatus;
			float missionScale = missions_[i].scaleEas.In(missions_[i].scalePow.Ratio());
			missionStatus.scale_ = Vector3(missionScale, missionScale, 0);

			missions_[i].rect->Update(missionStatus);
		}
	}

	// 帯
	{
		band_.heightPow.Update(isPop_ || !isVanish_);
		
		Transform::Status status;
		float height = band_.heightEas.InOut(band_.heightPow.Ratio());
		status.scale_ = Vector3(0, height, 0);

		band_.band->Update(status);
	}

	// ミッション
	{
		for (size_t i = 0; i < missionUIs_.size(); i++)
		{
			missionUIs_[i].animeTim.Update();
			if (0.5f <= missionUIs_[i].animeTim.Ratio() && i < missionUIs_.size() - 1)
			{
				missionUIs_[i + 1].animeTim.SetActive(true);
			}

			if (missionUIs_[i].animeTim.IsEnd() && i == missionUIs_.size() - 1)
			{
				if (isPop_)
				{
					remainTim_.SetActive(true);
				}
			}

			float posVal = 0.0f;
			if (isPop_)		{ posVal = missionUIs_[i].animePosEass[0].Out(missionUIs_[i].animeTim.Ratio()); }
			if (isVanish_)	{ posVal = missionUIs_[i].animePosEass[1]. In(missionUIs_[i].animeTim.Ratio()); }

			missionUIs_[i].trfm.UpdateMatrix({ {posVal,0,0} });
			missionUIs_[i].star->Update();
			missionUIs_[i].starFrame->Update();
			missionUIs_[i].scoreTrfm.UpdateMatrix();
			missionUIs_[i].score->Update();
			missionUIs_[i].mission->Update();

			float alpha = 0.0f;
			if (isPop_)		{ alpha = YMath::EaseOut<float>(0.0f, 1.0f, missionUIs_[i].animeTim.Ratio(), 3.0f); }
			if (isVanish_) { alpha = YMath::EaseIn <float>(1.0f, 0.0f, missionUIs_[i].animeTim.Ratio(), 3.0f); }
			missionUIs_[i].color->data_.baseColor.a_ = alpha;
		}
	}

	remainTim_.Update();
	if (remainTim_.IsEnd())
	{
		isPop_ = false;
		isVanish_ = true;

		center_.isAct = false;

		for (size_t i = 0; i < missions_.size(); i++)
		{
			missions_[i].isAct = false;
		}

		for (size_t i = 0; i < missionUIs_.size(); i++)
		{
			missionUIs_[i].animeTim.Reset(true);
		}

		remainTim_.Reset();

		isAct_ = false;
	}
}

void BeginingDrawer::Draw()
{
	for (size_t i = 0; i < missionUIs_.size(); i++)
	{
		missionUIs_[i].starFrame->Draw("Sprite2DDefault", 2);
		if (missionUIs_[i].isClear) { missionUIs_[i].star->Draw("Sprite2DDefault", 2); }
		missionUIs_[i].score->Draw("Sprite2DDefault", 2);
		missionUIs_[i].mission->Draw("Sprite2DDefault", 2);
	}

	band_.band->Draw("Sprite2DDefault", 2);
	
	for (size_t i = 0; i < missions_.size(); i++)
	{
		size_t idx = missions_.size() - 1 - i;
		missions_[idx].rect->Draw("Sprite2DDefault", 2);
	}
	center_.rect->Draw("Sprite2DDefault", 2);

	if (ui_.isTutorial) { ui_.tutorial->Draw("Sprite2DDefault", 2); }
	else { ui_.num->Draw("Sprite2DDefault", 2); }
}

void BeginingDrawer::PlayAnimation()
{
	Reset();
	isPop_ = true;
	center_.isAct = true;

	isAct_ = true;
}

bool BeginingDrawer::IsAct()
{
	return isAct_;

	//bool result = false;

	//for (size_t i = 0; i < missions_.size(); i++)
	//{
	//	result = result || missions_[i].isAct;
	//}

	//result = result || isPop_;
	//result = result || isVanish_;

	//return result;
}
