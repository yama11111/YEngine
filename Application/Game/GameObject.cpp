#include "GameObject.h"
#include <cassert>

using YGame::GameObject;

void GameObject::Initialize(const Transform::Status& status)
{
	// トランスフォーム生成 + 初期化
	transform_.reset(new Transform(status));
}

void GameObject::Update()
{
	// 基底コライダー更新
	if (collider_) { collider_->Update(); }

	// 核更新
	transform_->UpdateMatrix();

	// 描画クラス更新
	if (drawer_) { drawer_->Update(); }
}

void GameObject::Draw()
{
	// 描画
	drawer_->Draw();
}

void GameObject::OnCollision()
{
}

void GameObject::SetCollider(BaseCollider* collider)
{
	// コライダークラス設定
	collider_.reset(collider);

	// null じゃないなら
	if (collider_)
	{
		// コライダークラス親ポインタ設定
		collider_->SetParent(transform_.get());
	}
}

void GameObject::SetDrawer(BaseDrawer* drawer)
{
	// 描画クラス設定
	drawer_.reset(drawer);
	
	// null じゃないなら
	if (drawer_)
	{
		// 描画クラス親ポインタ設定
		drawer_->SetParent(transform_.get());
	}
}