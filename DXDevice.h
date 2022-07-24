#pragma once
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

class DXDevice
{
private:
	D3D_FEATURE_LEVEL featureLevel{};
	ID3D12Device* device = nullptr;
public:
	bool Create();
	ID3D12Device* Device();
public:
	static DXDevice* GetInstance();
private:
	DXDevice() = default;
	~DXDevice() = default;
	DXDevice(const DXDevice&) = delete;
	const DXDevice& operator=(const DXDevice&) = delete;
};

