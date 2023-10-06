#pragma once
#include "DescriptorHeap.h"
#include <windows.h>
#include <dxgi1_6.h>

#pragma comment(lib, "dxgi.lib")

class ImGuiManager
{
private:
	// コマンドリストポインタ
	ID3D12GraphicsCommandList* pCmdList_ = nullptr;
	// デスクリプターヒープ
	YDX::DescriptorHeap* pDescHeap_ = nullptr;
public:
	struct InitStatus 
	{
		HWND hwnd_; // ウィンドウハンドル
		ID3D12Device* pDevice_; // デバイス
		ID3D12GraphicsCommandList* pCmdList_; // コマンドリスト
		YDX::DescriptorHeap* pDescHeap_; // デスクリプターヒープ
		size_t backBufferCount_; // バックバッファの数
	};
public:
	// 初期化
	void Initialize(const InitStatus& state);
	// 終了処理
	void Finalize();
	// 受付開始
	void Begin();
	// 受付終了
	void End();
	// 描画
	void Draw();
};

