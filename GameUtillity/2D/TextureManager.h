#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"
#include "Vector4.h"
#include <vector>
#include <string>

namespace YGame
{
	// テクスチャ構造体
	struct Texture 
	{
		// テクスチャバッファ
		YDX::GPUResource buff_;
		// SRVハンドル (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		// SRVハンドル (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
		// テクスチャファイル名
		std::string fileName_;
	};

	class TextureManager
	{
	private:
		// テクスチャ用vector配列
		std::vector<Texture> texs_;
	public:
		// テクスチャ生成
		UINT CreateTex(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
		// テクスチャ読み込み
		UINT Load(const std::string& texFileName, const bool mipMap = true);
		// テクスチャ読み込み(モデル用)
		UINT Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap = true);
		// テクスチャ描画前コマンド 
		void SetDrawCommand(const UINT rootParamIndex, const UINT texIndex);
	public:
		// テクスチャバッファ取得
		ID3D12Resource* TextureBuffer(const UINT texIndex);
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
		// 静的デスクリプターヒープクラス
		static YDX::DescriptorHeap* pDescHeap_;
	public:
		// 静的初期化設定
		struct StaticInitStatus
		{
			ID3D12Device* pDevice_;
			ID3D12GraphicsCommandList* pCmdList_;
			YDX::DescriptorHeap* pDescHeap_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
	};
}

