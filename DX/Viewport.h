#pragma once
#include "Vec2.h"
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class Viewport
	{
	private:
		// ビューポート設定コマンド
		D3D12_VIEWPORT viewport{};
		static ID3D12GraphicsCommandList* pCmdList;
	public:
		struct SetStatus
		{
			Math::Vec2 size;
			Math::Vec2 topLeft = { 0,0 };
			float minDepth = 0.0f;
			float maxDepth = 1.0f;
		};
		void Set(const SetStatus& set);
		void Stack();
	public:
		static void StaticInit(ID3D12GraphicsCommandList* pCommandList);
	};
}