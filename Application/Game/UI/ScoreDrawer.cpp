#include "ScoreDrawer.h"
#include "DrawObjectForSprite3D.h"
#include "Lerp.h"

using YGame::ScoreDrawer;
using YGame::Sprite3D;
using YMath::Vector3;

namespace
{
	Sprite3D* pLogoSpr = nullptr;

	const Vector3 kGaugePos = { 0.0f, -0.6f, 0.0f };
	const Vector3 kGaugeScale = Vector3(30.0f, 1.0f, 0.0f) / 6.0f;

	const Vector3 kMissionPos = { 0.0f, -0.6f, 0.0f };
	const Vector3 kMissionScale = { 0.2f, 0.2f, 0.0f };

	const Vector3 kLogoPos = { -2.2f, +0.6f, 0.0f };
	const Vector3 kLogoScale = { 1.2f, 0.3f, 0.0f };

	const uint32_t kReelFrame = 20;

	const std::string kShaderTag = "Sprite3DUI";
}

void ScoreDrawer::LoadResource()
{
	pLogoSpr = Sprite3D::Create({ {"Texture0", Texture::Load("UI/play/score.png")}});
}

ScoreDrawer* ScoreDrawer::Create(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	ScoreDrawer* newDrawer = new ScoreDrawer();

	newDrawer->Initialize(pParent, pVP);

	return newDrawer;
}

void ScoreDrawer::Initialize(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	currentScore_ = elderScore_ = scoreForAnimation_ = 0;

	transform_.Initialize();
	transform_.parent_ = pParent;

	// 数
	if (uiNum_ == nullptr)
	{
		uiNum_.reset(UINumber::Create3D(
			0, digitAnimeStatuses_.size(), 0.8f, true, false,
			&transform_.m, false, false, pVP));
	}
	for (size_t i = 0; i < uiColors_.size(); i++)
	{
		if (uiColors_[i] == nullptr)
		{
			uiColors_[i].reset(ConstBufferObject<CBColor>::Create());
			uiNum_->InsertConstBuffer(i, uiColors_[i].get());
		}
	}

	// ロゴ
	if (logo_ == nullptr)
	{
		logo_.reset(DrawObjectForSprite3D::Create(
			{ kLogoPos, {}, kLogoScale }, false, false, pVP, pLogoSpr));
		logo_->transform_.parent_ = &transform_.m;
	}

	reelTim_.Initialize(kReelFrame);
}

void ScoreDrawer::Update()
{
	transform_.UpdateMatrix();

	reelTim_.Update();

	// リールする
	scoreForAnimation_ = static_cast<uint32_t>
		(YMath::Lerp(static_cast<float>(elderScore_), static_cast<float>(currentScore_), reelTim_.Ratio()));
	uiNum_->SetNumber(scoreForAnimation_);


	for (size_t i = 0; i < digitAnimeStatuses_.size(); i++)
	{
		digitAnimeStatuses_[i] = {};

		uiNum_->SetAnimationStatus(i, digitAnimeStatuses_[i]);
	}
	uiNum_->Update();

	logo_->Update();

	if (reelTim_.IsEnd())
	{
		elderScore_ = currentScore_;
	}

	UpdateDigitColor();
}

void ScoreDrawer::UpdateDigitColor()
{
	uint32_t num = scoreForAnimation_;

	for (size_t i = 0; i < uiColors_.size(); i++)
	{
		if (num <= 0 && 0 < i)
		{
			uiColors_[i]->data_.baseColor = { 0.5f,0.5f,0.5f,0.5f };
		}
		else
		{
			uiColors_[i]->data_.baseColor = { 1.0f,1.0f,1.0f,1.0f };
		}
		
		num /= 10;
	}
}

void ScoreDrawer::Draw()
{
	logo_->Draw(kShaderTag, 0);
	uiNum_->Draw(kShaderTag, 0);
}

void ScoreDrawer::ChangeScoreAnimation(const uint32_t score)
{
	if (currentScore_ != score)
	{
		reelTim_.Reset(true);
	}

	currentScore_ = score;
}
