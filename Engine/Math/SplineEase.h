#pragma once
#include <vector>

namespace YMath
{
	// スプライン曲線イージングクラス
	template<typename T>
	class SplineEase
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
		/// <param name="exponent"> : 指数(緩急)</param>
		void Initialize(const std::vector<T>& points, const float exponent);

	public:

		/// <summary>
		/// イーズイン(だんだん早く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <returns>その割合の時の値</returns>
		T In(const float ratio);

		/// <summary>
		/// イーズアウト(だんだん遅く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <returns>その割合の時の値</returns>
		T Out(const float ratio);

	public:

		/// <summary>
		/// 基準点設定
		/// </summary>
		/// <param name="points"> : 基準点の配列</param>
		void SetPoints(const std::vector<T>& points) { points_ = points; };

		/// <summary>
		/// 緩急設定
		/// </summary>
		/// <param name="exponent"> : 緩急</param>
		void SetExponent(const float exponent) { exponent_ = exponent; }

	public:

		/// <summary>
		/// 基準点取得
		/// </summary>
		/// <returns>基準点の配列</returns>
		std::vector<T> Points() const { return points_; };

		/// <summary>
		/// 緩急取得
		/// </summary>
		/// <returns>緩急</returns>
		float Exponent() const { return exponent_; }

	private:

		// 値
		std::vector<T> points_{};

		// 緩急(指数)
		float exponent_ = 0.0f;

	};
}
