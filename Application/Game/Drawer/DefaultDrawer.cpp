#include "DefaultDrawer.h"
#include "DrawObjectForModel.h"

using YGame::DefaultDrawer;
using YGame::Model;

namespace
{
	Model* pModel = nullptr;
}

DefaultDrawer* DefaultDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	DefaultDrawer* newDrawer = new DefaultDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
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