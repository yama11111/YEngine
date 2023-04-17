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
	protected:
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
		/// <param name="pos"> : 位置</param>
		/// <param name="rota"> : 回転</param>
		void Initialize(const YMath::Vector3 pos, const YMath::Vector3 rota);
		/// <summary>
		/// 初期化 (追従ver)
		/// </summary>
		/// <param name="pos"> : 位置</param>
		/// <param name="pFollowPoint"> : 追従点ポインタ</param>
		/// <param name="isFollow"> : 追従するか</param>
		void Initialize(const YMath::Vector3 pos, YMath::Vector3* pFollowPoint, bool isFollow = true);
		// 更新
		void Update();
	public:
		// カメラシェイク
		virtual void Shaking(const int swing, const int dekey);
		// ビュープロジェクション
		virtual ViewProjection GetViewProjection();
		// カメラ向き
		virtual YMath::Vector3 Direction();
		// 追従点設定
		virtual void SetFollowPoint(YMath::Vector3* pFollowPoint);
		// 追従設定
		virtual void SetIsFollow(const bool isFollow);
	private:
		// 注視点更新
		void UpdateTarget();
	public:
		Camera() = default;
		~Camera() = default;
	};
}