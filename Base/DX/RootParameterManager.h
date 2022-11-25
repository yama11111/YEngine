#pragma once
#include <d3d12.h>
#include <vector>

#pragma comment(lib, "d3d12.lib")

namespace DX 
{
	class RootParameterManager
	{
	private:
		// ルートパラメーター用vector配列
		std::vector<D3D12_ROOT_PARAMETER> rps_;
		// CBVカウント用
		UINT cbvIndex_ = 0;
		// デスクリプタレンジの設定
		D3D12_DESCRIPTOR_RANGE descriptorRange_{};
	public:
		// 定数バッファ挿入 (戻り値 : ルートパラメータ番号)
		UINT PushBackCBV();
		// テクスチャレジスタ挿入 (戻り値 : ルートパラメータ番号)
		UINT PushBackTR();
		// デスクリプターヒープ挿入 (戻り値 : ルートパラメータ番号)
		UINT PushBackDescriptorTable(const D3D12_DESCRIPTOR_RANGE& descriptorRange);
	public:
		// ルートパラメーター
		std::vector<D3D12_ROOT_PARAMETER>* Get() { return &rps_; }
	};
}
