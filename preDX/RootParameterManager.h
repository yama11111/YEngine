#pragma 
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class RootParameterManager
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
		static RootParameterManager* GetInstance();
	private:
		RootParameterManager() = default;
		~RootParameterManager() = default;
		RootParameterManager(const RootParameterManager&) = delete;
		const RootParameterManager& operator=(const RootParameterManager&) = delete;
	};
}