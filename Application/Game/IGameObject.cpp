#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(
	const Type type, 
	const Transform::Status& status, 
	const float radius, 
	const bool isSlip)
{
	// 核生成
	transform_.reset(new Transform());

	// 初期化
	transform_->Initialize(status);


	// オブジェクト生成
	obj_.reset(Model::Object::Create());

	// 親子関係設定
	obj_->parent_ = &transform_->m_;


	// コライダー初期化
	GameObjectCollider::Initialize(type, &transform_->pos_, radius, isSlip);
}

void IGameObject::Update()
{
	// 核更新
	transform_->UpdateMatrix();

	// オブジェクト更新
	obj_->UpdateMatrix();
	
	// コライダー更新
	GameObjectCollider::Update();
}

void IGameObject::SetModel(Model* pModel)
{
	// nullチェック
	assert(pModel);

	// 代入
	pModel_ = pModel;
}
