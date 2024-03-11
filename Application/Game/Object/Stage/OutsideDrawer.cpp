#include "OutsideDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"
#include "ColorConfig.h"
#include "CircleShadowManager.h"

using YGame::OutsideDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;
using YGame::ViewProjectionManager;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<OutsideDrawer> OutsideDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<OutsideDrawer> newDrawer = std::make_unique<OutsideDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void OutsideDrawer::LoadResource()
{
	pModel = Model::LoadObj("outside", true);
}

void OutsideDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create());

	InsertConstBuffer("Outside", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Outside", cbTexConfig_.get());

	SetShaderTag("Outside", "ModelBack");
}

void OutsideDrawer::InitializeObjects()
{
	InsertObject("Outside", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void OutsideDrawer::UpdateAnimation()
{
	cbTexConfig_->data_.offset.x += 0.01f;
	//objs_["Outside"]->transform_.rota_.z += 0.01f;
}
