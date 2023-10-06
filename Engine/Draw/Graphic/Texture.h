#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"
#include "Vector4.h"
#include <vector>
#include <string>
#include <memory>

namespace YGame
{
	// テクスチャ
	class Texture
	{
		
	private:
		
		// テクスチャバッファ
		YDX::GPUResource buff_;
		
		// SRVハンドル (CPU)
		D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
		
		// SRVハンドル (GPU)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
	
		// テクスチャファイル名
		std::string fileName_;

	private:
		
		// 静的テクスチャ格納用vector配列
		static std::vector<std::unique_ptr<Texture>> sTexs_;

	public:
		
		/// <summary>
		/// テクスチャ生成
		/// </summary>
		/// <param name="color"> : 色 (0.0 ~ 1.0)</param>
		/// <returns>テクスチャポインタ</returns>
		static Texture* Create(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });

		/// <summary>
		/// レンダーテクスチャ生成
		/// </summary>
		/// <returns>テクスチャポインタ</returns>
		static Texture* CreateRender();

		/// <summary>
		/// テクスチャ読み込み
		/// </summary>
		/// <param name="texFileName"> : テクスチャファイル名</param>
		/// <param name="mipMap"> : ミップマップを生成するか</param>
		/// <returns>テクスチャポインタ</returns>
		static Texture* Load(const std::string& texFileName, const bool mipMap = true);

		/// <summary>
		/// テクスチャ読み込み (ディレクトリパス指定ver)
		/// </summary>
		/// <param name="directoryPath"> : ディレクトリパス名</param>
		/// <param name="texFileName"> : テクスチャファイル名</param>
		/// <param name="mipMap"> : ミップマップを生成するか</param>
		/// <returns>テクスチャポインタ</returns>
		static Texture* Load(const std::string& directoryPath, const std::string texFileName, const bool mipMap = true);

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// 描画コマンド (シェーダーに転送)
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const UINT rootParamIndex);
	
		/// <summary>
		/// テクスチャバッファ取得
		/// </summary>
		ID3D12Resource* Buffer();

	public:
		
		// コモンクラス
		class Common
		{
		public:

			// 静的デバイスポインタ
			static ID3D12Device* spDevice_;
			
			// 静的コマンドリストポインタ
			static ID3D12GraphicsCommandList* spCmdList_;
			
			// 静的デスクリプターヒープ
			static YDX::DescriptorHeap* spDescHeap_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			/// <param name="pDevice"> : デバイスポインタ</param>
			/// <param name="pCmdList"> : コマンドリストポインタ</param>
			/// <param name="pDescHeap"> : デスクリプターヒープポインタ</param>
			static void StaticInitialize(
				ID3D12Device* pDevice, 
				ID3D12GraphicsCommandList* pCmdList, 
				YDX::DescriptorHeap* pDescHeap);

		public:

			Common() = default;

			~Common() = default;

		};

	public:

		Texture() = default;

		~Texture() = default;
	};
}

