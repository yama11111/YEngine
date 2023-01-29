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
		static ID3D12GraphicsCommandList* pCommandList_;
		// 静的デスクリプターヒープクラス
		static DescriptorHeap* pDescHeap_;
	public:
		// 静的初期化設定
		struct StaticInitStatus
		{
			ID3D12GraphicsCommandList* pCommandList_;
			DescriptorHeap* pDescHeap_;
		};
	public:
		// 静的初期化
		static void StaticInitialize(const StaticInitStatus& state);
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
		// 定数バッファの生成 + マッピング
		void Create();
		// 描画前コマンド
		void SetDrawCommand(const UINT rootParamIndex);
	};
}