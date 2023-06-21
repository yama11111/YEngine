#include "IGameObject.h"
#include <cassert>

using YGame::IGameObject;

void IGameObject::Initialize(
	const Transform::Status& status,
	IDrawer* drawer,
	const DrawLocation location)
{
	// 核生成
	transform_.reset(new Transform());

	// 初期化
	transform_->Initialize(status);

	// 描画クラス
	SetDrawer(drawer);

	// 描画位置設定
	SetDrawLocation(location);
}

void IGameObject::Update()
{
	// 核更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	drawer_->Update();
}

void IGameObject::Draw()
{
	// 描画
	drawer_->Draw(location_);
}

void IGameObject::SetDrawer(IDrawer* drawer)
{
	// null なら
	if (drawer == nullptr)
	{
		// スタンダード描画クラス設定
		//drawer_.reset(スタンダード);
	}
	else
	{
		// 描画クラス設定
		drawer_.reset(drawer);
	}

	// 描画クラス初期化
	drawer_->Initialize(transform_.get());
}

void IGameObject::SetDrawLocation(const DrawLocation location)
{
	// 代入
	location_ = location;
}
