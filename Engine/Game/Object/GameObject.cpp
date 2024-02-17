#include "GameObject.h"
#include <cassert>
#include <imgui.h>

using YGame::GameObject;

void GameObject::Initialize(const std::string& name, const Transform::Status& status, GameObject* pParent)
{
	SetName(name);

	// トランスフォーム生成 + 初期化
	transform_.reset(new Transform(status));
	
	SetParent(pParent);

	// 行列更新
	transform_->UpdateMatrix();

	initPos_ = status.pos_;

	localPos_ = {};

	worldPos_ = initPos_;

	isExist_ = true;

	isControlUpdate_ = true;

	isSaveColl_ = false;
}

void GameObject::UpdateBeforeCollision()
{
	if (collider_) 
	{
		collider_->Update(); 
	}

	if (isControlUpdate_)
	{
		UpdateControl();
	}
}

void GameObject::UpdateAfterCollision()
{	
	transform_->UpdateMatrix();

	if (drawer_)
	{
		drawer_->Update();
	}

	if (subDrawer_.empty() == false)
	{
		for (auto itr = subDrawer_.begin(); itr != subDrawer_.end(); ++itr)
		{
			itr->second->Update();
		}
	}

	// 衝突処理
	UpdateCollision();
}

void GameObject::Draw()
{
	// 描画
	if (drawer_) { drawer_->Draw(); }

	if (subDrawer_.empty() == false)
	{
		for (auto itr = subDrawer_.begin(); itr != subDrawer_.end(); ++itr)
		{
			itr->second->Draw();
		}
	}
}

void GameObject::SetParent(GameObject* pParent)
{
	pParent_ = pParent;

	if (pParent_)
	{
		// 親行列に挿入
		transform_->parent_ = &pParent_->transform_->m;
	}
	else
	{
		transform_->parent_ = nullptr;
	}
}

void GameObject::SetCollider(std::unique_ptr<GameCollider>&& collider)
{
	collider_.reset();
	collider_ = std::move(collider);
}

void GameObject::SetDrawer(std::unique_ptr<BaseDrawer>&& drawer)
{
	drawer_.reset();
	drawer_ = std::move(drawer);

	// null じゃないなら
	if (drawer_)
	{
		// 描画クラス親ポインタ設定
		drawer_->SetParent(transform_.get());
		drawer_->SetParentWorldPos(&worldPos_);
	}
}

void GameObject::InsertSubDrawer(const std::string& tag, std::unique_ptr<BaseDrawer>&& drawer)
{
	assert(drawer);
	assert(subDrawer_.contains(tag) == false);

	// 描画クラス親ポインタ設定
	drawer->SetParent(transform_.get());

	// マップに挿入
	subDrawer_.insert({ tag, std::move(drawer) });
}

YGame::ICollisionInfomation GameObject::GetCollisionInfomation()
{
	ICollisionInfomation info{};

	info.pTrfm = transform_.get();

	return info;
}

void GameObject::UpdateControl()
{
}

void GameObject::UpdateCollision()
{
	if (collider_ == nullptr) { return; }

	std::queue<ICollisionInfomation> queue = collider_->InfoOnCollisionQueue();

	// 衝突情報を1つ1つ処理
	// 空なら終わり
	while (true)
	{
		if (queue.empty()) { break; }

		OnCollision(queue.front());

		queue.pop();
	}
}

void GameObject::OnCollision(const ICollisionInfomation& info)
{
	info;
}

void GameObject::DrawDebugTextContent()
{
	ImGui::SetNextItemOpen(false, ImGuiCond_Once);
	if (ImGui::TreeNode("transform"))
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("pos"))
		{
			ImGui::Text("x : %5f", transform_->pos_.x);
			ImGui::Text("y : %5f", transform_->pos_.y);
			ImGui::Text("z : %5f", transform_->pos_.z);
			ImGui::TreePop();
		}
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("rotation"))
		{
			ImGui::Text("x : %5f", transform_->rota_.x);
			ImGui::Text("y : %5f", transform_->rota_.y);
			ImGui::Text("z : %5f", transform_->rota_.z);
			ImGui::TreePop();
		}
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("scale"))
		{
			ImGui::Text("x : %5f", transform_->scale_.x);
			ImGui::Text("y : %5f", transform_->scale_.y);
			ImGui::Text("z : %5f", transform_->scale_.z);
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}

	if (collider_)
	{
		collider_->DrawDebugTextContent();
	}

	if (drawer_)
	{
		drawer_->DrawDebugTextContent();
	}
}
