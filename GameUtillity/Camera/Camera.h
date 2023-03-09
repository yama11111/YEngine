#pragma once
#include "Model.h"
#include "Shake.h"

namespace YGame
{
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
		// オブジェクト
		std::unique_ptr<YGame::ObjectModel> obj_;
		// ビュープロジェクション
		YGame::ViewProjection vp_;
		// カメラシェイク
		YMath::Shake shake_;
	public:
		struct InitStatus 
		{
			YGame::BaseObject::Status objState_;
			YMath::Vector3* pFollowPos_ = nullptr;
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
		YMath::Vector3 Direction();
		// 揺れているか
		bool IsAct() { return shake_.IsAct(); }
		// 追従点設定
		void SetFollowPoint(YMath::Vector3* pFollowPoint, const bool isFollow = true);
		// 追従設定
		void SetIsFollow(const bool isFollow);
	private:
		void UpdateTarget();
	};
}