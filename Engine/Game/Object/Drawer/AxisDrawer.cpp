#include "AxisDrawer.h"
#include "DrawObjectForModel.h"
#include "ViewProjectionManager.h"

using YGame::AxisDrawer;
using YGame::Model;
using YGame::ViewProjectionManager;
using YMath::Vector3;
using YMath::Vector4;

namespace 
{
	Model* pModel = nullptr;
	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<AxisDrawer> AxisDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<AxisDrawer> newDrawer = std::make_unique<AxisDrawer>();

	newDrawer->Initialize(init);
	newDrawer->SetIsVisible(false);

	return std::move(newDrawer);
}

void AxisDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png") } });
}

void AxisDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);

	
	for (size_t i = 0; i < cbColors_.size(); i++)
	{
		if (cbColors_[i] == nullptr)
		{
			cbColors_[i].reset(ConstBufferObject<CBColor>::Create());
		}
	}

	InsertConstBuffer("X", cbColors_[0].get());
	InsertConstBuffer("Y", cbColors_[1].get());
	InsertConstBuffer("Z", cbColors_[2].get());

	SetIsVisible(true);
	
	isVisibleUpdate_ = false;

	SetShaderTag("ModelPhong");

	const float kLength = 2.0f;

	objs_["X"]->transform_.pos_ = { kLength,0.0f,0.0f };
	objs_["Y"]->transform_.pos_ = { 0.0f,kLength,0.0f };
	objs_["Z"]->transform_.pos_ = { 0.0f,0.0f,kLength };

	objs_["X"]->transform_.scale_ = { kLength,0.1f,0.1f };
	objs_["Y"]->transform_.scale_ = { 0.1f,kLength,0.1f };
	objs_["Z"]->transform_.scale_ = { 0.1f,0.1f,kLength };
	
	cbColors_[0]->data_.baseColor = { 1.0f,0.0f,0.0f,1.0f };
	cbColors_[1]->data_.baseColor = { 0.0f,1.0f,0.0f,1.0f };
	cbColors_[2]->data_.baseColor = { 0.0f,0.0f,1.0f,1.0f };
}

void AxisDrawer::InitializeObjects()
{
	InsertObject("X", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Y", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
	InsertObject("Z", DrawObjectForModel::Create({}, pVPMan->ViewProjectionPtr(vpKey_), pModel));
}

std::string AxisDrawer::Name()
{
	return "Axis";
}