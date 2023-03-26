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

	// テクスチャマネージャーコモンクラス
	class TextureManagerCommon 
	{
	protected:
		// 横方向ピクセル数 (テクスチャ生成用)
		static const size_t textureWidth = 1;
		// 縦方向ピクセル数 (テクスチャ生成用)
		static const size_t textureHeight = 1;
		// 配列の要素数 (テクスチャ生成用)
		static const size_t imageDataCount = textureWidth * textureHeight;
	protected:
		// 静的デバイスポインタ
		static ID3D12Device* pDevice_;
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
		// 静的デスクリプターヒープ
		static YDX::DescriptorHeap* pDescHeap_;
	public:
		// 静的初期化設定
		struct StaticInitStatus
		{
			ID3D12Device* pDevice_; // デバイスポインタ
			ID3D12GraphicsCommandList* pCmdList_; // コマンドリストポインタ
			YDX::DescriptorHeap* pDescHeap_; // デスクリプターヒープ
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
	};

	// テクスチャマネージャークラス (シングルトン)
	class TextureManager : private TextureManagerCommon
	{
	private:
		// テクスチャ用vector配列
		std::vector<Texture> texs_;
	public:
		/// <summary>
		/// テクスチャ生成
		/// </summary>
		/// <param name="color"> : 色 (0.0 ~ 1.0)</param>
		/// <returns>テクスチャ番号</returns>
		UINT CreateTex(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
		/// <summary>
		/// テクスチャ読み込み
		/// </summary>
		/// <param name="texFileName"> : テクスチャファイル名</param>
		/// <param name="mipMap"> : ミップマップを生成するか</param>
		/// <returns>テクスチャ番号</returns>
		UINT Load(const std::string& texFileName, const bool mipMap = true);
		/// <summary>
		/// テクスチャ読み込み (ディレクトリパス指定ver)
		/// </summary>
		/// <param name="directoryPath"> : ディレクトリパス名</param>
		/// <param name="texFileName"> : テクスチャファイル名</param>
		/// <param name="mipMap"> : ミップマップを生成するか</param>
		/// <returns>テクスチャ番号</returns>
		UINT Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap = true);
		/// <summary>
		/// テクスチャ描画前コマンド (シェーダーに転送)
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		/// <param name="texIndex"> : テクスチャ番号</param>
		void SetDrawCommand(const UINT rootParamIndex, const UINT texIndex);
	public:
		/// <summary>
		/// テクスチャバッファ取得
		/// </summary>
		/// <param name="texIndex"> : テクスチャ番号</param>
		/// <returns>対応するテクスチャのバッファ</returns>
		ID3D12Resource* TextureBuffer(const UINT texIndex);
	public:
		// インスタンス取得
		static TextureManager* GetInstance();
	private:
		TextureManager() = default;
		~TextureManager() = default;
		TextureManager(const TextureManager&) = delete;
		const TextureManager& operator=(const TextureManager&) = delete;
	};
}

