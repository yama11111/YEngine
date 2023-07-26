#pragma once
#include "DescriptorHeap.h"
#include "GPUResource.h"
#include <cstdint>
#include <string>

namespace YDX
{
	class ConstBufferCommon
	{
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pDescHeap"> : デスクリプターヒープポインタ</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCmdList, YDX::DescriptorHeap* pDescHeap);

	protected:

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;

		// 静的デスクリプターヒープポインタ
		static YDX::DescriptorHeap* spDescHeap_;
	};

	class BaseConstBuffer : 
		protected ConstBufferCommon
	{

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		virtual void SetDrawCommand(const uint32_t rootParamIndex);

		/// <summary>
		/// 定数バッファタイプ名取得
		/// </summary>
		/// <returns>定数バッファタイプ名</returns>
		virtual std::string TypeName() = 0;

	public:

		BaseConstBuffer() = default;
	
		virtual ~BaseConstBuffer() = default;
	
	protected:

		// バッファ
		YDX::GPUResource buff_;

		// CBV設定
		D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc_{};
	
	protected:

		/// <summary>
		/// 定数バッファの生成 + マッピング
		/// </summary>
		/// <param name="isMutable">シーン遷移時クリアするか</param>
		void CreateBuffer(const bool isMutable);

		/// <summary>
		/// 定数バッファのサイズ取得
		/// </summary>
		/// <returns>定数バッファのサイズ</returns>
		virtual size_t SizeOfCBData() = 0;

		/// <summary>
		/// マッピング用データダブルポインタ取得
		/// </summary>
		/// <returns>マッピング用データダブルポインタ</returns>
		virtual void** MapDataPtrPtr() = 0;

	};
}
