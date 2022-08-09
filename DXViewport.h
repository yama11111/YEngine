#pragma once
#include "Vec2.h"
#include "DXCommandList.h"

class DXViewport
{
private:
	// ビューポート設定コマンド
	D3D12_VIEWPORT viewport{};
	DXCommandList* cmdList = nullptr;
public:
	struct SetStatus
	{
		Vec2 size;
		Vec2 topLeft = { 0,0 };
		float minDepth = 0.0f;
		float maxDepth = 1.0f;
	};
	void Set(const SetStatus& set);
	void Stack();
};