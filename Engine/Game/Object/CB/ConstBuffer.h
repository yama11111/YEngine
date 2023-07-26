#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	// 定数バッファ
	template <typename CBType>
	class ConstBuffer final : 
		public YDX::BaseConstBuffer
	{

	public:

		// 定数バッファデータ
		CBType::Data data_{};
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <returns>動的インスタンス</returns>
		static ConstBuffer* Create(const bool isMutable = true);

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="type">定数バッファタイプ</param>
		/// <returns>動的インスタンス</returns>
		static ConstBuffer* Create(const CBType& type, const bool isMutable = true);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const uint32_t rootParamIndex) override;

		/// <summary>
		/// 定数バッファタイプ名取得
		/// </summary>
		/// <returns>定数バッファタイプ名</returns>
		std::string TypeName() override;

	public:

		virtual ~ConstBuffer() = default;
	
	private:

		// マッピング用
		CBType::Data* map_ = nullptr;

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

	template<typename CBType>
	inline ConstBuffer<CBType>* ConstBuffer<CBType>::Create(const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->map_ = newConstBuffer->data_ = {};

		return newConstBuffer;
	}

	template<typename CBType>
	ConstBuffer<CBType>* ConstBuffer<CBType>::Create(const CBType& data, const bool isMutable)
	{
		ConstBuffer* newConstBuffer = new ConstBuffer();

		newConstBuffer->CreateBuffer(isMutable);

		*newConstBuffer->*map_ = newConstBuffer->data_ = data;

		return newConstBuffer;
	}

	template<typename CBType>
	void ConstBuffer<CBType>::SetDrawCommand(const uint32_t rootParamIndex) 
	{
		// 値を更新
		*map_ = data_;

		BaseConstBuffer::SetDrawCommand(rootParamIndex);
	}

	template<typename CBType>
	inline std::string ConstBuffer<CBType>::TypeName()
	{
		return CBType::TypeName();
	}

	template<typename CBType>
	size_t ConstBuffer<CBType>::SizeOfCBData()
	{
		return sizeof(CBType::Data);
	}

	template<typename CBType>
	void** ConstBuffer<CBType>::MapDataPtrPtr()
	{
		return (void**)&map_;
	}
}
