#pragma once
#include "BaseConstBuffer.h"

namespace YGame
{
	// 定数バッファ
	template <typename CBType>
	class ConstBufferObject final : 
		public BaseConstBuffer
	{

	public:

		// 定数バッファデータ
		CBType::Data data_{};
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		static ConstBufferObject* Create(const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const uint32_t rootParamIndex) override;

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		const std::string Tag() const override;

	public:

		virtual ~ConstBufferObject() = default;
	
	private:

		// マッピング用
		CBType::Data* map_ = nullptr;

	private:

		// 宣言、代入を禁止
		ConstBufferObject() = default;

		ConstBufferObject(const ConstBufferObject&) = delete;

		const ConstBufferObject& operator=(const ConstBufferObject&) = delete;

	};

	template<typename CBType>
	inline ConstBufferObject<CBType>* ConstBufferObject<CBType>::Create(const bool isMutable)
	{
		ConstBufferObject* newConstBuffer = new ConstBufferObject();

		newConstBuffer->CreateBuffer(sizeof(CBType::Data), (void**)&newConstBuffer->map_, isMutable);

		return newConstBuffer;
	}

	template<typename CBType>
	void ConstBufferObject<CBType>::SetDrawCommand(const uint32_t rootParamIndex) 
	{
		// 値を更新
		*map_ = data_;

		BaseConstBuffer::SetDrawCommand(rootParamIndex);
	}

	template<typename CBType>
	inline const std::string ConstBufferObject<CBType>::Tag() const
	{
		return CBType::Tag();
	}
}
