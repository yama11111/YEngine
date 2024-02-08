#include "BlockDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"
#include "ColorConfig.h"
#include "CircleShadowManager.h"

using YGame::BlockDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;
using YGame::ViewProjectionManager;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<BlockDrawer> BlockDrawer::Create(const DrawerInitSet& init, const bool isBackground)
{
	std::unique_ptr<BlockDrawer> newDrawer = std::make_unique<BlockDrawer>();

	newDrawer->Initialize(init);

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

void BlockDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);
	
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
	InsertObject("Block", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Block_O", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}
