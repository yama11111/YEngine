#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace DX
{
	class GPUResource
	{
	private:
		// バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer_ = nullptr;
	public:
		// 生成用ステータス
		struct CreateStatus
		{
			// バッファ設定
			D3D12_HEAP_PROPERTIES heapProp_{};
			// リソース設定
			D3D12_RESOURCE_DESC resDesc_{};
		};
	public:
		// 生成
		void Create(const CreateStatus& state);
	public:
		// バッファポインタ
		ID3D12Resource* Get() { return buffer_.Get(); }
	private:
		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;
	public:
		// 静的メンバ初期化
		static void StaticInitialize(ID3D12Device* pDevice);
	};
}