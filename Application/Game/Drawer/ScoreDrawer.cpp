#include "ScoreDrawer.h"
#include "Lerp.h"

using YGame::ScoreDrawer;
using YGame::Sprite2D;

namespace
{
	//Sprite2D* pSpr = nullptr;
}

ScoreDrawer* ScoreDrawer::Create(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority)
{
	ScoreDrawer* newDrawer = new ScoreDrawer();

	newDrawer->Initialize(pParent, shaderTag, drawPriority);

	return newDrawer;
}

void ScoreDrawer::LoadResource()
{

}

void ScoreDrawer::Initialize(YMath::Matrix4* pParent, const std::string& shaderTag, const size_t drawPriority)
{
	currentScore_ = elderScore_ = scoreForAnimation_ = 0;

	transform_.Initialize();
	transform_.parent_ = pParent;

	uiNum_.reset(UINumber::Create2D(0, digitAnimeStatuses_.size(), 80.0f, false, false, &transform_.m_));
	uiColor_.reset(ConstBufferObject<CBColor>::Create());
	uiNum_->InsertConstBuffer(uiColor_.get());

	uiBackNum_.reset(UINumber::Create2D(0, digitAnimeStatuses_.size(), 80.0f, true, false, &transform_.m_));
	uiBackColor_.reset(ConstBufferObject<CBColor>::Create());
	uiBackNum_->InsertConstBuffer(uiBackColor_.get());
	uiBackColor_->data_.baseColor = { 0.5f,0.5f,0.5f,0.5f };

	shaderTag_ = shaderTag;
	drawPriority_ = drawPriority;
	
	reelTim_.Initialize(20);
}

void ScoreDrawer::Update()
{
	transform_.UpdateMatrix();

	reelTim_.Update();

	// スコアをリール
	scoreForAnimation_ = static_cast<uint32_t>
		(YMath::Lerp(static_cast<float>(elderScore_), static_cast<float>(currentScore_), reelTim_.Ratio()));
	uiNum_->SetNumber(scoreForAnimation_);


	for (size_t i = 0; i < digitAnimeStatuses_.size(); i++)
	{
		digitAnimeStatuses_[i] = {};

		uiNum_->SetAnimationStatus(i, digitAnimeStatuses_[i]);
	}
	uiNum_->Update();
	uiBackNum_->Update();

	if (reelTim_.IsEnd())
	{
		elderScore_ = currentScore_;
	}
}

void ScoreDrawer::Draw()
{
	uiBackNum_->Draw(shaderTag_, drawPriority_);
	uiNum_->Draw(shaderTag_, drawPriority_);
}

void ScoreDrawer::ChangeScoreAnimation(const uint32_t score)
{
	if (currentScore_ != score)
	{
		reelTim_.Reset(true);
	}

	currentScore_ = score;
}
