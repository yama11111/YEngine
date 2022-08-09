#pragma once
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

class DXVertexLayoutManager
{
public:
	// 頂点レイアウト
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
public:
	DXVertexLayoutManager();
};

