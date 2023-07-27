#pragma once
#include "DescriptorHeap.h"
#include "GPUResource.h"
#include <cstdint>
#include <string>

namespace YGame
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

	// 基底定数バッファクラス
	class BaseConstBuffer : 
		protected ConstBufferCommon
	{

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		virtual void SetDrawCommand(const uint32_t rootParamIndex);
	
	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		virtual const std::string Tag() const = 0;

	public:

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
		/// <param name="dataSize"> : データサイズ</param>
		/// <param name="map"> : マップダブルポインタ</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		void CreateBuffer(const size_t dataSize, void** map, const bool isClearWhenTransition = true);

	protected:

		// 宣言を制限
		BaseConstBuffer() = default;
	
	private:

		// 代入を禁止
		BaseConstBuffer(const BaseConstBuffer&) = delete;

		const BaseConstBuffer& operator=(const BaseConstBuffer&) = delete;
	};
}
