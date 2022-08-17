#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXCommandList
{
private:
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
public:
	void Create();
	void ClearAndPrepare();
	void CrearRTV(D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle);
	void CrearDSV(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);
	ID3D12GraphicsCommandList* List();
	ID3D12CommandAllocator* Allocator();
public:
	static DXCommandList* GetInstance();
private:
	DXCommandList() = default;
	~DXCommandList() = default;
	DXCommandList(const DXCommandList&) = delete;
	const DXCommandList& operator=(const DXCommandList&) = delete;
};

