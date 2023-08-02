#include "DebugTextAttacher.h"
#include <imgui.h>

void DebugTextAttacher::DrawDebugText(const bool isWindow)
{
	bool isTree = false;

	if (isWindow)
	{
		// �E�B���h�E�쐬
		ImGui::Begin(name_.c_str());
	}
	else
	{
		if (name_.empty())
		{
			// �c���[�m�[�h�쐬
			isTree = ImGui::TreeNode("noname");
		}
		else
		{
			// �c���[�m�[�h�쐬
			isTree = ImGui::TreeNode(name_.c_str());
		}
	}

	if (isTree)
	{
		// �f�o�b�O�e�L�X�g
		DrawDebugTextContent();
	}

	if (isWindow)
	{
		// �I��
		ImGui::End();
	}
	else
	{
		if (isTree)
		{
			// �|�b�v
			ImGui::TreePop();
		}
	}
}

void DebugTextAttacher::SetName(const std::string& name)
{
	// ���O�}��
	name_ = name;
}