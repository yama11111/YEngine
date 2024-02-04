#include "CoinCountDrawer.h"
#include "Lerp.h"

using YGame::CoinCountDrawer;
using YGame::Sprite2D;
using YMath::Vector3;

namespace
{
	Sprite2D* pSpr = nullptr;
}

CoinCountDrawer* CoinCountDrawer::Create(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority)
{
	CoinCountDrawer* newDrawer = new CoinCountDrawer();

	newDrawer->Initialize(pParent, shaderTag, drawPriority);

	return newDrawer;
}

void CoinCountDrawer::LoadResource()
{
	pSpr = Sprite2D::Create({ {"Texture0", Texture::Load("white1x1.png")} });
}

void CoinCountDrawer::Initialize(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority)
{
	currentCoin_ = elderCoin_ = coinForAnimation_ = 0;

	transform_.Initialize();
	transform_.parent_ = pParent;

	numTrfm_.Initialize();
	numTrfm_.parent_ = &transform_.m;
	numTrfm_.pos_ = Vector3(+45.0f, 0.0f, 0.0f);
	numTrfm_.scale_ = Vector3(0.5f, 0.5f, 0.0f);

	uiNum_.reset(UINumber::Create2D(0, digitAnimeStatuses_.size(), 80.0f, true, false, &numTrfm_.m));
	for (size_t i = 0; i < uiColors_.size(); i++)
	{
		uiColors_[i].reset(ConstBufferObject<CBColor>::Create());
		uiNum_->InsertConstBuffer(i, uiColors_[i].get());
	}

	uiCoin_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pSpr));
	uiCoin_->transform_.pos_ = Vector3(-45.0f, 0.0f, 0.0f);
	uiCoin_->transform_.scale_ = Vector3(0.5f, 0.5f, 0.0f);
	uiCoin_->transform_.parent_ = &transform_.m;

	shaderTag_ = shaderTag;
	drawPriority_ = drawPriority;

	reelTim_.Initialize(20);
}

void CoinCountDrawer::Update()
{
	transform_.UpdateMatrix();

	reelTim_.Update();

	// リールする
	coinForAnimation_ = static_cast<uint32_t>
		(YMath::Lerp(static_cast<float>(elderCoin_), static_cast<float>(currentCoin_), reelTim_.Ratio()));
	uiNum_->SetNumber(coinForAnimation_);

	numTrfm_.UpdateMatrix();
	for (size_t i = 0; i < digitAnimeStatuses_.size(); i++)
	{
		digitAnimeStatuses_[i] = {};

		uiNum_->SetAnimationStatus(i, digitAnimeStatuses_[i]);
	}
	uiNum_->Update();

	uiCoin_->Update();

	if (reelTim_.IsEnd())
	{
		elderCoin_ = currentCoin_;
	}

	UpdateDigitColor();
}

void CoinCountDrawer::Draw()
{
	uiCoin_->Draw(shaderTag_, drawPriority_);
	uiNum_->Draw(shaderTag_, drawPriority_);
}

void CoinCountDrawer::ChangeCoinAnimation(const uint32_t coin)
{
	if (currentCoin_ != coin)
	{
		reelTim_.Reset(true);
	}

	currentCoin_ = coin;
}

void CoinCountDrawer::UpdateDigitColor()
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
