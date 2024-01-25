#include "CloudDrawer.h"
#include "DrawObjectForModel.h"

#include "CircleShadowManager.h"

using YGame::CloudDrawer;
using YGame::Model;

namespace
{
	Model* pModel = nullptr;
}

std::unique_ptr<CloudDrawer> CloudDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	std::unique_ptr<CloudDrawer> newDrawer = std::make_unique<CloudDrawer>();

	newDrawer->Initialize(pParent, drawPriority);

	return std::move(newDrawer);
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

	InsertConstBuffer("Cloud", CircleShadowManager::GetInstance()->CBPtr(2));
	
	SetShaderTag("ModelToon");

	cbColor_->data_.baseColor.a_ = 0.4f;
}

void CloudDrawer::InitializeObjects()
{
	InsertObject("Cloud", DrawObjectForModel::Create({}, spVP_, pModel));
}