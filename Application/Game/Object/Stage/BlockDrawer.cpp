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
	const DrawerInitSet& init, const Type type, const bool isBackground,
	const SceneKey scene)
{
	std::unique_ptr<BlockDrawer> newDrawer = std::make_unique<BlockDrawer>();

	newDrawer->scene_ = scene;
	newDrawer->isBackground_ = isBackground;
	newDrawer->type_ = type;
	newDrawer->Initialize(init);

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

	cbColor_->data_.texColorRate = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	cbMaterial_->data_.ambient = Vector3(0.4f, 0.4f, 0.4f);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.range = 0.02f;
	
	InsertConstBuffer("Block", CircleShadowManager::GetInstance()->CBPtr(CircleShadowManager::Key::eWorld_0));
	InsertConstBuffer("Block_O", cbOutline_.get());
	
	if (scene_ == SceneKey::eTitleKey)
	{
		SetShaderTag("ModelSingleColor");

		if (isBackground_)
		{
			cbColor_->data_.baseColor = ColorConfig::skTurquoise[4];
			cbColor_->data_.texColorRate.w = 0.5f;
		}
		else
		{
			SetShaderTag("Block_O", "ModelOutline");
			cbColor_->data_.baseColor = kColorSet[static_cast<size_t>(Type::eGreen)].body;
			cbOutline_->data_.color = kColorSet[static_cast<size_t>(Type::eGreen)].outline;
		}
	}
	if (scene_ == SceneKey::ePlayKey)
	{
		SetShaderTag("Block", "ModelToon");
		SetShaderTag("Block_O", "ModelOutline");
	}
}

void BlockDrawer::InitializeObjects()
{
	InsertObject("Block", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Block_O", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

void BlockDrawer::UpdateAnimation()
{
	if (scene_ == SceneKey::ePlayKey)
	{
		cbColor_->data_.baseColor = kColorSet[static_cast<size_t>(type_)].body;
		cbOutline_->data_.color = kColorSet[static_cast<size_t>(type_)].outline;
	}

	if (isBackground_)
	{
		cbOutline_->data_.color = Vector4(1.0f, 1.0f, 1.0f, 0.5f);
		cbColor_->data_.texColorRate.w = 0.5f;
	}
}
