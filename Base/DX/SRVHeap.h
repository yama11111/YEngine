#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	class SRVHeap
	{
	private:
		// SRV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;
	public:
		// ヒープ生成
		void Create();
		// SRV描画前コマンド (最初に一回)
		void SetDrawCommand();
	public:
		D3D12_CPU_DESCRIPTOR_HANDLE CPUHandleStart() { return srvHeap_->GetCPUDescriptorHandleForHeapStart(); }
		D3D12_GPU_DESCRIPTOR_HANDLE GPUHandleStart() { return srvHeap_->GetGPUDescriptorHandleForHeapStart(); }
	private:
		// 最大テクスチャ数
		static const UINT MaxSRVCount_ = 2056;
	private:
		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// 静的初期化
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);
	};
}
