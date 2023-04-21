#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// パーティクル基底クラス
	class IParticle
	{
	public:
		// 生存フラグ
		bool isAlive_ = false;
	protected:
		// オブジェクト
		std::unique_ptr<YGame::ModelObject> obj_;
		// 生存タイマー
		YMath::Timer aliveTim_;
	public:
		// 更新
		virtual void Update() = 0;
		// 描画
		virtual void Draw() = 0;
	protected:
		// ビュープロジェクションポインタ
		static YGame::ViewProjection* spVP_;
	public:
		// 静的初期化
		static void StaticInitialize(YGame::ViewProjection* pVP);
	public:
		// デストラクタ
		virtual ~IParticle() = default;
	};
}
