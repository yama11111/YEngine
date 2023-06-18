#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(
	const Type type, 
	const Transform::Status& status, 
	const float radius, 
	const bool isSlip,
	IDrawer* drawer)
{
	// 核生成
	transform_.reset(new Transform());

	// 初期化
	transform_->Initialize(status);

	// 描画クラス
	SetDrawer(drawer);

	// コライダー初期化
	GameObjectCollider::Initialize(type, &transform_->pos_, radius, isSlip);
}

void IGameObject::Update()
{
	// 核更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_->Update();
	
	// コライダー更新
	GameObjectCollider::Update();
}

void IGameObject::DrawDebugText(const bool isWindow)
{
	// ウィンドウなら
	if (isWindow)
	{

	}
}

void IGameObject::SetDrawer(IDrawer* drawer)
{
	// null なら
	if (drawer == nullptr && drawer_ == nullptr)
	{
		// スタンダード描画クラス設定
		// drawer_.reset(スタンダード);
	}
	else
	{
		// 描画クラス設定
		drawer_.reset(drawer);
	}

	// 描画クラス初期化
	drawer_->Initialize(transform_.get());
}
