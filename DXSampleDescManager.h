#pragma once
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

class DXSampleDescManager
{
public:
	std::vector<D3D12_STATIC_SAMPLER_DESC> sd;
public:
	static DXSampleDescManager* GetInstance();
private:
	DXSampleDescManager();
	~DXSampleDescManager() = default;
	DXSampleDescManager(const DXSampleDescManager&) = delete;
	const DXSampleDescManager& operator=(const DXSampleDescManager&) = delete;
};
