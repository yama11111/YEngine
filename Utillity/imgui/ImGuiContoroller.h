#pragma once
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

class ImGuiContoroller
{
private:
	// デスクリプターヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;
	// コマンドリストポインタ
	ID3D12GraphicsCommandList* pCommandList_ = nullptr;
public:
	struct InitStatus 
	{
		HWND* hwnd_; // ウィンドウハンドル
		ID3D12Device* pDevice_; // デバイス
		size_t backBufferCount_; // バックバッファの数
		ID3D12GraphicsCommandList* pCommandList_; // コマンドリスト
	};
public:
	// 初期化
	void Initialize(const InitStatus& state);
	// 受付開始
	void Begin();
	// 受付終了
	void End();
	// 描画
	void Draw();
	// 終了処理
	void Finalize();
};

