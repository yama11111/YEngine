#include "Skydome.h"
#include <cassert>

using YGame::Skydome;

void Skydome::Initialize(const Transform::Status status, YGame::Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 代入
	pModel_ = pModel;

	// 生成
	obj_.reset(ModelObject::Create(status));
}

void Skydome::Update()
{
	// 更新
	obj_->UpdateMatrix();
}

void Skydome::Draw()
{
	// 描画
	pModel_->Draw(obj_.get());
}