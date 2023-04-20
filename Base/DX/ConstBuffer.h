#pragma once
#include "GPUResource.h"
#include "DescriptorHeap.h"

namespace YDX
{
	// 定数バッファコモンクラス
	class ConstBufferCommon 
	{
	protected:
		
		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* pCmdList_;
		
		// 静的デスクリプターヒープクラス
		static DescriptorHeap* pDescHeap_;
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pDescHeap"> : デスクリプターヒープポインタ</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCmdList, DescriptorHeap* pDescHeap);
	
	};


	// 定数バッファ
	template <typename T>
	class ConstBuffer : private ConstBufferCommon
	{
	public:

		// マッピング用
		T* map_ = nullptr;
	
	private:
		
		// バッファ
		GPUResource rsc_;
		
		// CBV設定
		D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc_{};
	
	public:
		
		/// <summary>
		/// 定数バッファの生成 + マッピング
		/// </summary>
		/// <param name="isMutable"> : リセットするか</param>
		void Create(const bool isMutable);

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const UINT rootParamIndex);
	
	};
}