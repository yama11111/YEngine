#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Shake.h"

namespace YGame
{
	// カメラクラス
	class Camera
	{
	public:
		// 位置
		YMath::Vector3 pos_;
		// 回転
		YMath::Vector3 rota_;
	private:
		// 追従点ポインタ
		YMath::Vector3* pFollowPoint_ = nullptr;
		// 追従フラグ
		bool isFollow_ = false;
		// トランスフォーム
		Transform transform_;
		// ビュープロジェクション
		ViewProjection vp_;
		// カメラシェイク
		YMath::Shake shake_;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : トランスフォーム設定用ステータス</param>
		/// <param name="status.pos_"> : 位置</param>
		/// <param name="status.rota_"> : 回転</param>
		/// <param name="status.scale_"> : 大きさ</param>
		/// <param name="-------------------------------------------"></param>
		/// <param name="pFollowPoint"> : 追従点ポインタ</param>
		/// <param name="isFollow"> : 追従するか</param>
		void Initialize(const Transform::Status& status, YMath::Vector3* pFollowPoint = nullptr, bool isFollow = false);
		// 更新
		void Update();
	public:
		// カメラシェイク
		void Shaking(const int swing, const int dekey);
		// ビュープロジェクション
		ViewProjection GetViewProjection();
		// カメラ向き
		YMath::Vector3 Direction();
		// 揺れているか
		bool IsAct() { return shake_.IsAct(); }
		// 追従点設定
		void SetFollowPoint(YMath::Vector3* pFollowPoint, const bool isFollow = true);
		// 追従設定
		void SetIsFollow(const bool isFollow);
	private:
		// 注視点更新
		void UpdateTarget();
	};
}