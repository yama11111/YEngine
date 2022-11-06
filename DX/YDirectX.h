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
		// DXGIファクトリー
		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;
		// デバイス
		Microsoft::WRL::ComPtr<ID3D12Device> device_ = nullptr;
		// コマンドアロケーター
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator_ = nullptr;
		// コマンドリスト
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_ = nullptr;
		// コマンドキュー
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue_ = nullptr;
		// スワップチェーン
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_ = nullptr;
		// RTV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;
		// バックバッファ (RTV本体)
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
		// DSV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;
		// DSVバッファ (DSV本体)
		Microsoft::WRL::ComPtr<ID3D12Resource> dsvBuff_ = nullptr;
		// フェンス
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;
		// フェンス番号
		UINT64 fenceValue_ = 0;
	public:
		// 初期化
		bool Initialize(const HWND& hwnd, const Math::Vec2& size = { 1280, 720 });
		// 描画前準備
		void PreDraw(const Math::Vec4& clearColor);
		// 描画後処理
		void PostDraw();
	public:
		// デバイスポインタ
		ID3D12Device* Device() { return device_.Get(); }
		// コマンドリストポインタ
		ID3D12GraphicsCommandList* CommandList() { return cmdList_.Get(); }
	};
}