#pragma once
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class VertexLayoutManager
	{
	public:
		// 頂点レイアウト
		std::vector<D3D12_INPUT_ELEMENT_DESC> spriteIL;
		// 頂点レイアウト
		std::vector<D3D12_INPUT_ELEMENT_DESC> modelIL;
	public:
		static VertexLayoutManager* GetInstance();
	private:
		VertexLayoutManager();
		~VertexLayoutManager() = default;
		VertexLayoutManager(const VertexLayoutManager&) = delete;
		const VertexLayoutManager& operator=(const VertexLayoutManager&) = delete;
	};
}