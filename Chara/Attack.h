//#pragma once
//#include "Collider.h"
//#include "Timer.h"
//
//class Attack : public YGame::Collider 
//{
//private:
//	// 位置
//	YMath::Vector3 pos_;
//	// 機能タイマー
//	YMath::Timer actTimer_;
//	// 動いているか
//	bool isAct_ = false;
//public:
//	// 初期化ステータス
//	struct InitStatus 
//	{
//		YMath::Vector3 pos_; // 位置
//		float rad_; // 半径
//		uint32_t attribute_; // 属性 (自分)
//		uint32_t mask_; // マスク (相手)
//		uint32_t actFrame_; // 時間
//	};
//public:
//	// 初期化
//	void Initialize(const InitStatus& state);
//	// 更新
//	void Update();
//public:
//	// 位置取得
//	YMath::Vector3 Pos() const override { return pos_; }
//	// 動いているか
//	bool IsAct() const { return isAct_; }
//};
//
