#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
namespace YDX
{
	class DescriptorHeap
	{
	private:
		// デスクリプターヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;
		// SRV 数
		UINT srvCount_ = 0;
		// UAV 数
		UINT uavCount_ = 0;
		// CBV 数
		UINT cbvCount_ = 0;
	public:
		// 初期化
		void Initialize();
		// SRV 生成
		void CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc, 
			D3D12_CPU_DESCRIPTOR_HANDLE& cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE& gpuHandle);
		// UAV 生成
		void CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc);
		// CBV 生成
		void CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc);
		// 描画前コマンド (最初に一回)
		void SetDrawCommand();
	public:
		// ポインタ取得
		ID3D12DescriptorHeap* Get() const { return descriptorHeap_.Get(); }
	private:
		// 最大 SRV 数
		static const UINT MaxSRVCount_ = 262144;
		// 最大 UAV 数
		static const UINT MaxUAVCount_ = 262144;
		// 最大 CBV 数
		static const UINT MaxCBVCount_ = 262144;
	private:
		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCommandList_;
	public:
		// 静的初期化設定
		struct StaticInitStatus
		{
			ID3D12Device* pDevice_;
			ID3D12GraphicsCommandList* pCommandList_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
	};
}
