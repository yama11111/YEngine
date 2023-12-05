#pragma once
#include <cstdint>

namespace YMath
{
	class BitFrag
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();
	
	public:

		/// <summary>
		/// フラグ立てる
		/// </summary>
		/// <param name="bitFrag"> : ビットフラグ</param>
		void SetFragTrue(const BitFrag bitFrag);

		/// <summary>
		/// フラグ立てる
		/// </summary>
		/// <typeparam name="BitType"> : ビットの種類</typeparam>
		/// <param name="bit"> : ビット</param>
		template <typename BitType>
		void SetFragTrue(const BitType bit)
		{
			bit_ |= static_cast<uint32_t>(bit);
		}

		/// <summary>
		/// フラグ下げる
		/// </summary>
		/// <param name="bitFrag"> : ビットフラグ</param>
		void SetFragFalse(const BitFrag bitFrag);

		/// <summary>
		/// フラグ下げる
		/// </summary>
		/// <typeparam name="BitType"> : ビットの種類</typeparam>
		/// <param name="bit"> : ビット</param>
		template <typename BitType>
		void SetFragFalse(const BitType bit)
		{
			bit_ &= ~static_cast<uint32_t>(bit);
		}
	
	public:

		/// <summary>
		/// 論理和演算
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>論理和</returns>
		bool OR(const BitFrag& other) const;

		/// <summary>
		/// 論理和演算
		/// </summary>
		/// <typeparam name="BitType"> : ビットの種類</typeparam>
		/// <param name="other"> : 相手</param>
		/// <returns>論理和</returns>
		template <typename BitType>
		bool OR(const BitType other) const
		{
			return bit_ | static_cast<uint32_t>(other);
		}

		/// <summary>
		/// 論理積演算
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>論理積</returns>
		bool AND(const BitFrag& other) const;

		/// <summary>
		/// 論理積演算
		/// </summary>
		/// <typeparam name="BitType"> : ビットの種類</typeparam>
		/// <param name="other"> : 相手</param>
		/// <returns>論理積</returns>
		template <typename BitType>
		bool AND(const BitType other) const
		{
			return bit_ & static_cast<uint32_t>(other);
		}

	public:

		BitFrag() = default;
		
		template <typename BitType>
		BitFrag(const BitType bit)
		{
			SetFragTrue(bit);
		}

		~BitFrag() = default;

	private:

		// ビットフラグ
		uint32_t bit_ = 0;

	private:

		/// <summary>
		/// ビット取得
		/// </summary>
		/// <returns> : ビット</returns>
		uint32_t Bit() const;

	};
}
