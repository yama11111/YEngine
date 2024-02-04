#include "StatusDrawer.h"
#include "DrawObjectForSprite3D.h"

using YGame::StatusDrawer;
using YGame::Sprite3D;
using YMath::Vector3;

namespace
{
	Sprite3D* pSpr = nullptr;
	
	const Vector3 kStatusPos = {};
	const Vector3 kStatusScale = { 480.0f,128.0f,0.0f };

	const std::string kShaderTag = "Sprite3DUI";
}

void StatusDrawer::LoadResource()
{
	pSpr = Sprite3D::Create({ {"Texture0", Texture::Load("UI/play/status_UI.png")} });
}

StatusDrawer* StatusDrawer::Create(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	StatusDrawer* newDrawer = new StatusDrawer();

	newDrawer->Initialize(pParent, pVP);

	return newDrawer;
}

void StatusDrawer::Initialize(YMath::Matrix4* pParent, ViewProjection* pVP)
{
	transform_.Initialize();
	transform_.parent_ = pParent;
	
	if (statusUI_ == nullptr)
	{
		Transform::Status status;
		status.pos_ = kStatusPos;
		status.scale_ = kStatusScale;

		statusUI_.reset(DrawObjectForSprite3D::Create(status, false, false, pVP, pSpr));
		statusUI_->transform_.parent_ = &transform_.m;
	}
	if (hpGauge_ == nullptr)
	{
		hpGauge_.reset(HPGaugeDrawer::Create(&transform_.m, pVP));
	}
	if (speedLev_ == nullptr)
	{
		speedLev_.reset(SpeedLevelDrawer::Create(&transform_.m, pVP));
	}
}

void StatusDrawer::Update(const uint32_t hp, const uint32_t maxHP, const uint32_t speedLevel)
{
	transform_.UpdateMatrix();

	statusUI_->Update();
	
	hpGauge_->ChangeHPAnimation(hp, maxHP);
	hpGauge_->Update();
	
	speedLev_->ChangeSpeedAnimation(speedLevel);
	speedLev_->Update();
}

void StatusDrawer::Draw()
{
	statusUI_->Draw(kShaderTag, 0);
	hpGauge_->Draw();
	speedLev_->Draw();
}
