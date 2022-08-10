#pragma 
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

class DXRootParameterManager
{
public:
	std::vector<D3D12_ROOT_PARAMETER> rp;
private:
	int cbvNum = 0;
public:
	int PushBackCBV();
	void PushBackDescTable(const D3D12_DESCRIPTOR_RANGE& descriptorRange);
public:
	static DXRootParameterManager* GetInstance();
private:
	DXRootParameterManager() = default;
	~DXRootParameterManager() = default;
	DXRootParameterManager(const DXRootParameterManager&) = delete;
	const DXRootParameterManager& operator=(const DXRootParameterManager&) = delete;
};
