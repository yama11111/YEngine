#include "DebugTextAttacher.h"
#include <imgui.h>

void DebugTextAttacher::DrawDebugText(const bool isWindow)
{
	bool isTree = false;

	if (isWindow)
	{
		// ウィンドウ作成
		ImGui::Begin(name_.c_str());
	}
	else
	{
		if (name_.empty())
		{
			// ツリーノード作成
			isTree = ImGui::TreeNode("noname");
		}
		else
		{
			// ツリーノード作成
			isTree = ImGui::TreeNode(name_.c_str());
		}
	}

	if (isTree)
	{
		// デバッグテキスト
		DrawDebugTextContent();
	}

	if (isWindow)
	{
		// 終了
		ImGui::End();
	}
	else
	{
		if (isTree)
		{
			// ポップ
			ImGui::TreePop();
		}
	}
}

void DebugTextAttacher::SetName(const std::string& name)
{
	// 名前挿入
	name_ = name;
}