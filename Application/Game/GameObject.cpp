#include "GameObject.h"
#include <cassert>
#include <imgui.h>

using YGame::GameObject;

void GameObject::Initialize(const std::string name, const Transform::Status& status, GameObject* pParent)
{
	SetName(name);

	// トランスフォーム生成 + 初期化
	transform_.reset(new Transform(status));
	
	SetParent(pParent);

	// 行列更新
	transform_->UpdateMatrix();
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
	if (drawer_) { drawer_->Draw(); }
}

void GameObject::OnCollision()
{
}

void GameObject::SetParent(GameObject* pParent)
{
	pParent_ = pParent;

	if (pParent_)
	{
		// 親行列に挿入
		transform_->parent_ = &pParent_->transform_->m_;
	}
	else
	{
		transform_->parent_ = nullptr;
	}
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

void GameObject::DrawDebugTextContent()
{
	ImGui::SetNextItemOpen(false, ImGuiCond_Once);
	if (ImGui::TreeNode("transform"))
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("pos"))
		{
			ImGui::Text("x : %5f", transform_->pos_.x_);
			ImGui::Text("y : %5f", transform_->pos_.y_);
			ImGui::Text("z : %5f", transform_->pos_.z_);
			ImGui::TreePop();
		}
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("rotation"))
		{
			ImGui::Text("x : %5f", transform_->rota_.x_);
			ImGui::Text("y : %5f", transform_->rota_.y_);
			ImGui::Text("z : %5f", transform_->rota_.z_);
			ImGui::TreePop();
		}
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("scale"))
		{
			ImGui::Text("x : %5f", transform_->scale_.x_);
			ImGui::Text("y : %5f", transform_->scale_.y_);
			ImGui::Text("z : %5f", transform_->scale_.z_);
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
