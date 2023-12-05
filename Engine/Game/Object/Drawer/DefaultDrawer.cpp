#include "DefaultDrawer.h"
#include "DrawObjectForModel.h"

using YGame::DefaultDrawer;
using YGame::Model;

namespace
{
	Model* pModel = nullptr;
}

std::unique_ptr<DefaultDrawer> DefaultDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	std::unique_ptr<DefaultDrawer> newDrawer = std::make_unique<DefaultDrawer>();

	newDrawer->Initialize(pParent, drawPriority);

	return std::move(newDrawer);
}

void DefaultDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void DefaultDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelDefault");
}

void DefaultDrawer::InitializeObjects()
{
	InsertObject("Default", DrawObjectForModel::Create({}, spVP_, pModel));
}