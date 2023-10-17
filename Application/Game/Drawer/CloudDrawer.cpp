#include "CloudDrawer.h"
#include "DrawObjectForModel.h"

using YGame::CloudDrawer;
using YGame::Model;

namespace
{
	Model* pModel = nullptr;
}

CloudDrawer* CloudDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	CloudDrawer* newDrawer = new CloudDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void CloudDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void CloudDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelToon");

	cbColor_->data_.baseColor.a_ = 0.4f;
}

void CloudDrawer::InitializeObjects()
{
	InsertObject("Cloud", DrawObjectForModel::Create({}, spVP_, pModel));
}