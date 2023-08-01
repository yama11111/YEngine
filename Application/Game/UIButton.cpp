#include "UIButton.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "SlimeActor.h"
#include "MathVector.h"
#include <cassert>

using YGame::UIButton;
using YMath::Vector3;
using YMath::Vector4;

namespace YGame
{
	class impl_UIButton final: 
		public UIButton, 
		private SlimeActor
	{
	
	public:

		// 初期化
		void Initialize(BaseDrawObject* obj, const bool isClearWhenTransition = true) override;

		// 更新
		void Update(const bool isDown) override;

		// 描画
		void Draw(const std::string& shaderTag, const uint16_t priority) override;
	
	public:
		
		impl_UIButton() = default;
		
		~impl_UIButton() = default;

	private:

		// オブジェクト
		std::unique_ptr<BaseDrawObject> obj_;

		// 色定数バッファ
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// 潰れる量
		YMath::Vector3 squash_;

	private:

		// 押す (瞬間)
		void PressAnimation(const bool isDown);

	};
	
	void impl_UIButton::Initialize(BaseDrawObject* obj, const bool isClearWhenTransition)
	{
		obj_.reset(obj);

		cbColor_.reset(ConstBufferObject<CBColor>::Create(isClearWhenTransition));
		obj->InsertConstBuffer(cbColor_.get());

		SlimeActor::Initialize();

		// アニメーションで潰れる量
		squash_ = YMath::DivAtComponent(obj_->transform_.scale_, Vector3(+2.0f, -4.0f, +2.0f));
	}
	
	void impl_UIButton::Update(const bool isDown)
	{
		assert(obj_);

		//PressAnimation(isDown);

		SlimeActor::Update();

		// ブヨブヨアニメーションを適応
		obj_->Update({ {}, {}, SlimeActor::WobbleScaleValue() });
	}
	
	void impl_UIButton::Draw(const std::string& shaderTag, const uint16_t priority)
	{
		obj_->Draw(shaderTag, priority);
	}
	
	void impl_UIButton::PressAnimation(const bool isDown)
	{
		// ブヨブヨアニメーション
		// スケールの遷移を挿入していく
		std::vector<Vector3> scaleVals;

		Vector3 currentScale = obj_->transform_.scale_ + SlimeActor::WobbleScaleValue();
		scaleVals.emplace_back(currentScale);
		
		if(isDown)
		{
			// 潰れる
			scaleVals.emplace_back(squash_);

			// 暗い色にする
			cbColor_->data_.baseColor = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else
		{
			// 元に戻る
			scaleVals.emplace_back(Vector3());
			
			cbColor_->data_.baseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		static const uint32_t frame = 4;

		static const float exponent = 3.0f;

		SlimeActor::Wobble(scaleVals, frame, exponent);
	}
}

UIButton* UIButton::Create(BaseDrawObject* obj, const bool isClearWhenTransition)
{
	impl_UIButton* newInstance = new impl_UIButton();

	newInstance->Initialize(obj);

	return newInstance;
}