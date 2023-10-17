#include "AxisDrawer.h"
#include "DrawObjectForModel.h"

using YGame::AxisDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace 
{
	Model* pModel = nullptr;
}

AxisDrawer* AxisDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	AxisDrawer* newDrawer = new AxisDrawer();

	newDrawer->Initialize(pParent, drawPriority);
	newDrawer->SetIsVisible(false);

	return newDrawer;
}

void AxisDrawer::LoadResource()
{
	// モデル設定
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png") } });
}

void AxisDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	BaseDrawer::Initialize(pParent, drawPriority);
	
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

	SetDrawPriority(drawPriority);

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
	InsertObject("X", DrawObjectForModel::Create({}, spVP_, pModel));
	InsertObject("Y", DrawObjectForModel::Create({}, spVP_, pModel));
	InsertObject("Z", DrawObjectForModel::Create({}, spVP_, pModel));
}

std::string AxisDrawer::Name()
{
	return "Axis";
}