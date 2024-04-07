#include "SkydomeDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

#include "ColorConfig.h"

using YGame::SkydomeDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;
using YGame::ViewProjectionManager;

namespace
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();

	const size_t kTypeNum = static_cast<size_t>(SkydomeDrawer::Type::eNum);
	
	const Vector4 kColors[kTypeNum] =
	{
		YMath::GetColor(192, 252, 229, 255),
		YMath::GetColor(38, 11, 38, 255),
		YGame::ColorConfig::skTurquoise[2],
	};

	const Vector4 kColorRates[kTypeNum] =
	{
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector4(0.5f, 0.5f, 0.5f, 1.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
	};
}

std::unique_ptr<SkydomeDrawer> SkydomeDrawer::Create(const DrawerInitSet& init, const Type type)
{
	std::unique_ptr<SkydomeDrawer> newDrawer = std::make_unique<SkydomeDrawer>();

	newDrawer->type_ = type;
	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void SkydomeDrawer::LoadResource()
{
	pModel = Model::LoadObj("skydome", true);
}

void SkydomeDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	SetShaderTag("Skydome", "ModelBack");
}

void SkydomeDrawer::InitializeObjects()
{
	InsertObject("Skydome", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr("Default"), pModel));
}

void SkydomeDrawer::UpdateAnimation()
{
	SetVPkey("Default");

	cbColor_->data_.baseColor = kColors[static_cast<size_t>(type_)];
	cbColor_->data_.texColorRate = kColorRates[static_cast<size_t>(type_)];
}
