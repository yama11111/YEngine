#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <vector>

namespace YMath
{
	/// <summary>
	/// 補間
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a"> : 初期値</param>
	/// <param name="b"> : 最終値</param>
	/// <param name="t"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T Lerp(const T& a, const T& b, const float t);

	/// <summary>
	/// 3次元補間
	/// </summary>
	/// <param name="v1"> : 初期値</param>
	/// <param name="v2"> : 最終値</param>
	/// <param name="t"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <returns>その割合の時の値</returns>
	Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

	/// <summary>
	/// イーズイン(だんだん早く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : 初期値</param>
	/// <param name="end"> : 最終値</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T EaseIn(const T& start, const T& end, const float ratio, const float exponent);

	/// <summary>
	/// イーズアウト(だんだん遅く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : 初期値</param>
	/// <param name="end"> : 最終値</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T EaseOut(const T& start, const T& end, const float ratio, const float exponent);


	/// <summary>
	/// ベジエ曲線
	/// </summary>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <returns>その割合の時の値</returns>
	Vector3 Bezier(const std::vector<Vector3>& points, const float ratio);

	/// <summary>
	/// スプライン曲線
	/// </summary>
	/// <param name="points"> : 基準点の配列 (4点以上必須)</param>
	/// <param name="section"> : 配列の位置 (pointとpointの間)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <returns>その割合の時の値</returns>
	Vector3 Spline(const std::vector<Vector3>& points, const size_t section, const float ratio);

	/// <summary>
	/// イーズイン[ベジエ曲線ver](だんだん早く)
	/// </summary>
	/// <param name="points"></param>
	/// <param name="ratio"></param>
	/// <param name="exponent"></param>
	/// <returns></returns>
	Vector3 EaseInBezier(const std::vector<Vector3>& points, const float ratio, const float exponent);

	/// <summary>
	/// イーズアウト[ベジエ曲線ver](だんだん遅く)
	/// </summary>
	/// <param name="points"></param>
	/// <param name="ratio"></param>
	/// <param name="exponent"></param>
	/// <returns></returns>
	Vector3 EaseOutBezier(const std::vector<Vector3>& points, const float ratio, const float exponent);


	// イージングクラス
	template<typename T>
	class Ease
	{
	private:
		// 初期値
		T start_ = T();
		// 最終値
		T end_ = T();
		// 緩急(指数)
		float exponent_ = 0.0f;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="start"> : 初期値</param>
		/// <param name="end"> : 最終値</param>
		/// <param name="exponent"> : 指数(緩急)</param>
		void Initialize(const T& start, const T& end, const float exponent);
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
		// 初期値設定
		void SetStart(const T& start) { start_ = start; };
		// 最終値設定 
		void SetEnd(const T& end) { end_ = end; };
		// 緩急設定
		void SetExponent(const float exponent) { exponent_ = exponent; }
	public:
		// 初期値設定
		T SetStart() const { return start_; };
		// 最終値設定 
		T SetEnd() const { return end_; };
		// 緩急設定
		float SetExponent() const { return exponent_; }
	};


	// 曲線イージングクラス
	class BezierEase
	{
	private:
		// 値
		std::vector<Vector3> points_{};
		// 緩急(指数)
		float exponent_ = 0.0f;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
		/// <param name="exponent"> : 指数(緩急)</param>
		void Initialize(const std::vector<Vector3>& points, const float exponent);
	public:
		/// <summary>
		/// イーズイン(だんだん早く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <returns>その割合の時の値</returns>
		Vector3 In(const float ratio);
		/// <summary>
		/// イーズアウト(だんだん遅く)
		/// </summary>
		/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
		/// <returns>その割合の時の値</returns>
		Vector3 Out(const float ratio);
	public:
		// 初期値設定
		void SetStart(const std::vector<Vector3>& points) { points_ = points; };
		// 緩急設定
		void SetExponent(const float exponent) { exponent_ = exponent; }
	};
}
