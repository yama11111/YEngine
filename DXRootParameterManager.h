#pragma 
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

class DXRootParameterManager
{
public:
	std::vector<D3D12_ROOT_PARAMETER> rp;
private:
	UINT cbvNum = 0;
	UINT index = 0;
public:
	UINT PushBackCBV();
	UINT PushBackDescriptorTable(const D3D12_DESCRIPTOR_RANGE& descriptorRange);
public:
	static DXRootParameterManager* GetInstance();
private:
	DXRootParameterManager() = default;
	~DXRootParameterManager() = default;
	DXRootParameterManager(const DXRootParameterManager&) = delete;
	const DXRootParameterManager& operator=(const DXRootParameterManager&) = delete;
};
