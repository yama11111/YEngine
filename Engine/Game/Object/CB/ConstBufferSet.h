#pragma once
#include "BaseConstBuffer.h"
#include <memory>

namespace YGame
{
	// 定数バッファ
	template<typename CBData>
	class ConstBufferSet final
	{

	public:

		// データ
		CBData data_;

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <returns>動的インスタンス</returns>
		static ConstBufferSet* Create(const bool isMutable = true);

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="data">定数バッファデータ</param>
		/// <returns>動的インスタンス</returns>
		static ConstBufferSet* Create(const CBData& data, const bool isMutable = true);

	public:

		/// <summary>
		/// 定数バッファ本体のポインタを取得
		/// </summary>
		/// <returns>定数バッファ本体のポインタ</returns>
		BaseConstBuffer* ConstBufferPtr();

	public:

		ConstBufferSet() = default;

		~ConstBufferSet() = default;

		// 譲渡 を 禁止
		ConstBufferSet(const ConstBufferSet&) = delete;

		const ConstBufferSet& operator=(const ConstBufferSet&) = delete;
	
	private:

		// 定数バッファ本体
		std::unique_ptr<BaseConstBuffer> cBuff_;
	};

	template<typename CBData>
	inline ConstBufferSet<CBData>* ConstBufferSet<CBData>::Create(const bool isMutable)
	{
		ConstBufferSet* newCB = new ConstBufferSet();

		// 定数バッファ本体を生成
		newCB->cBuff_.reset(BaseConstBuffer::Create<CBData>(&newCB->data_, isMutable));

		return newCB;
	}
	template<typename CBData>
	inline ConstBufferSet<CBData>* ConstBufferSet<CBData>::Create(const CBData& data, const bool isMutable)
	{
		ConstBufferSet* newCB = ConstBufferSet();

		// 定数バッファ本体を生成
		newCB->cBuff_.reset(BaseConstBuffer::Create<CBData>(&newCB->data_, isMutable));

		newCB->SetData(data);

		return newCB;
	}
	template<typename CBData>
	inline BaseConstBuffer* ConstBufferSet<CBData>::ConstBufferPtr()
	{
		return cBuff_.get();
	}
}
