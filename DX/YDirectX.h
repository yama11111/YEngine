#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <vector>
#include <chrono>
#include "Vec2.h"
#include "Vec4.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace DX 
{
	class YDirectX
	{
	private:
		// ComPtr�p�G�C���A�X�e���v���[�g
		template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	private:
		// DXGI�t�@�N�g���[
		ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;
		// �f�o�C�X
		ComPtr<ID3D12Device> device_ = nullptr;
		// �R�}���h�A���P�[�^�[
		ComPtr<ID3D12CommandAllocator> cmdAllocator_ = nullptr;
		// �R�}���h���X�g
		ComPtr<ID3D12GraphicsCommandList> cmdList_ = nullptr;
		// �R�}���h�L���[
		ComPtr<ID3D12CommandQueue> cmdQueue_ = nullptr;
		// �X���b�v�`�F�[��
		ComPtr<IDXGISwapChain4> swapChain_ = nullptr;
		// RTV�p�q�[�v
		ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;
		// �o�b�N�o�b�t�@ (RTV�{��)
		std::vector<ComPtr<ID3D12Resource>> backBuffers_;
		// DSV�p�q�[�v
		ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;
		// DSV�o�b�t�@ (DSV�{��)
		ComPtr<ID3D12Resource> dsvBuff_ = nullptr;
		// �t�F���X
		ComPtr<ID3D12Fence> fence_ = nullptr;
		// �t�F���X�ԍ�
		UINT64 fenceValue_ = 0;
		// FPS�Œ�p���ԋL�^
		std::chrono::steady_clock::time_point timeRef_;
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
	private:
		// �Œ莞fps (�����l : 60fps)
		static std::chrono::microseconds MinTime_;
		// �����pfps (�����l : 65fps)
		static std::chrono::microseconds MinCheckTime_;
	public:
		static void SetFPS(const float fps);
	};
}