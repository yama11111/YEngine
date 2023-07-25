#include "Smoke.h"
#include "PipelineManager.h"
#include "MathVector.h"

void YGame::Smoke::Initialize(const Transform::Status& status)
{
	pModels_.emplace_back(Model::CreateCube(
		{
			{ "Texture", Texture::Load("player.png") },
			{ "Mask", Texture::Load("DissolveMap.png") },
		}
	));

	pModels_.emplace_back(Model::CreateCube(
		{
			{ "Texture", Texture::Load("enemy.png") },
			{ "Mask", Texture::Load("DissolveMap.png") },
		}
	));

	transform_.reset(new Transform(status));

	objs_.resize(2);

	// オブジェクト + 定数バッファ生成
	// 生成後、オブジェクトに挿入
	objs_[0].reset(new Object());
	objs_[1].reset(new Object());

	cbTransform_.reset(ConstBuffer<CBModelTransform::CBData>::Create());
	objs_[0]->InsertConstBuffer(CBModelTransform::KeyName(), cbTransform_.get());
	objs_[1]->InsertConstBuffer(CBModelTransform::KeyName(), cbTransform_.get());

	cbTime_.reset(ConstBuffer<CBTime::CBData>::Create());
	objs_[0]->InsertConstBuffer(CBTime::KeyName(), cbTime_.get());
	objs_[1]->InsertConstBuffer(CBTime::KeyName(), cbTime_.get());

	cbColor_.reset(ConstBuffer<CBColor::CBData>::Create());
	objs_[0]->InsertConstBuffer(CBColor::KeyName(), cbColor_.get());
	objs_[1]->InsertConstBuffer(CBColor::KeyName(), cbColor_.get());

	cbTexConfig_.reset(ConstBuffer<CBTexConfig::CBData>::Create());
	objs_[0]->InsertConstBuffer(CBTexConfig::KeyName(), cbTexConfig_.get());
	objs_[1]->InsertConstBuffer(CBTexConfig::KeyName(), cbTexConfig_.get());

	objs_[0]->SetGraphic(pModels_[0]);
	objs_[1]->SetGraphic(pModels_[1]);
}

void YGame::Smoke::Update(const YGame::ViewProjection& vp)
{
	transform_->UpdateMatrix();
	
	cbTransform_->data_.matWorld = transform_->m_;
	cbTransform_->data_.matViewProj = vp.view_ * vp.pro_;
	cbTransform_->data_.cameraPos = vp.eye_;

	cbTime_->data_.time += 0.005f;
	if (cbTime_->data_.time > 1.0f)
	{
		cbTime_->data_.time = 0.0f;
	}
}

void YGame::Smoke::Draw(const std::string& key, const size_t index)
{
	PipelineManager::GetInstance()->EnqueueDrawSet(key, 0, objs_[index].get());
}
