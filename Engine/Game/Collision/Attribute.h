#pragma once
#include <cstdint>
#include "AttributeType.h"

namespace YGame
{
	class Attribute
	{	
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 属性追加
		/// </summary>
		/// <param name="attributeType"> : 属性</param>
		void Add(const AttributeType attributeType);
		
		/// <summary>
		/// 属性削除
		/// </summary>
		/// <param name="attributeType"> : 属性</param>
		void Remove(const AttributeType attributeType);

	public:

		/// <summary>
		/// 論理和演算
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>論理和</returns>
		bool OR(const Attribute& other) const;

		/// <summary>
		/// 論理和演算
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>論理和</returns>
		bool OR(const AttributeType other) const;

		/// <summary>
		/// 論理積演算
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>論理積</returns>
		bool AND(const Attribute& other) const;
	
		/// <summary>
		/// 論理積演算
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>論理積</returns>
		bool AND(const AttributeType other) const;

	public:

		Attribute() = default;
		
		~Attribute() = default;
	
	private:
		
		// 属性ビット
		uint32_t attributeBit_;
	
	private:

		/// <summary>
		/// ビット取得
		/// </summary>
		/// <returns> : ビット</returns>
		uint32_t Bit() const;
	
	};
}
