#include "UIButton.h"
#include <cassert>

using YGame::UIButton;
using YMath::Vector3;

void UIButton::Initialize(BaseDrawObject* obj)
{
	// オブジェクトがある時のみ設定
	if (obj)
	{
		obj_.reset(obj);
	}

	SlimeActor::Initialize();
}

void UIButton::Update()
{
	assert(obj_);

	SlimeActor::Update();

	// ブヨブヨアニメーションを適応
	obj_->Update({ {}, {}, SlimeActor::WobbleScaleValue() });
}

void UIButton::PressTrigger()
{
	// ブヨブヨアニメーション
	// 潰れる
	
	std::vector<Vector3> scaleVals;

	// 潰れる量
	Vector3 squash = obj_->transform_.scale_ / 4.0f;
	squash.y_ *= -1.0f;

	scaleVals.emplace_back(Vector3()); // 普通
	scaleVals.emplace_back(squash); // 潰れる
	scaleVals.emplace_back(Vector3()); // 元に戻る

	static const uint32_t frame = 5;
	
	static const float exponent = 3.0f;

	SlimeActor::Wobble(scaleVals, frame, exponent);
}

void UIButton::Draw(const std::string& shaderTag, const uint16_t priority)
{
	obj_->Draw(shaderTag, priority);
}
