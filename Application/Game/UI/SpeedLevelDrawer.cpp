#include "SpeedLevelDrawer.h"
#include "DrawObjectForSprite3D.h"
#include "Lerp.h"
#include "MathUtil.h"

using YGame::SpeedLevelDrawer;
using YGame::Sprite3D;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Sprite3D* pSpr = nullptr;

	const Vector3 kLevelPos = { +56.0f,-46.0f,0.0f };
	const Vector3 kLevelScale = { 50.0f,50.0f,0.0f };
	const Vector3 kLevelUIPos = { +80.0f,-32.0f,0.0f };
	const Vector3 kLevelUIScale = { 32.0f,48.0f,0.0f };
	
	const float kMoveValue = 28.0f;
	const float kMoveExponent = 3.0f;
	const uint32_t kMoveFrame = 16;
	
	const Vector4 kLevelColor = YMath::GetColor(255, 133, 0, 255);

	const std::string kShaderTag = "Sprite3DUI";
}

void SpeedLevelDrawer::LoadResource()
{
	pSpr = Sprite3D::Create({ {"Texture0", Texture::Load("UI/play/speed_counter.png")} });
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
	levelTrfm_.parent_ = &transform_.m_;
	levelTrfm_.pos_ = kLevelPos;
	levelTrfm_.scale_ = kLevelScale;

	if (level_ == nullptr)
	{
		level_.reset(UIDigit::Create3D(0, &levelTrfm_.m_, false, false, pVP));
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
					{ kLevelUIPos, {}, kLevelUIScale }, false, false, pVP, pSpr));
		}
		levelUIs_[i].obj_->transform_.parent_ = &transform_.m_;
		levelUIs_[i].animeStatus_ = {};

		levelUIs_[i].moveEas_.Initialize(0.0f, kMoveValue * i, kMoveExponent);
		levelUIs_[i].movePower_.Initialize(kMoveFrame);
	}

	speedLevel_ = 0;
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
		levelUIs_[i].animeStatus_.pos_.x_ = levelUIs_[i].moveEas_.Out(levelUIs_[i].movePower_.Ratio());

		levelUIs_[i].obj_->Update(levelUIs_[i].animeStatus_);
	}
}

void SpeedLevelDrawer::Draw()
{
	for (size_t i = 0; i < levelUIs_.size(); i++)
	{
		levelUIs_[i].obj_->Draw(kShaderTag, 0);
	}
}

void SpeedLevelDrawer::ChangeSpeedAnimation(const uint32_t speed)
{
	speedLevel_ = speed;
	level_->SetNumber(speed);
}
