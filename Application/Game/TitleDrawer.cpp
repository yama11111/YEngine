#include "TitleDrawer.h"
#include "CharacterConfig.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "Def.h"

#include "Keys.h"
#include "Pad.h"

using YGame::TitleDrawer;
using YMath::Vector3;

YGame::Sprite2D* TitleDrawer::spLogoSpr_ = nullptr;
YGame::Sprite2D* TitleDrawer::spLineSpr_ = nullptr;
YGame::Sprite2D* TitleDrawer::spNameSpr_ = nullptr;
YGame::Sprite2D* TitleDrawer::spStartSpr_ = nullptr;
YGame::Sprite2D* TitleDrawer::spButtonSpr_ = nullptr;
YGame::MapChipManager* TitleDrawer::spMapChipManager_ = nullptr;

void TitleDrawer::StaticInitialize()
{
	spLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_logo.png")} });
	spLineSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_line.png")} });
	spNameSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_name.png")} });

	spStartSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("title/title_start.png")} });
	
	spButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });
	
	spMapChipManager_ = MapChipManager::GetInstance();
}

void TitleDrawer::Initialize()
{
	// ウィンドウサイズ を 3次元ベクトルにしておく
	Vector3 win = YMath::ConvertToVector3(WinSize);

	Vector3 logoPos = (win / 2.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, spLogoSpr_));
	lineObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, spLineSpr_));
	nameObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, spNameSpr_));


	Vector3 startPos = (win / 2.0f) + Vector3(480.0f, 240.0f, 0.0f);
	startObj_.reset(DrawObjectForSprite2D::Create({ startPos, {}, {0.75f,0.75f,0.0f} }, spStartSpr_));

	startColor_.reset(ConstBufferObject<CBColor>::Create());
	startObj_->InsertConstBuffer(startColor_.get());

	Vector3 buttonPos = startPos + Vector3(0.0f, 64.0f, 0.0f);
	DrawObjectForSprite2D* newStartButton = DrawObjectForSprite2D::Create({ buttonPos, {}, {1.0f,1.0f,0.0f} }, spButtonSpr_);
	startButton_.reset(UIButton::Create(newStartButton));

	letterBox_.reset(new UILetterBox());
	letterBox_->Initialize(WinSize, 96.0f, 96.0f);


	pLevel_ = Level::LoadJson("levelData.json");
	
	spMapChipManager_->Initialize(0, Vector3(-28.0f, +17.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

	horse_.Initialize();
	horseDra_.reset(HorseDrawer::Create(&horse_, 0));
	//horseDra_->PlayAnimation(static_cast<uint16_t>(HorseDrawer::AnimationType::eMove), 10, true);

	player_.Initialize();
	player_.pos_ = YGame::PetConfig::kRiddenHeight;
	player_.parent_ = &horse_.m_;
	playerDra_.reset(PlayerDrawer::Create(&player_, 0));


	openingTims_[0].Initialize(60);
	openingTims_[1].Initialize(60);
	
	titlePosEass_[0].Initialize({0.0f,-400.0f, 0.0f}, {}, 3.0f);
	titlePosEass_[1].Initialize({}, { -450, -250.0f, 0.0f }, 3.0f);
	
	titleScaleEass_[0].Initialize(-1.0f, 0.0f, 3.0f);
	titleScaleEass_[1].Initialize(0.0f, -0.6f, 3.0f);
	
	slimeActor_.Initialize(70, { {}, Vector3(+0.15f, +0.15f, 0.0f), {} }, 3.0f);
}

void TitleDrawer::Update()
{
	{
		size_t animeIndex = 0;
		Transform::Status anime;

		for (size_t i = 0; i < openingTims_.size(); i++)
		{
			openingTims_[i].Update();
		}
		slimeActor_.Update();

		if (openingTims_[0].IsEnd() && slimeActor_.IsAct() == false)
		{
			openingTims_[1].SetActive(true);
		}

		if (openingTims_[1].IsAct())
		{
			animeIndex = 1;
		}

		anime.pos_ += titlePosEass_[animeIndex].InOut(openingTims_[animeIndex].Ratio());

		float scale = titleScaleEass_[animeIndex].InOut(openingTims_[animeIndex].Ratio());
		anime.scale_ += { scale, scale, scale };
		anime.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eIn);

		logoObj_->Update(anime);
		lineObj_->Update(anime);
		nameObj_->Update(anime);
	}

	{
		startObj_->Update();

		startButton_->Update(
			YInput::Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
			YInput::Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A));

		letterBox_->Update();
	}

	{
		horse_.rota_ = YMath::AdjustAngle({ +1.0f, 0.0f, 0.0f });
		horse_.UpdateMatrix();

		horseDra_->Update();

		player_.UpdateMatrix();
		playerDra_->Update();

		spMapChipManager_->Update();

		pLevel_->Update(); 
	}
}

void TitleDrawer::Draw()
{
	pLevel_->Draw();
	spMapChipManager_->Draw();
	horseDra_->Draw();
	playerDra_->Draw();

	logoObj_->Draw("Sprite2DDefault", 1);
	lineObj_->Draw("Sprite2DDefault", 1);
	nameObj_->Draw("Sprite2DDefault", 1);
	startObj_->Draw("Sprite2DDefault", 1);

	startButton_->Draw("Sprite2DDefault", 1);

	letterBox_->Draw("Sprite2DDefault", 2);
}

void TitleDrawer::StartAnimation()
{
	startColor_->data_.baseColor = { 1.0f,1.0f,0.0f,1.0f };

	//horseDra_->AbortAnimation(static_cast<uint16_t>(HorseDrawer::AnimationType::eMove));
	//horseDra_->PlayAnimation(static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding), 8);
}

void TitleDrawer::OpeningAnimation()
{
	openingTims_[0].Reset(true);
	openingTims_[1].Reset(false);
	slimeActor_.Wobble();
}
