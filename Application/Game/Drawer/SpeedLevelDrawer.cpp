#include "SpeedLevelDrawer.h"
#include "Lerp.h"

using YGame::SpeedLevelDrawer;
using YGame::Sprite2D;
using YMath::Vector3;

namespace
{
	Sprite2D* pSpr = nullptr;
}

SpeedLevelDrawer* SpeedLevelDrawer::Create(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority)
{
	SpeedLevelDrawer* newDrawer = new SpeedLevelDrawer();

	newDrawer->Initialize(pParent, shaderTag, drawPriority);

	return newDrawer;
}

void SpeedLevelDrawer::LoadResource()
{
	pSpr = Sprite2D::Create({ {"Texture0", Texture::Load("play/speedUI.png")} });
}

void SpeedLevelDrawer::Initialize(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority)
{
	currentSpeed_ = elderSpeed_ = coinForAnimation_ = 0;

	transform_.Initialize();
	transform_.parent_ = pParent;

	numTrfm_.Initialize();
	numTrfm_.parent_ = &transform_.m_;
	numTrfm_.pos_ = Vector3(+25.0f, 0.0f, 0.0f);
	numTrfm_.scale_ = Vector3(0.5f, 0.5f, 0.0f);

	uiNum_.reset(UINumber::Create2D(0, digitAnimeStatuses_.size(), 80.0f, true, false, &numTrfm_.m_));
	for (size_t i = 0; i < uiColors_.size(); i++)
	{
		uiColors_[i].reset(ConstBufferObject<CBColor>::Create());
		uiNum_->InsertConstBuffer(i, uiColors_[i].get());
	}

	uiSpeed_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pSpr));
	uiSpeed_->transform_.pos_ = Vector3(-25.0f, 0.0f, 0.0f);
	uiSpeed_->transform_.scale_ = Vector3(0.75f, 0.75f, 0.0f);
	uiSpeed_->transform_.parent_ = &transform_.m_;

	shaderTag_ = shaderTag;
	drawPriority_ = drawPriority;

	reelTim_.Initialize(20);
}

void SpeedLevelDrawer::Update()
{
	transform_.UpdateMatrix();

	reelTim_.Update();

	// リールする
	coinForAnimation_ = static_cast<uint32_t>
		(YMath::Lerp(static_cast<float>(elderSpeed_), static_cast<float>(currentSpeed_), reelTim_.Ratio()));
	uiNum_->SetNumber(coinForAnimation_);

	numTrfm_.UpdateMatrix();
	for (size_t i = 0; i < digitAnimeStatuses_.size(); i++)
	{
		digitAnimeStatuses_[i] = {};

		uiNum_->SetAnimationStatus(i, digitAnimeStatuses_[i]);
	}
	uiNum_->Update();

	uiSpeed_->Update();

	if (reelTim_.IsEnd())
	{
		elderSpeed_ = currentSpeed_;
	}

	UpdateDigitColor();
}

void SpeedLevelDrawer::Draw()
{
	uiSpeed_->Draw(shaderTag_, drawPriority_);
	uiNum_->Draw(shaderTag_, drawPriority_);
}

void SpeedLevelDrawer::ChangeSpeedAnimation(const uint32_t speed)
{
	if (currentSpeed_ != speed)
	{
		reelTim_.Reset(true);
	}

	currentSpeed_ = speed;
}

void SpeedLevelDrawer::UpdateDigitColor()
{
	uint32_t num = coinForAnimation_;

	for (size_t i = 0; i < uiColors_.size(); i++)
	{
		if (num <= 0 && 0 < i)
		{
			uiColors_[i]->data_.baseColor = {};
		}
		else
		{
			uiColors_[i]->data_.baseColor = { 1.0f,1.0f,1.0f,1.0f };
		}

		num /= 10;
	}
}
