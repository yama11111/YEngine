/**
 * @file ImGuiManager.h
 * @brief ImGui管理クラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "DescriptorHeap.h"
#include <windows.h>
#include <dxgi1_6.h>

#pragma comment(lib, "dxgi.lib")

class ImGuiManager
{

public:
	
	// 初期化ステータス
	struct InitStatus 
	{
		HWND hwnd_; // ウィンドウハンドル
		ID3D12Device* pDevice_; // デバイス
		ID3D12GraphicsCommandList* pCmdList_; // コマンドリスト
		YDX::DescriptorHeap* pDescHeap_; // デスクリプターヒープ
		size_t backBufferCount_; // バックバッファの数
	};

public:
	
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="state"> : 初期化ステータス</param>
	void Initialize(const InitStatus& state);
	
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	
	/// <summary>
	/// 受付開始
	/// </summary>
	void Begin();
	
	/// <summary>
	/// 受付終了
	/// </summary>
	void End();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	
	// コマンドリストポインタ
	ID3D12GraphicsCommandList* pCmdList_ = nullptr;
	
	// デスクリプターヒープ
	YDX::DescriptorHeap* pDescHeap_ = nullptr;
};

