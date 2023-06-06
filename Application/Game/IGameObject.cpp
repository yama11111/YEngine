#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(const Transform::Status& status)
{
	// 核生成
	core_.reset(new Transform());

	// 初期化
	core_->Initialize(status);


	// オブジェクト生成
	obj_.reset(Model::Object::Create());

	// 親子関係設定
	obj_->parent_ = &core_->m_;
}

void IGameObject::SetModel(Model* pModel)
{
	// nullチェック
	assert(pModel);

	// 代入
	pModel_ = pModel;
}
