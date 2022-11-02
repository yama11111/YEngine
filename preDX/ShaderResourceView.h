#pragma once
#include "Utility/DescriptorHeap.h"
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class ShaderResourceView
	{
	public:
		UINT rpIndex = 0;
	private:
		Utility::DescriptorHeap srv;
		D3D12_CPU_DESCRIPTOR_HANDLE handle;
		UINT incrementSize = 0;
		UINT index = 0;
		static ID3D12GraphicsCommandList* pCmdList;
		D3D12_DESCRIPTOR_RANGE descriptorRange;
	public:
		UINT SetSRV(ID3D12Resource* texBuff, D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc);
		void SetDescriptorHeaps();
		void SetRootParameter();
		void SetCommand(const UINT index);
	public:
		static void StaticInit(ID3D12GraphicsCommandList* pCommandList);
		static ShaderResourceView* GetInstance();
	private:
		ShaderResourceView();
		~ShaderResourceView() = default;
		ShaderResourceView(const ShaderResourceView&) = delete;
		const ShaderResourceView& operator=(const ShaderResourceView&) = delete;
	};
}
