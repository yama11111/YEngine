#include "BlockDrawer.h"
#include "DrawObjectForModel.h"

using YGame::BlockDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Model* pModel = nullptr;
}

BlockDrawer* BlockDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	BlockDrawer* newDrawer = new BlockDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void BlockDrawer::LoadResource()
{
	pModel = Model::LoadObj("soil", true);
}

void BlockDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);
	
	SetShaderTag("ModelPhong");
	
	transform_.scale_ = Vector3(1.0f, 1.0f, 15.0f);

	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);
}

void BlockDrawer::InitializeObjects()
{
	InsertObject("Block", DrawObjectForModel::Create({}, spVP_, pModel));
}
