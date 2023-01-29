#pragma once
#include "Object.h"
#include "ViewProjection.h"
#include "Shake.h"

namespace YCamera
{
	class Camera
	{
	public:
		// 位置
		YMath::Vec3 pos_;
		// 回転
		YMath::Vec3 rota_;
	private:
		// 追従点ポインタ
		YMath::Vec3* pFollowPoint_ = nullptr;
		// 追従フラグ
		bool isFollow_ = false;
		// オブジェクト
		//YGame::Object obj_;
		// ビュープロジェクション
		YGame::ViewProjection vp_;
		// カメラシェイク
		YMath::Shake shake_;
	public:
		struct InitStatus 
		{
			//YGame::Object::Status objState_;
			YMath::Vec3* pFollowPos_ = nullptr;
			bool isFollow_ = false;
		};
	public:
		// 初期化
		void Initialize(const InitStatus& state);
		// trfm → vp
		void Update();
	public:
		// カメラシェイク
		void Shaking(const int swing, const int dekey);
		// ビュープロジェクション
		YGame::ViewProjection GetViewProjection();
		// カメラ向き
		YMath::Vec3 Direction();
		// 揺れているか
		bool IsAct() { return shake_.IsAct(); }
		// 追従点設定
		void SetFollowPoint(YMath::Vec3* pFollowPoint, const bool isFollow = true);
		// 追従設定
		void SetIsFollow(const bool isFollow);
	private:
		void UpdateTarget();
	};
}