#pragma once
#include "DescriptorHeap.h"

namespace YDX
{
	// 定数バッファコモンクラス
	class ConstBufferCommon
	{

	protected:

		// 静的コマンドリストポインタ
		static ID3D12GraphicsCommandList* spCmdList_;

		// 静的デスクリプターヒープポインタ
		static DescriptorHeap* spDescHeap_;

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="pDevice"> : デバイスポインタ</param>
		/// <param name="pDescHeap"> : デスクリプターヒープポインタ</param>
		static void StaticInitialize(ID3D12GraphicsCommandList* pCmdList, DescriptorHeap* pDescHeap);

	};
}
