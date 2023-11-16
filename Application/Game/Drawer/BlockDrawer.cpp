#include "BlockDrawer.h"
#include "DrawObjectForModel.h"
#include "ColorConfig.h"

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
	
	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	cbColor_->data_.baseColor = ColorConfig::skTurquoise[5];
	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skTurquoise[3];
	cbOutline_->data_.range = 0.01f;
	
	InsertConstBuffer("Block_O", cbOutline_.get());
	
	SetShaderTag("Block", "ModelToon");
	SetShaderTag("Block_O", "ModelOutline");
}

void BlockDrawer::InitializeObjects()
{
	InsertObject("Block", DrawObjectForModel::Create({}, spVP_, pModel));
	InsertObject("Block_O", DrawObjectForModel::Create({}, spVP_, pModel));
}
