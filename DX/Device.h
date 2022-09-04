#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	class Device
	{
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> device = nullptr;
		D3D_FEATURE_LEVEL featureLevel{};
	public:
		bool Create();
		ID3D12Device* Get();
	public:
		static Device* GetInstance();
	private:
		Device() = default;
		~Device() = default;
		Device(const Device&) = delete;
		const Device& operator=(const Device&) = delete;
	};
}
