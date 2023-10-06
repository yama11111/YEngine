#include "AxisDrawer.h"

using YGame::AxisDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* AxisDrawer::spModel_ = nullptr;

AxisDrawer* AxisDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	AxisDrawer* newDrawer = new AxisDrawer();

	newDrawer->Initialize(pParent, drawPriority);
	newDrawer->isVisible_ = false;

	return newDrawer;
}

void AxisDrawer::LoadResource()
{
	// モデル設定
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png") } });
}

std::string AxisDrawer::Name()
{
	return "Axis";
}

void AxisDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	for (size_t i = 0; i < objs_.size(); i++)
	{
		if (objs_[i] == nullptr)
		{
			// オブジェクト + 定数バッファ生成
			objs_[i].reset(DrawObjectForModel::Create({}, spVP_, nullptr));

			cbColors_[i].reset(ConstBufferObject<CBColor>::Create());
		}

		objs_[i]->Initialize();

		
		objs_[i]->SetParent(&pParent->m_);

		// オブジェクトに定数バッファを設定
		objs_[i]->InsertConstBuffer(cbColors_[i].get());

	}
	
	const float kLength = 2.0f;

	objs_[0]->transform_.pos_ = { kLength,0.0f,0.0f };
	objs_[1]->transform_.pos_ = { 0.0f,kLength,0.0f };
	objs_[2]->transform_.pos_ = { 0.0f,0.0f,kLength };

	objs_[0]->transform_.scale_ = { kLength,0.1f,0.1f };
	objs_[1]->transform_.scale_ = { 0.1f,kLength,0.1f };
	objs_[2]->transform_.scale_ = { 0.1f,0.1f,kLength };
	
	cbColors_[0]->data_.baseColor = { 1.0f,0.0f,0.0f,1.0f };
	cbColors_[1]->data_.baseColor = { 0.0f,1.0f,0.0f,1.0f };
	cbColors_[2]->data_.baseColor = { 0.0f,0.0f,1.0f,1.0f };

	pParent_ = pParent;


	drawPriority_ = drawPriority;

	isVisible_ = true;

	isVisibleUpdate_ = true;

	isVisibleUpdate_ = false;

	shaderKey_ = "ModelPhong";
}

void AxisDrawer::Update()
{
	animeStatus_ = {};

	animeStatus_.pos_ += offset_;

	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i]->Update(animeStatus_);
	}

	VisibleUpdate();
}

void AxisDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i]->Draw(shaderKey_, drawPriority_);
	}
}

void AxisDrawer::SetParent(Transform* pParent)
{
	pParent_ = pParent;
	
	for (size_t i = 0; i < objs_.size(); i++)
	{
		objs_[i]->SetParent(&pParent->m_);
	}
}
