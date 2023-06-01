#pragma once
#include "GPUResource.h"
#include <dxgi1_6.h>
#include <vector>
#include <chrono>
#include "Vector2.h"
#include "Vector4.h"

#pragma comment(lib, "dxgi.lib")

namespace YDX 
{
	class YDirectX
	{
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="hwnd"> : �E�B���h�E�n���h��</param>
		/// <param name="windowSize"> : �E�B���h�E�T�C�Y</param>
		/// <returns>�������ɐ���������</returns>
		bool Initialize(const HWND& hwnd, const YMath::Vector2& windowSize = { 1280, 720 }); 
		
		/// <summary>
		/// �`��O����
		/// </summary>
		/// <param name="clearColor"> : ��ʃN���A���̐F</param>
		void PreDraw(const YMath::Vector4& clearColor);

		/// <summary>
		/// �`��㏈��
		/// </summary>
		void PostDraw();
	
	public:

		/// <summary>
		/// DXGI�t�@�N�g���[�|�C���^�擾
		/// </summary>
		/// <returns>DXGI�t�@�N�g���[�|�C���^</returns>
		IDXGIFactory7* DXGIFactoryPtr() { return dxgiFactory_.Get(); }

		/// <summary>
		/// �f�o�C�X�|�C���^�擾
		/// </summary>
		/// <returns>�f�o�C�X�|�C���^</returns>
		ID3D12Device* DevicePtr() { return device_.Get(); }
		
		/// <summary>
		/// �R�}���h���X�g�|�C���^�擾
		/// </summary>
		/// <returns>�R�}���h���X�g�|�C���^</returns>
		ID3D12GraphicsCommandList* CommandListPtr() { return cmdList_.Get(); }

		/// <summary>
		/// �R�}���h���X�g�|�C���^�擾
		/// </summary>
		/// <returns>�R�}���h���X�g�|�C���^</returns>
		ID3D12CommandQueue* CommandQueuePtr() { return cmdQueue_.Get(); }
		
		/// <summary>
		/// �o�b�N�o�b�t�@���擾
		/// </summary>
		/// <returns>�o�b�N�o�b�t�@��</returns>
		size_t BackBufferCount() { return backBuffers_.size(); }
	
	public:
		
		/// <summary>
		/// FPS�ݒ�
		/// </summary>
		/// <param name="fps"> : FPS</param>
		static void SetFPS(const float fps);
	
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
		
		// �[�x�o�b�t�@ (DSV�{��)
		ComPtr<ID3D12Resource> depthBuff_ = nullptr;
		

		// �t�F���X
		ComPtr<ID3D12Fence> fence_ = nullptr;
		
		// �t�F���X�ԍ�
		UINT64 fenceValue_ = 0;
		
		// FPS�Œ�p���ԋL�^
		std::chrono::steady_clock::time_point timeRef_;
	
	private:
		
		// �Œ莞fps (�����l : 60fps)
		static std::chrono::microseconds MinTime_;
		
		// �����pfps (�����l : 65fps)
		static std::chrono::microseconds MinCheckTime_;
	
	};
}