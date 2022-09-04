#pragma once
#include "../Math/Vec2.h"
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class ScissorRect
	{
	private:
		// シザー矩形
		D3D12_RECT scissorRect{};
		static ID3D12GraphicsCommandList* pCmdList;
	public:
		static void StaticInit(ID3D12GraphicsCommandList* pCommandList);
		struct SetStatus
		{
			Vec2 topLeft;
			Vec2 bottomRight;
		};
		void Set(const SetStatus& set);
		void Stack();
	};
}