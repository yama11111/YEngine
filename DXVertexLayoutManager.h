#pragma once
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

class DXVertexLayoutManager
{
public:
	// ���_���C�A�E�g
	std::vector<D3D12_INPUT_ELEMENT_DESC> spriteIL;
	// ���_���C�A�E�g
	std::vector<D3D12_INPUT_ELEMENT_DESC> modelIL;
public:
	static DXVertexLayoutManager* GetInstance();
private:
	DXVertexLayoutManager();
	~DXVertexLayoutManager() = default;
	DXVertexLayoutManager(const DXVertexLayoutManager&) = delete;
	const DXVertexLayoutManager& operator=(const DXVertexLayoutManager&) = delete;
};

