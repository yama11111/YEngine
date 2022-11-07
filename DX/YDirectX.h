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
		// ComPtr用エイリアステンプレート
		template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	private:
		// DXGIファクトリー
		ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;
		// デバイス
		ComPtr<ID3D12Device> device_ = nullptr;
		// コマンドアロケーター
		ComPtr<ID3D12CommandAllocator> cmdAllocator_ = nullptr;
		// コマンドリスト
		ComPtr<ID3D12GraphicsCommandList> cmdList_ = nullptr;
		// コマンドキュー
		ComPtr<ID3D12CommandQueue> cmdQueue_ = nullptr;
		// スワップチェーン
		ComPtr<IDXGISwapChain4> swapChain_ = nullptr;
		// RTV用ヒープ
		ComPtr<ID3D12DescriptorHeap> rtvHeap_ = nullptr;
		// バックバッファ (RTV本体)
		std::vector<ComPtr<ID3D12Resource>> backBuffers_;
		// DSV用ヒープ
		ComPtr<ID3D12DescriptorHeap> dsvHeap_ = nullptr;
		// DSVバッファ (DSV本体)
		ComPtr<ID3D12Resource> dsvBuff_ = nullptr;
		// フェンス
		ComPtr<ID3D12Fence> fence_ = nullptr;
		// フェンス番号
		UINT64 fenceValue_ = 0;
		// FPS固定用時間記録
		std::chrono::steady_clock::time_point timeRef_;
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
	private:
		// 固定時fps (初期値 : 60fps)
		static std::chrono::microseconds MinTime_;
		// 調整用fps (初期値 : 65fps)
		static std::chrono::microseconds MinCheckTime_;
	public:
		static void SetFPS(const float fps);
	};
}