#pragma once

namespace YMath
{
	// イージングクラス
	template<typename T>
	class Ease
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="start"> : 初期値</param>
		/// <param name="end"> : 最終値</param>
		/// <param name="exponent"> : 指数(緩急)</param>
		void Initialize(const T& start, const T& end, const float exponent);
	
	public:
		
		/// <summary>
		/// イーズイン
		/// (だんだん早く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <returns>その割合の時の値</returns>
		T In(const float ratio) const;
		
		/// <summary>
		/// イーズアウト
		/// (だんだん遅く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <returns>その割合の時の値</returns>
		T Out(const float ratio) const;

		/// <summary>
		/// イーズインアウト
		/// (だんだん早く → だんだん遅く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <param name="controlPoint"> : 制御点</param>
		/// <returns>その割合の時の値</returns>
		T InOut(const float ratio, const float controlPoint = 0.5f) const;

		/// <summary>
		/// イーズアウトイン
		/// (だんだん遅く → だんだん早く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <param name="controlPoint"> : 制御点</param>
		/// <returns>その割合の時の値</returns>
		T OutIn(const float ratio, const float controlPoint = 0.5f) const;
	
	public:
		
		/// <summary>
		/// 初期値設定
		/// </summary>
		/// <param name="start"> : 初期値</param>
		void SetStart(const T& start) { start_ = start; };

		/// <summary>
		/// 最終値設定
		/// </summary>
		/// <param name="end"> : 最終値</param>
		void SetEnd(const T& end) { end_ = end; };

		/// <summary>
		/// 緩急設定
		/// </summary>
		/// <param name="exponent"> : 緩急</param>
		void SetExponent(const float exponent) { exponent_ = exponent; }
	
	public:
		
		/// <summary>
		/// 初期値取得
		/// </summary>
		/// <returns>初期値</returns>
		T Start() const { return start_; };
		
		/// <summary>
		/// 最終値取得
		/// </summary>
		/// <returns>最終値</returns>
		T End() const { return end_; };

		/// <summary>
		/// 緩急取得
		/// </summary>
		/// <returns>緩急</returns>
		float Exponent() const { return exponent_; }

	private:

		// 初期値
		T start_ = T();

		// 最終値
		T end_ = T();

		// 緩急(指数)
		float exponent_ = 0.0f;

	};
}

