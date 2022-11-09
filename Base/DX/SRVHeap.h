#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	class SRVHeap
	{
	private:
		// SRV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;
	public:
		// �q�[�v����
		void Create();
		// SRV�`��O�R�}���h (�ŏ��Ɉ��)
		void SetDrawCommand();
	public:
		D3D12_CPU_DESCRIPTOR_HANDLE CPUHandleStart() { return srvHeap_->GetCPUDescriptorHandleForHeapStart(); }
		D3D12_GPU_DESCRIPTOR_HANDLE GPUHandleStart() { return srvHeap_->GetGPUDescriptorHandleForHeapStart(); }
	private:
		// �ő�e�N�X�`����
		static const UINT MaxSRVCount_ = 2056;
	private:
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* pDevice_;
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// �ÓI������
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);
	};
}
