#include "GameObject.h"
#include <cassert>
#include <imgui.h>

using YGame::GameObject;

void GameObject::Initialize(const std::string name, const Transform::Status& status, GameObject* pParent)
{
	SetName(name);

	// �g�����X�t�H�[������ + ������
	transform_.reset(new Transform(status));
	
	SetParent(pParent);

	// �s��X�V
	transform_->UpdateMatrix();
}

void GameObject::Update()
{
	// ���R���C�_�[�X�V
	if (collider_) { collider_->Update(); }

	// �j�X�V
	transform_->UpdateMatrix();

	// �`��N���X�X�V
	if (drawer_) { drawer_->Update(); }
}

void GameObject::Draw()
{
	// �`��
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
		// �e�s��ɑ}��
		transform_->parent_ = &pParent_->transform_->m_;
	}
	else
	{
		transform_->parent_ = nullptr;
	}
}

void GameObject::SetCollider(BaseCollider* collider)
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
	// �`��N���X�ݒ�
	drawer_.reset(drawer);
	
	// null ����Ȃ��Ȃ�
	if (drawer_)
	{
		// �`��N���X�e�|�C���^�ݒ�
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
