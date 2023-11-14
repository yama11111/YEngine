#include "GameObject.h"
#include <cassert>
#include <imgui.h>

#include "AxisDrawer.h"

using YGame::GameObject;

void GameObject::Initialize(const std::string& name, const Transform::Status& status, GameObject* pParent)
{
	SetName(name);

	// トランスフォーム生成 + 初期化
	transform_.reset(new Transform(status));
	
	SetParent(pParent);

	InsertSubDrawer(AxisDrawer::Name(), AxisDrawer::Create(transform_.get(), 1));

	// 行列更新
	transform_->UpdateMatrix();

	isUpdate_ = true;

	isExist_ = true;
}

void GameObject::UpdateBeforeCollision()
{

}

void GameObject::UpdateAfterCollision()
{
	// 核更新
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

void GameObject::SendCollisionInfo(const size_t collIndex)
{
	collIndex;
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

void GameObject::SetCollider(GameCollider* collider)
{
	collider_.reset(collider);
}

void GameObject::SetDrawer(BaseDrawer* drawer)
{
	drawer_.reset(drawer);
	
	// null じゃないなら
	if (drawer_)
	{
		// 描画クラス親ポインタ設定
		drawer_->SetParent(transform_.get());
	}
}

void GameObject::InsertSubDrawer(const std::string& tag, BaseDrawer* drawer)
{
	assert(drawer);
	assert(subDrawer_.contains(tag) == false);

	std::unique_ptr<BaseDrawer> newDrawer;
	newDrawer.reset(drawer);
	
	// 描画クラス親ポインタ設定
	newDrawer->SetParent(transform_.get());

	// マップに挿入
	subDrawer_.insert({ tag, std::move(newDrawer) });
}

void GameObject::SetCollisionIndex(const size_t collIndex)
{
	collIndex_ = collIndex;
}

void GameObject::SetIsUpdate(const bool isUpdate)
{
	isUpdate_ = isUpdate;
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
