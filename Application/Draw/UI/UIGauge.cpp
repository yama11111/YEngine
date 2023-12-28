#include "UIGauge.h"
#include "Ease.h"
#include "Timer.h"
#include "MathVector.h"
#include "MathUtil.h"
#include <cassert>

using YGame::UIGauge;
using YMath::Vector3;
using YMath::Vector4;

namespace YGame
{
	class impl_UIGauge final :
		public UIGauge
	{

	public:

		// 初期化
		void Initialize(BaseDrawObject* obj, const bool isClearWhenTransition = true) override;

		// 更新
		void Update() override;

		// 描画
		void Draw(const std::string& shaderTag, const size_t priority) override;

	public:

		// 変更
		void Change(const float ratio, const uint32_t frame, const float exponent) override;

		// アニメーション更新
		void UpdateAnimation();

	public:

		impl_UIGauge() = default;

		~impl_UIGauge() = default;
	
	private:

		// オブジェクト
		std::unique_ptr<BaseDrawObject> obj_;

		// 潰れる量
		Transform::Status animeStatus_;

		// 割合
		float currentRatio_ = 0.0f;

		// スケール
		float maxWidth = 0.0f;

		// 割合イージング
		YMath::Ease<float> ratioEase_;
		
		// 割合パワー
		YMath::Timer ratioTimer_;

	};

	void impl_UIGauge::Initialize(BaseDrawObject* obj, const bool isClearWhenTransition)
	{
		isClearWhenTransition;
		obj_.reset(obj);

		animeStatus_ = {};

		maxWidth = obj_->transform_.scale_.x_;

		currentRatio_ = 1.0f;
		ratioEase_.Initialize(0.0f, 0.0f, 0.0f);
		ratioTimer_.Initialize(0);
	}

	void impl_UIGauge::Update()
	{
		assert(obj_);

		animeStatus_ = {};

		UpdateAnimation();

		// ブヨブヨアニメーションを適応
		obj_->Update(animeStatus_);
	}

	void impl_UIGauge::Change(const float ratio, const uint32_t frame, const float exponent)
	{
		float r = YMath::Clamp(ratio, 0.0f, 1.0f);
		
		ratioTimer_.Initialize(frame);
		ratioTimer_.SetActive(true);
		
		ratioEase_.Initialize(currentRatio_, r, exponent);
	}

	void impl_UIGauge::UpdateAnimation()
	{
		ratioTimer_.Update();
		currentRatio_ = ratioEase_.InOut(ratioTimer_.Ratio());

		animeStatus_.pos_.x_ = -(maxWidth * (1.0f - currentRatio_) / 2.0f);
		animeStatus_.scale_.x_ = -maxWidth * (1.0f - currentRatio_);
	}

	void impl_UIGauge::Draw(const std::string& shaderTag, const size_t priority)
	{
		obj_->Draw(shaderTag, priority);
	}
}

UIGauge* UIGauge::Create(BaseDrawObject* obj, const bool isClearWhenTransition)
{
	impl_UIGauge* newInstance = new impl_UIGauge();

	newInstance->Initialize(obj, isClearWhenTransition);

	return newInstance;
}