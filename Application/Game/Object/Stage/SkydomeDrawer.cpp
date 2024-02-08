#include "SkydomeDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"
#include "ColorConfig.h"
#include "Lerp.h"
#include "Def.h"

using YGame::SkydomeDrawer;
using YGame::ViewProjectionManager;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<SkydomeDrawer> SkydomeDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<SkydomeDrawer> newDrawer = std::make_unique<SkydomeDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void SkydomeDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::LoadObj("sphere", true);
}

void SkydomeDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	if (backTexConfig_ == nullptr)
	{
		backTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create());
	}
	InsertConstBuffer(backTexConfig_.get());
	
	backTexConfig_->data_.tiling = { 50.0f,50.0f };
	
	//cbColor_->data_.baseColor = YGame::ColorConfig::skTurquoise[0];
	//cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	isVisibleUpdate_ = false;

	SetShaderTag("ModelDefault");

	PlayAnimation(static_cast<uint32_t>(AnimationType::eIdle), true);
}

void SkydomeDrawer::InitializeObjects()
{
	InsertObject("Sphere", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void SkydomeDrawer::InitializeTimers()
{
	InsertAnimationTimer(static_cast<uint32_t>(AnimationType::eIdle), AnimationTimer(YMath::Timer(240), true));
}

void SkydomeDrawer::UpdateAnimation()
{
	float ratio = animationTimers_[static_cast<uint16_t>(AnimationType::eIdle)].timer.Ratio();
	float offsetX = YMath::Lerp(0.0f, 1.0f, ratio);
	float offsetY = YMath::Lerp(0.0f, 1.0f, ratio);
	
	backTexConfig_->data_.offset = { offsetX, offsetY };
}