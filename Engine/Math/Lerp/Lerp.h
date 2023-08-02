#pragma once
#include "Vector3.h"
#include <vector>

namespace YMath
{

#pragma region Lerp

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
	/// ベジエ曲線
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T Bezier(const std::vector<T>& points, const float ratio);

	/// <summary>
	/// スプライン曲線
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (2点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T Spline(const std::vector<T>& points, const float ratio);

#pragma endregion

#pragma region Ease

	/// <summary>
	/// イーズイン
	/// (だんだん早く)
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
	/// イーズアウト
	/// (だんだん遅く)
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
	/// イーズインアウト
	/// (だんだん早く → だんだん遅く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : 初期値</param>
	/// <param name="end"> : 最終値</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <param name="controlPoint"> : 制御点</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T EaseInOut(const T& start, const T& end, const float ratio, const float exponent, const float controlPoint = 0.5f);

	/// <summary>
	/// イーズアウトイン
	/// (だんだん遅く → だんだん早く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="start"> : 初期値</param>
	/// <param name="end"> : 最終値</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <param name="controlPoint"> : 制御点</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T EaseOutIn(const T& start, const T& end, const float ratio, const float exponent, const float controlPoint = 0.5f);

#pragma endregion

#pragma region BezierEase

	/// <summary>
	/// イーズイン [ベジエ曲線ver]
	/// (だんだん早く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T BezierEaseIn(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// イーズアウト [ベジエ曲線ver]
	/// (だんだん遅く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T BezierEaseOut(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// イーズアウト [ベジエ曲線ver]
	/// (だんだん早く → だんだん遅く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <param name="controlPoint"> : 制御点</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T BezierEaseOutIn(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

	/// <summary>
	/// イーズアウト [ベジエ曲線ver]
	/// (だんだん遅く → だんだん早く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <param name="controlPoint"> : 制御点</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T BezierEaseInOut(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

#pragma endregion

#pragma region SplineEase

	/// <summary>
	/// イーズイン [スプライン曲線ver]
	/// (だんだん早く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (4点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T SplineEaseIn(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// イーズアウト [スプライン曲線ver]
	/// (だんだん遅く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (4点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T SplineEaseOut(const std::vector<T>& points, const float ratio, const float exponent);

	/// <summary>
	/// イーズアウト [スプライン曲線ver]
	/// (だんだん早く → だんだん遅く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <param name="controlPoint"> : 制御点</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T SplineEaseOutIn(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

	/// <summary>
	/// イーズアウト [スプライン曲線ver]
	/// (だんだん遅く → だんだん早く)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="points"> : 基準点の配列 (1点以上必須)</param>
	/// <param name="ratio"> : 割合 (基本 0.0 ~ 1.0)</param>
	/// <param name="exponent"> : 指数(緩急)</param>
	/// <param name="controlPoint"> : 制御点</param>
	/// <returns>その割合の時の値</returns>
	template<typename T>
	T SplineEaseInOut(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint = 0.5f);

#pragma endregion

}
