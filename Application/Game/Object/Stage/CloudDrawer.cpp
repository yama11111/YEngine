#include "CloudDrawer.h"
#include "ViewProjectionManager.h"
#include "DrawObjectForModel.h"

#include "CircleShadowManager.h"

using YGame::CloudDrawer;
using YGame::Model;
using YGame::ViewProjectionManager;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<CloudDrawer> CloudDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<CloudDrawer> newDrawer = std::make_unique<CloudDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void CloudDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void CloudDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);


	InsertConstBuffer("Cloud", CircleShadowManager::GetInstance()->CBPtr(2));
	
	SetShaderTag("ModelToon");

	cbColor_->data_.baseColor.w = 0.4f;
}

void CloudDrawer::InitializeObjects()
{
	InsertObject("Cloud", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}