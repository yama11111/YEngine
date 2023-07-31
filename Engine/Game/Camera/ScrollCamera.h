#pragma once
#include "Camera.h"

namespace YGame
{
	class ScrollCamera : private Camera
	{
	public:
		// 追従点との距離
		YMath::Vector3 distance_;
		// 追従しない範囲
		YMath::Vector3 tolerance_;
	public:
		/// <summary>
		/// 初期化 (追従ver)
		/// </summary>
		/// <param name="distance"> : 追従点との距離 (この距離を保ち続ける)</param>
		/// <param name="pFollowPoint"> : 追従点ポインタ</param>
		/// <param name="tolerance"> : 追従しない範囲</param>
		void Initialize(const YMath::Vector3 distance, YMath::Vector3* pFollowPoint, const YMath::Vector3 tolerance);
		
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		void Update(const Transform::Status& status = {});
	public:
		// カメラシェイク
		void Shaking(const float swing, const float dekey, const float place) override { Camera::Shaking(swing, dekey, place); }
		// ビュープロジェクション
		ViewProjection GetViewProjection() override { return Camera::GetViewProjection(); }
		// カメラ向き
		YMath::Vector3 Direction() override { return Camera::Direction(); }
		// 追従点設定
		void SetFollowPoint(YMath::Vector3* pFollowPoint) override;
		// 追従設定
		void SetIsFollow(const bool isFollow) override { Camera::SetIsFollow(isFollow); }
	public:
		ScrollCamera() = default;
		~ScrollCamera() = default;
	};
}

