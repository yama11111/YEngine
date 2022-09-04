#pragma once
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class SampleDescManager
	{
	public:
		std::vector<D3D12_STATIC_SAMPLER_DESC> sd;
	public:
		static SampleDescManager* GetInstance();
	private:
		SampleDescManager();
		~SampleDescManager() = default;
		SampleDescManager(const SampleDescManager&) = delete;
		const SampleDescManager& operator=(const SampleDescManager&) = delete;
	};
}
