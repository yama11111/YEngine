#pragma once
#include "BaseScene.h"
#include "BaseDrawer.h"

#include "Ease.h"
#include "BezierEase.h"
#include "SplineEase.h"

#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// テストシーン
	class TestScene : public BaseScene
	{

	private:

		Model*pGraph_ = nullptr;

		std::unique_ptr<DrawObjectForModel> obj_;
		std::unique_ptr<DrawObjectForModel> start_;
		std::unique_ptr<DrawObjectForModel> end_;
		
		std::unique_ptr<ConstBufferObject<CBColor>> cbColorObj_;
		std::unique_ptr<ConstBufferObject<CBColor>> cbColorStart_;
		std::unique_ptr<ConstBufferObject<CBColor>> cbColorEnd_;

		YMath::Ease<YMath::Vector3> ease_;
		YMath::BezierEase<YMath::Vector3> bezier_;
		YMath::SplineEase<YMath::Vector3> spline_;

		YMath::Timer timer_;
		YMath::Power power_;

		YGame::ViewProjection vp_;

		uint32_t lerpIdx = 0;
		uint32_t ratioIdx = 0;

	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		void Load() override;

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		// コンストラクタ
		TestScene() = default;
		
		// デストラクタ
		~TestScene() = default;

	};
}
