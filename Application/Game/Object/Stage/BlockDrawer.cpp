#include "BlockDrawer.h"
#include "DrawObjectForModel.h"
#include "ColorConfig.h"
#include "CircleShadowManager.h"

using YGame::BlockDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	Model* pModel = nullptr;
}

std::unique_ptr<BlockDrawer> BlockDrawer::Create(
	Transform* pParent, YMath::Vector3* pParentWorldPos, const bool isBackground, const size_t drawPriority)
{
	std::unique_ptr<BlockDrawer> newDrawer = std::make_unique<BlockDrawer>();

	newDrawer->Initialize(pParent, pParentWorldPos, drawPriority);

	if (isBackground)
	{
		newDrawer->cbOutline_->data_.color.w = 0.0f;
	}

	return std::move(newDrawer);
}

void BlockDrawer::LoadResource()
{
	pModel = Model::LoadObj("soil", true);
}

void BlockDrawer::Initialize(Transform* pParent, YMath::Vector3* pParentWorldPos, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, pParentWorldPos, drawPriority);

	
	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	cbColor_->data_.baseColor = ColorConfig::skTurquoise[5];
	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skTurquoise[3];
	cbOutline_->data_.range = 0.02f;
	
	InsertConstBuffer("Block", CircleShadowManager::GetInstance()->CBPtr(0));
	InsertConstBuffer("Block_O", cbOutline_.get());
	
	SetShaderTag("Block", "ModelToon");
	SetShaderTag("Block_O", "ModelOutline");
}

void BlockDrawer::InitializeObjects()
{
	InsertObject("Block", DrawObjectForModel::Create({}, spVP_, pModel));
	InsertObject("Block_O", DrawObjectForModel::Create({}, spVP_, pModel));
}
