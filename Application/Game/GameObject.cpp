#include "GameObject.h"
#include <cassert>
#include <imgui.h>

#include "AxisDrawer.h"

using YGame::GameObject;

void GameObject::Initialize(const std::string name, const Transform::Status& status, GameObject* pParent)
{
	SetName(name);

	// �g�����X�t�H�[������ + ������
	transform_.reset(new Transform(status));
	
	SetParent(pParent);

	InsertSubDrawer(AxisDrawer::Name(), AxisDrawer::Create(transform_.get(), 1));

	// �s��X�V
	transform_->UpdateMatrix();
}

void GameObject::Update()
{
	// �j�X�V
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
	// �`��
	if (drawer_) { drawer_->Draw(); }

	if (subDrawer_.empty() == false)
	{
		for (auto itr = subDrawer_.begin(); itr != subDrawer_.end(); ++itr)
		{
			itr->second->Draw();
		}
	}
}

void GameObject::OnCollision()
{
}

void GameObject::SetParent(GameObject* pParent)
{
	pParent_ = pParent;

	if (pParent_)
	{
		// �e�s��ɑ}��
		transform_->parent_ = &pParent_->transform_->m_;
	}
	else
	{
		transform_->parent_ = nullptr;
	}
}

void GameObject::SetCollider(GameCollider* collider)
{
	// �R���C�_�[�N���X�ݒ�
	collider_.reset(collider);

	// null ����Ȃ��Ȃ�
	if (collider_)
	{
		// �R���C�_�[�N���X�e�|�C���^�ݒ�
		collider_->SetParent(transform_.get());
	}
}

void GameObject::SetDrawer(BaseDrawer* drawer)
{
	drawer_.reset(drawer);
	
	// null ����Ȃ��Ȃ�
	if (drawer_)
	{
		// �`��N���X�e�|�C���^�ݒ�
		drawer_->SetParent(transform_.get());
	}
}

void GameObject::InsertSubDrawer(const std::string& tag, BaseDrawer* drawer)
{
	assert(drawer);
	assert(subDrawer_.contains(tag) == false);

	std::unique_ptr<BaseDrawer> newDrawer;
	newDrawer.reset(drawer);
	
	// �`��N���X�e�|�C���^�ݒ�
	newDrawer->SetParent(transform_.get());

	// �}�b�v�ɑ}��
	subDrawer_.insert({ tag, std::move(newDrawer)});
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
