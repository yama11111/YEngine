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

	const size_t kTypeNum = static_cast<size_t>(BlockDrawer::Type::eNum);

	struct ColorSet
	{
		Vector4 body;
		Vector4 outline;
	};

	const ColorSet kColorSet[kTypeNum] =
	{
		{ YGame::ColorConfig::skTurquoise[5], YGame::ColorConfig::skTurquoise[3] },
		{ YMath::GetColor(245, 24, 83, 255), YMath::GetColor(143, 13, 48, 255) },
		{ {}, {}},
	};
}

std::unique_ptr<BlockDrawer> BlockDrawer::Create(
	const DrawerInitSet& init, const Type type, const bool isBackground)
{
	std::unique_ptr<BlockDrawer> newDrawer = std::make_unique<BlockDrawer>();

	newDrawer->Initialize(init);
	newDrawer->type_ = type;
	newDrawer->isBackground_ = isBackground;

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

	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.range = 0.02f;
	
	InsertConstBuffer("Block", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Block_O", cbOutline_.get());
	
	SetShaderTag("Block", "ModelToon");
	SetShaderTag("Block_O", "ModelOutline");
}

void BlockDrawer::InitializeObjects()
{
	InsertObject("Block", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Block_O", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void BlockDrawer::UpdateAnimation()
{
	cbColor_->data_.baseColor = kColorSet[static_cast<size_t>(type_)].body;
	cbOutline_->data_.color = kColorSet[static_cast<size_t>(type_)].outline;

	if (isBackground_)
	{
		cbOutline_->data_.color.w = 0.0f;
	}
}
