#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <vector>
#include "Vec2.h"
#include "Vec4.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace DX 
{
	class YDirectX
	{
	private:
		// DXGI�t�@�N�g���[
		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;
		// �f�o�C�X
		Microsoft::WRL::ComPtr<ID3D12Device> device_ = nullptr;
		// �R�}���h�A���P�[�^�[
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator_ = nullptr;
		// �R�}���h���X�g
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_ = nullptr;
		// �R�}���h�L���[
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue_ = nullptr;
		// �X���b�v�`�F�[��
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_ = nullptr;
		// RTV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;
		// �o�b�N�o�b�t�@ (RTV�{��)
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
		// DSV�p�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;
		// DSV�o�b�t�@ (DSV�{��)
		Microsoft::WRL::ComPtr<ID3D12Resource> dsvBuff_ = nullptr;
		// �t�F���X
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;
		// �t�F���X�ԍ�
		UINT64 fenceValue_ = 0;
	public:
		// ������
		bool Initialize(const HWND& hwnd, const Math::Vec2& size = { 1280, 720 });
		// �`��O����
		void PreDraw(const Math::Vec4& clearColor);
		// �`��㏈��
		void PostDraw();
	public:
		// �f�o�C�X�|�C���^
		ID3D12Device* Device() { return device_.Get(); }
		// �R�}���h���X�g�|�C���^
		ID3D12GraphicsCommandList* CommandList() { return cmdList_.Get(); }
	};
}