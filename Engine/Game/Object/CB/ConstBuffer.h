#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	// 定数バッファ
	template <typename CBData>
	class ConstBuffer final : 
		public YDX::BaseConstBuffer
	{

	public:

		// 定数バッファデータ
		CBData data_{};
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <returns>動的インスタンス</returns>
		static ConstBuffer* Create(const bool isMutable = true);

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="data">定数バッファデータ</param>
		/// <returns>動的インスタンス</returns>
		static ConstBuffer* Create(const CBData& data, const bool isMutable = true);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const uint32_t rootParamIndex) override;

	public:

		virtual ~ConstBuffer() = default;
	
	private:

		// マッピング用
		CBData* map_ = nullptr;

	private:

		/// <summary>
		/// 定数バッファのサイズ取得
		/// </summary>
		/// <returns>定数バッファのサイズ</returns>
		size_t SizeOfCBData() override;

		/// <summary>
		/// マッピング用データダブルポインタ取得
		/// </summary>
		/// <returns>マッピング用データダブルポインタ</returns>
		void** MapDataPtrPtr() override;

	private:

		ConstBuffer() = default;

	};

	template<typename CBData>
	inline ConstBuffer<CBData>* ConstBuffer<CBData>::Create(const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->map_ = newConstBuffer->data_ = {};

		return newConstBuffer;
	}

	template<typename CBData>
	ConstBuffer<CBData>* ConstBuffer<CBData>::Create(const CBData& data, const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->*map_ = newConstBuffer->data_ = data;

		return newConstBuffer;
	}

	template<typename CBData>
	void ConstBuffer<CBData>::SetDrawCommand(const uint32_t rootParamIndex) 
	{
		// 値を更新
		*map_ = data_;

		// 定数バッファビュー設定コマンド
		spCmdList_->SetGraphicsRootConstantBufferView(static_cast<UINT>(rootParamIndex), viewDesc_.BufferLocation);
	}

	template<typename CBData>
	size_t ConstBuffer<CBData>::SizeOfCBData()
	{
		return sizeof(CBData);
	}

	template<typename CBData>
	void** ConstBuffer<CBData>::MapDataPtrPtr()
	{
		return (void**)&map_;
	}
}
