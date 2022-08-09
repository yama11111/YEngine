#pragma once
#include "Vec2.h"
#include "DXCommandList.h"

class DXScissorRect
{
private:
	// シザー矩形
	D3D12_RECT scissorRect{};
	DXCommandList* cmdList = nullptr;
public:
	struct SetStatus
	{
		Vec2 topLeft;
		Vec2 bottomRight;
	};
	void Set(const SetStatus& set);
	void Stack();
};
