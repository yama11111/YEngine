/**
 * @file YDirectX.h
 * @brief DirectX12クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "GPUResource.h"
#include <dxgi1_6.h>
#include <vector>
#include <chrono>
#include "Vector2.h"
#include "Vector4.h"

namespace YDX 
{
	class YDirectX
	{
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="hwnd"> : ウィンドウハンドル</param>
		/// <param name="windowSize"> : ウィンドウサイズ</param>
		/// <returns>初期化に成功したか</returns>
		bool Initialize(const HWND& hwnd, const YMath::Vector2& windowSize = { 1280, 720 }); 
		
		/// <summary>
		/// 描画前準備
		/// </summary>
		/// <param name="clearColor"> : 画面クリア時の色</param>
		void PreDraw(const YMath::Vector4& clearColor);

		/// <summary>
		/// 描画後処理
		/// </summary>
		void PostDraw();
	
	public:

		/// <summary>
		/// DXGIファクトリーポインタ取得
		/// </summary>
		/// <returns>DXGIファクトリーポインタ</returns>
		IDXGIFactory7* DXGIFactoryPtr() { return dxgiFactory_.Get(); }

		/// <summary>
		/// デバイスポインタ取得
		/// </summary>
		/// <returns>デバイスポインタ</returns>
		ID3D12Device* DevicePtr() { return device_.Get(); }
		
		/// <summary>
		/// コマンドリストポインタ取得
		/// </summary>
		/// <returns>コマンドリストポインタ</returns>
		ID3D12GraphicsCommandList* CommandListPtr() { return cmdList_.Get(); }

		/// <summary>
		/// コマンドリストポインタ取得
		/// </summary>
		/// <returns>コマンドリストポインタ</returns>
		ID3D12CommandQueue* CommandQueuePtr() { return cmdQueue_.Get(); }
		
		/// <summary>
		/// バックバッファ数取得
		/// </summary>
		/// <returns>バックバッファ数</returns>
		size_t BackBufferCount() { return backBuffers_.size(); }
	
	public:
		
		/// <summary>
		/// FPS設定
		/// </summary>
		/// <param name="fps"> : FPS</param>
		static void SetFPS(const float fps);
	
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
		
		// 深度バッファ (DSV本体)
		ComPtr<ID3D12Resource> depthBuff_ = nullptr;
		

		// フェンス
		ComPtr<ID3D12Fence> fence_ = nullptr;
		
		// フェンス番号
		UINT64 fenceValue_ = 0;
		
		// FPS固定用時間記録
		std::chrono::steady_clock::time_point timeRef_;
	
	private:
		
		// 固定時fps (初期値 : 60fps)
		static std::chrono::microseconds MinTime_;
		
		// 調整用fps (初期値 : 65fps)
		static std::chrono::microseconds MinCheckTime_;
	
	};
}