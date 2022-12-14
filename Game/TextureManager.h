#pragma once
#include "GPUResource.h"
#include "SRVHeap.h"
#include "Vec4.h"
#include <vector>
#include <string>

namespace Game
{
	// テクスチャ構造体
	struct Texture 
	{
		// テクスチャバッファ
		DX::GPUResource buff_;
		// SRV先頭ハンドル (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		// SRV先頭ハンドル (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
		// テクスチャファイル名
		std::string fileName_;
	};

	class TextureManager
	{
	private:
		// テクスチャ用vector配列
		std::vector<Texture> texs_;
		// デスクリプタテーブル生成時番号保存用
		UINT rpIndex_ = 0;
	public:
		// テクスチャ生成
		UINT CreateTex(const Math::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// テクスチャ読み込み
		UINT Load(const std::string& texFileName, const bool mipMap = true);
		// テクスチャ読み込み(モデル用)
		UINT Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap = true);
		// テクスチャ描画前コマンド 
		void SetDrawCommand(const UINT texIndex);
	public:
		// デスクリプターテーブル番号設定
		void SetRootParameterIndex(UINT rpIndex) { rpIndex_ = rpIndex; }
		// テクスチャバッファ取得
		ID3D12Resource* TextureBuffer(const UINT texIndex);
	private:
		// テクスチャ設定
		void SetTexture(Texture& tex, D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc);
		// 拡張子取得
		static std::string FileExtension(const std::string path);
	private:
		// 横方向ピクセル数
		static const size_t textureWidth = 1;
		// 縦方向ピクセル数
		static const size_t textureHeight = 1;
		// 配列の要素数
		static const size_t imageDataCount = textureWidth * textureHeight;
	private:
		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
		// 静的シェーダーリソースヒープクラス
		static DX::SRVHeap* pSrvHeap_;
	public:
		// 静的初期化
		static void StaticInitialize(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCommandList, DX::SRVHeap* pSrvHeap);
	};
}

