#pragma once
#include "GPUResource.h"
#include <vector>
#include "Vec4.h"

namespace DX
{
	// テクスチャ構造体
	struct Texture 
	{
		// テクスチャバッファ
		GPUResource buff_;
		// SRV先頭ハンドル (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
	};

	class TextureManager
	{
	private:
		// SRV用ヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_ = nullptr;
		// SRV先頭ハンドル (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		// テクスチャ用vector配列
		std::vector<Texture> texs_;
		// デスクリプタテーブル生成時番号保存用
		UINT rpIndex_ = 0;
	public:
		// 初期化
		void Initialize();
		// テクスチャ生成
		UINT CreateTex(const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// テクスチャロード
		UINT Load(const wchar_t* fileName, const bool mipMap = true);
		// SRV描画前コマンド (最初に一回)
		void SetSRVDrawCommand();
		// テクスチャ描画前コマンド 
		void SetDrawCommand(const UINT texIndex);
	private:
		// テクスチャ設定
		void SetTexture(Texture& tex, D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc);
	public:
		// デスクリプターテーブル番号設定
		void SetRootParameterIndex(UINT rpIndex) { rpIndex_ = rpIndex; }
	private:
		// 最大テクスチャ数
		static const UINT MaxSRVCount_ = 2056;
		// 横方向ピクセル数
		static const size_t textureWidth = 1;
		// 縦方向ピクセル数
		static const size_t textureHeight = 1;
		// 配列の要素数
		static const size_t imageDataCount = textureWidth * textureHeight;
		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
	public:
		// 静的初期化
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList);
	};
}

