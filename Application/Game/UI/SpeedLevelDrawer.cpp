#include "SpeedLevelDrawer.h"
#include "DrawObjectForSprite2D.h"
#include "DrawObjectForSprite3D.h"
#include "Lerp.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "Def.h"

using YGame::SpeedLevelDrawer;
using YGame::Sprite3D;
using YGame::Sprite2D;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Sprite3D* pCounterSpr = nullptr;
	Sprite2D* pLevelUpSpr = nullptr;

	const Vector3 kLevelPos = { +56.0f,-46.0f,0.0f };
	const Vector3 kLevelScale = { 50.0f,50.0f,0.0f };
	const Vector3 kLevelUIPos = { +80.0f,-32.0f,0.0f };
	const Vector3 kLevelUIScale = { 32.0f,48.0f,0.0f };
	
	const float kMoveValue = 28.0f;
	const float kMoveExponent = 3.0f;
	const uint32_t kMoveFrame = 16;
	
	const Vector4 kLevelColor = YMath::GetColor(255, 133, 0, 255);
	
	const Vector3 kLevelUpPos = YMath::ConvertToVector3(WinSize) / 2.0f;;
	const uint32_t kLevelUpPowerFrame = 10;
	const uint32_t kLevelUpRemainFrame = 60;
	const float kLevelUpMaxScale = 1.0f;
	const float kLevelUpMaxAlpha = 0.8f;
	const float kLevelUpExponent = 2.0f;

	const std::string kShaderTag = "Sprite3DUI";
}

void SpeedLevelDrawer::LoadResource()
{
	pCounterSpr = Sprite3D::Create({ {"Texture0", Texture::Load("UI/play/speed_counter.png")} });
	pLevelUpSpr = Sprite2D::Create({ {"Texture0", Texture::Load("UI/play/fever.png")} });
}

SpeedLevelDrawer* SpeedLevelDrawer::Create(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	SpeedLevelDrawer* newDrawer = new SpeedLevelDrawer();

	newDrawer->Initialize(pParent, pVP);

	return newDrawer;
}

void SpeedLevelDrawer::Initialize(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	transform_.Initialize();
	transform_.parent_ = pParent;

	levelTrfm_.Initialize();
	levelTrfm_.parent_ = &transform_.m;
	levelTrfm_.pos_ = kLevelPos;
	levelTrfm_.scale_ = kLevelScale;

	if (level_ == nullptr)
	{
		level_.reset(UIDigit::Create3D(0, &levelTrfm_.m, false, false, pVP));
	}
	if (levelColor_ == nullptr)
	{
		levelColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	levelColor_->data_.baseColor = kLevelColor;
	levelColor_->data_.texColorRate = {1.0f,1.0f,1.0f,1.0f};
	level_->InsertConstBuffer(levelColor_.get());

	for (size_t i = 0; i < levelUIs_.size(); i++)
	{
		if (levelUIs_[i].obj_ == nullptr)
		{
			levelUIs_[i].obj_.reset(
				DrawObjectForSprite3D::Create(
					{ kLevelUIPos, {}, kLevelUIScale }, false, false, pVP, pCounterSpr));
		}
		levelUIs_[i].obj_->transform_.parent_ = &transform_.m;
		levelUIs_[i].animeStatus_ = {};

		levelUIs_[i].moveEas_.Initialize(0.0f, kMoveValue * i, kMoveExponent);
		levelUIs_[i].movePower_.Initialize(kMoveFrame);
	}

	speedLevel_ = 1;

	// レベルアップ
	{
		isLevelUpAnimation_ = false;

		if (up_ == nullptr)
		{
			up_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pLevelUpSpr));
		}
		up_->transform_.Initialize();
		up_->transform_.pos_ = kLevelUpPos;

		if (upColor_ == nullptr)
		{
			upColor_.reset(ConstBufferObject<CBColor>::Create());
		}
		up_->InsertConstBuffer(upColor_.get());
		upPow_.Initialize(kLevelUpPowerFrame);
		upRemainTim_.Initialize(kLevelUpRemainFrame);
	}
}

void SpeedLevelDrawer::Update()
{
	transform_.UpdateMatrix();

	levelTrfm_.UpdateMatrix();
	level_->Update();
	
	// レベル分表示(アニメーション)
	for (size_t i = 0; i < levelUIs_.size(); i++)
	{
		levelUIs_[i].animeStatus_ = {};

		levelUIs_[i].movePower_.Update(i < speedLevel_);
		levelUIs_[i].animeStatus_.pos_.x = levelUIs_[i].moveEas_.Out(levelUIs_[i].movePower_.Ratio());

		levelUIs_[i].obj_->Update(levelUIs_[i].animeStatus_);
	}

	// レベルアップアニメーション
	{
		upPow_.Update(isLevelUpAnimation_);

		upRemainTim_.Update();
		if (upRemainTim_.IsEnd())
		{
			upRemainTim_.Reset();
			isLevelUpAnimation_ = false;
		}

		float upScale = YMath::EaseInOut(-kLevelUpMaxScale, 0.0f, upPow_.Ratio(), kLevelUpExponent);
		up_->Update({ {},{},{upScale, upScale, 0.0f} });

		float upAlpha = YMath::EaseInOut(0.0f, kLevelUpMaxAlpha, upPow_.Ratio(), kLevelUpExponent);
		upColor_->data_.baseColor.w = upAlpha; 
	}
}

void SpeedLevelDrawer::Draw()
{
	for (size_t i = 0; i < levelUIs_.size(); i++)
	{
		levelUIs_[i].obj_->Draw(kShaderTag, 0);
	}

	up_->Draw("Sprite2DDefault", 2);
}

void SpeedLevelDrawer::ChangeSpeedAnimation(const uint32_t speed)
{
	// 上昇時アニメーション開始
	if (speedLevel_ < speed)
	{
		isLevelUpAnimation_ = true;
		upPow_.Reset();
		upRemainTim_.Reset(true);
	}

	speedLevel_ = speed;
	level_->SetNumber(speed);
}
