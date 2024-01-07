#include "TitleDrawer.h"
#include "CharacterConfig.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "ColorConfig.h"
#include "Lerp.h"
#include "Def.h"

#include "Keys.h"
#include "Pad.h"

using YGame::TitleDrawer;
using YMath::Vector3;

std::array<YGame::Sprite2D*, 6> TitleDrawer::spTitleCharaSprs_ = {};
YGame::Sprite2D* TitleDrawer::spStartSpr_ = nullptr;
YGame::Sprite2D* TitleDrawer::spButtonSpr_ = nullptr;
YGame::Sprite2D* TitleDrawer::spCircleSpr_ = nullptr;
YGame::Sprite2D* TitleDrawer::spWhiteSpr_ = nullptr;

void TitleDrawer::LoadResource()
{
	spTitleCharaSprs_[0] = Sprite2D::Create({ { "Texture0", Texture::Load("title/logo/B.png")} });
	spTitleCharaSprs_[1] = Sprite2D::Create({ { "Texture0", Texture::Load("title/logo/E.png")} });
	spTitleCharaSprs_[2] = Sprite2D::Create({ { "Texture0", Texture::Load("title/logo/D.png")} });
	spTitleCharaSprs_[3] = Sprite2D::Create({ { "Texture0", Texture::Load("title/logo/A.png")} });
	spTitleCharaSprs_[4] = Sprite2D::Create({ { "Texture0", Texture::Load("title/logo/S.png")} });
	spTitleCharaSprs_[5] = Sprite2D::Create({ { "Texture0", Texture::Load("title/logo/H.png")} });
	
	spStartSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });

	spButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("white1x1.png")} });

	spCircleSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/circle.png")} });
	
	spWhiteSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("white1x1.png")} });
	spWhiteSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("white1x1.png")} });
}

void TitleDrawer::Initialize()
{
	for (size_t i = 0; i < titleLogo_.size(); i++)
	{
		if (titleLogo_[i].chara == nullptr)
		{
			titleLogo_[i].chara.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spTitleCharaSprs_[i]));
		}
		if (titleLogo_[i].color == nullptr)
		{
			titleLogo_[i].color.reset(ConstBufferObject<CBColor>::Create());
		}
		titleLogo_[i].chara->InsertConstBuffer(titleLogo_[i].color.get());
	}

	for (size_t i = 0; i < bands_.size(); i++)
	{
		if (bands_[i].band == nullptr)
		{
			bands_[i].band.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spWhiteSpr_));
		}
		if (bands_[i].color == nullptr)
		{
			bands_[i].color.reset(ConstBufferObject<CBColor>::Create());
		}
		bands_[i].band->InsertConstBuffer(bands_[i].color.get());
	}

	if (start_ == nullptr)
	{
		start_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spStartSpr_));
	}
	if (startColor_ == nullptr)
	{
		startColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	start_->InsertConstBuffer(startColor_.get());
	
	startButtonTrfm_.Initialize();
	if (startButton_ == nullptr)
	{
		DrawObjectForSprite2D* obj = DrawObjectForSprite2D::Create(Transform::Status::Default(), spButtonSpr_);
		obj->SetParent(&startButtonTrfm_.m_);
		startButton_.reset(UIButton::Create(obj));
	}

	if (circle_ == nullptr)
	{
		circle_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spCircleSpr_));
	}
	if (circleColor_ == nullptr)
	{
		circleColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	circle_->InsertConstBuffer(circleColor_.get());

	if (curten_ == nullptr)
	{
		curten_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spWhiteSpr_));
	}
	if (curtenColor_ == nullptr)
	{
		curtenColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	curten_->InsertConstBuffer(curtenColor_.get());
	
	skydomeTrfm_.Initialize();
	if (skydomeDra_ == nullptr)
	{
		skydomeDra_ = std::move(SkydomeDrawer::Create(&skydomeTrfm_, 2));
	}	

	Reset();
}

void TitleDrawer::Reset()
{
	Vector3 pos = Vector3(WinSize.x_ / 2.0f, 256.0f, 0.0f);

	for (size_t i = 0; i < titleLogo_.size(); i++)
	{
		titleLogo_[i].chara->transform_.Initialize();
		titleLogo_[i].chara->transform_.pos_ = pos;
		float ratio = static_cast<float>(i) / static_cast<float>(titleLogo_.size() - 1);
		titleLogo_[i].chara->transform_.pos_.x_ += YMath::Lerp(-320.0f, +320.0f, ratio);
		
		titleLogo_[i].color->data_.baseColor.a_ = 0.0f;

		titleLogo_[i].animeTim.Initialize(40);
		float startVal = -96.0f;
		if (i % 2 == 0) { startVal *= -1; }
		titleLogo_[i].posEas.Initialize(startVal, 0.0f, 3.0f);
	}
	
	bands_[0].color->data_.baseColor = ColorConfig::skTurquoise[1];
	bands_[1].color->data_.baseColor = ColorConfig::skTurquoise[2];
	for (size_t i = 0; i < bands_.size(); i++)
	{
		bands_[i].band->transform_.Initialize();
		bands_[i].band->transform_.pos_ = pos;
		bands_[i].band->transform_.scale_ = {};
		
		bands_[i].color->data_.baseColor.a_ = 1.0f;
		
		bands_[i].scaleTim.Initialize(30);
		bands_[i].scaleEas.Initialize({}, { WinSize.x_, 128.0f - (16.0f * i), 0.0f }, 3.0f);
	}

	start_->transform_.Initialize();
	start_->transform_.pos_ = { WinSize.x_ / 2.0f, 512.0f, 0.0f };

	startButtonTrfm_.Initialize();
	startButtonTrfm_.pos_ = { WinSize.x_ / 2.0f, 640.0f, 0.0f };

	circle_->transform_.Initialize();
	circle_->transform_.pos_ = Vector3(WinSize.x_, WinSize.y_, 0.0f) / 2.0f;
	circle_->transform_.scale_ = {};
	circleColor_->data_.baseColor = ColorConfig::skTurquoise[1];
	
	circleScaleTim_.Initialize(10);
	circleScaleEas_.Initialize(0.0f, 16.0f, 2.0f);

	curten_->transform_.Initialize();
	curten_->transform_.pos_ = Vector3(WinSize.x_, WinSize.y_, 0.0f) / 2.0f;
	curten_->transform_.scale_ = Vector3(WinSize.x_, WinSize.y_, 0.0f);
	curtenColor_->data_.baseColor = ColorConfig::skTurquoise[0];

	curtenAlphaTim_.Initialize(30);
	
	skydomeTrfm_.Initialize();
	skydomeTrfm_.scale_ = { 100.0f,100.0f,100.0f };
}

void TitleDrawer::UpdateAnimeFlag()
{
	if(circleScaleTim_.IsEnd())
	{
		bands_[0].scaleTim.SetActive(true);
	}

	if (0.4f <= bands_[0].scaleTim.Ratio())
	{
		bands_[1].scaleTim.SetActive(true);
		titleLogo_[0].animeTim.SetActive(true);
	}

	for (size_t i = 0; i < titleLogo_.size(); i++)
	{
		if (0.2f <= titleLogo_[i].animeTim.Ratio())
		{
			if (titleLogo_.size() - 1 <= i)
			{
				curtenAlphaTim_.SetActive(true);
				break;
			}
			titleLogo_[i + 1].animeTim.SetActive(true);
		}
	}
}

void TitleDrawer::Update()
{
	UpdateAnimeFlag();

	for (size_t i = 0; i < titleLogo_.size(); i++)
	{
		titleLogo_[i].animeTim.Update();
		float posY = titleLogo_[i].posEas.InOut(titleLogo_[i].animeTim.Ratio());
		titleLogo_[i].chara->Update({ {0.0f, posY, 0.0f} });

		float alpha = YMath::EaseIn<float>(0.0f, 1.0f, titleLogo_[i].animeTim.Ratio(), 3.0f);
		titleLogo_[i].color->data_.baseColor.a_ = alpha;
	}

	for (size_t i = 0; i < bands_.size(); i++)
	{
		bands_[i].scaleTim.Update();
		YMath::Vector3 scaleVal = bands_[i].scaleEas.Out(bands_[i].scaleTim.Ratio());
		bands_[i].band->Update({ {},{},scaleVal });
	}

	start_->Update();
	startButtonTrfm_.UpdateMatrix();
	startButton_->Update(
		YInput::Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		YInput::Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A));

	circleScaleTim_.Update();
	float circleScale = circleScaleEas_.In(circleScaleTim_.Ratio());
	circle_->Update({ {},{},{circleScale, circleScale, 0.0f} });
	
	curten_->Update();
	curtenAlphaTim_.Update();
	float curtenAlpha = YMath::EaseIn<float>(1.0f, 0.0f, curtenAlphaTim_.Ratio(), 3.0f);
	curtenColor_->data_.baseColor.a_ = curtenAlpha;

	skydomeTrfm_.UpdateMatrix();
	skydomeDra_->Update();
}

void TitleDrawer::Draw()
{
	skydomeDra_->Draw();
	
	start_->Draw("Sprite2DDefault", 3);
	startButton_->Draw("Sprite2DDefault", 3);

	curten_->Draw("Sprite2DDefault", 2);
	
	circle_->Draw("Sprite2DDefault", 2);

	for (size_t i = 0; i < bands_.size(); i++)
	{
		bands_[i].band->Draw("Sprite2DDefault", 1);
	}
	
	for (size_t i = 0; i < titleLogo_.size(); i++)
	{
		titleLogo_[i].chara->Draw("Sprite2DDefault", 1);
	}
}

void TitleDrawer::StartAnimation()
{
	startColor_->data_.baseColor = { 1.0f,1.0f,0.0f,1.0f };
}

void TitleDrawer::OpeningAnimation()
{
	Reset();
	circleScaleTim_.SetActive(true);
}
