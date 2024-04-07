/**
 * @file GPUResource.h
 * @brief GPUリソースクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include <d3d12.h>
#include <wrl.h>

namespace YDX
{
	class GPUResource final
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pHeapProp"> : バッファ設定ポインタ</param>
		/// <param name="pResourceDesc"> : リソース設定ポインタ</param>
		/// <param name="resourceState"> : リソースステート</param>
		/// <param name="pClearValue"> : クリア値ポインタ</param>
		void Create(
			const D3D12_HEAP_PROPERTIES* pHeapProp,
			const D3D12_RESOURCE_DESC* pResourceDesc,
			const D3D12_RESOURCE_STATES resourceState = D3D12_RESOURCE_STATE_GENERIC_READ,
			const D3D12_CLEAR_VALUE* pClearValue = nullptr);

	public:

		/// <summary>
		/// バッファポインタ取得
		/// </summary>
		/// <returns>バッファポインタ</returns>
		ID3D12Resource* Get() { return buffer_.Get(); }

		/// <summary>
		/// バッファポインタポインタ取得
		/// </summary>
		/// <returns>バッファポインタポインタ</returns>
		ID3D12Resource** GetAddressOf() { return buffer_.GetAddressOf(); }

	public:

		GPUResource() = default;
		
		~GPUResource() = default;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		static void StaticInitialize(ID3D12Device* pDevice);
	
	private:
		
		// バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer_ = nullptr;

	private:
		
		// 静的デバイスポインタ
		static ID3D12Device* spDevice_;
	
	};
}