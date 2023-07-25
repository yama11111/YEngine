#include "Floor.h"
#include "PipelineManager.h"
#include "MathVector.h"

void YGame::Floor::Initialize(const Transform::Status& status)
{
	pSprite2D_ = Sprite2D::Create(
		{
			{ "Texture0", Texture::Load("Grass.jpg") },
			{ "Texture1", Texture::Load("Dirt.jpg") },
			{ "Mask", Texture::Load("FirldMask.png") },
		}
	);

	transform_.reset(new Transform(status));

	// オブジェクト + 定数バッファ生成
	// 生成後、オブジェクトに挿入
	obj_.reset(new Object());

	cbTransform_.reset(ConstBuffer<CBSprite2DTransform::CBData>::Create());
	obj_->InsertConstBuffer(CBSprite2DTransform::KeyName(), cbTransform_.get());

	cbColor_.reset(ConstBuffer<CBColor::CBData>::Create());
	obj_->InsertConstBuffer(CBColor::KeyName(), cbColor_.get());

	cbTexConfig_.reset(ConstBuffer<CBTexConfig::CBData>::Create());
	obj_->InsertConstBuffer(CBTexConfig::KeyName(), cbTexConfig_.get());

	obj_->SetGraphic(pSprite2D_);
}

void YGame::Floor::Update()
{
	transform_->UpdateMatrix();

	cbTransform_->data_.matWorld = transform_->m_ * YMath::MatOrthoGraphic();
}

void YGame::Floor::Draw(const std::string& key)
{
	PipelineManager::GetInstance()->EnqueueDrawSet(key, 0, obj_.get());
}
