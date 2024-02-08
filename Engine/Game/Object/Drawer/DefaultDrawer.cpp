#include "DefaultDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

using YGame::DefaultDrawer;
using YGame::Model;
using YGame::ViewProjectionManager;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<DefaultDrawer> DefaultDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<DefaultDrawer> newDrawer = std::make_unique<DefaultDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void DefaultDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void DefaultDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);


	SetShaderTag("ModelDefault");
}

void DefaultDrawer::InitializeObjects()
{
	InsertObject("Default", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}