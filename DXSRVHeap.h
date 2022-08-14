#pragma once
#include "DXDescriptorHeap.h"
#include "DXCommandList.h"

class DXSRVHeap
{
public:
	UINT rpIndex = 0;
private:
	DXDescriptorHeap srvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;
	UINT incrementSize = 0;
	int index = 0;
	DXCommandList* cmdList = nullptr;
public:
	int SetSRV(ID3D12Resource* texBuff, D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc);
	void SetCommand();
	void SetRootParameter(const int index);
public:
	static DXSRVHeap* GetInstance();
private:
	DXSRVHeap();
	~DXSRVHeap() = default;
	DXSRVHeap(const DXSRVHeap&) = delete;
	const DXSRVHeap& operator=(const DXSRVHeap&) = delete;
};

