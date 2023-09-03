#include "UINumber.h"
#include "UIDigit.h"
#include "Transform.h"
#include <cassert>
#include <vector>
#include <memory>
#include <cmath>

using YGame::UINumber;
using YMath::Vector3;

namespace YGame
{
	class impl_UINumber final :
		public UINumber
	{

	public:

		// 初期化
		void Initialize(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isClearWhenTransition = true) override;

		// 更新
		void Update() override;

		// 描画
		void Draw(const std::string& shaderTag, const uint16_t priority) override;

		// 定数バッファ挿入
		void InsertConstBuffer(BaseConstBuffer* pCB) override;

		// 数設定
		void SetNumber(const uint32_t num) override;

		// 間隔設定
		void SetInterval(const float interval) override;

		// 桁ごとのオフセット設定
		void SetDigitOffset(const size_t digitIndex, const YMath::Vector3& offset) override;

		// ゼロ表示設定
		void SetShowZero(const bool shouldShowZero) override;

	public:

		impl_UINumber() = default;

		~impl_UINumber() = default;

	private:

		// トランスフォーム (各数字の親)
		Transform transform_;

		// 数字
		std::vector<std::unique_ptr<UIDigit>> digits_;

		// 数
		uint32_t num_ = 0;
		
		// 桁数
		size_t digitSize_ = 0;

		// 間隔
		float interval_ = 0;

		// ゼロ表示するか
		bool shouldShowZero_ = false;
	
	private:

		// 各数字毎に数字設定
		void SetDigitNumber();

		// 桁数計算
		void CalcDigitSize();

		// オフセット調整
		void AdjustOffset();

	};

	void impl_UINumber::Initialize(
		const uint32_t num,
		const size_t maxDigits,
		const float interval,
		const bool shouldShowZero,
		YMath::Matrix4* pParent,
		const bool isClearWhenTransition)
	{
		assert(pParent);

		transform_.Initialize();

		transform_.parent_ = pParent;

		for (size_t i = 0; i < maxDigits; i++)
		{
			digits_.emplace_back(UIDigit::Create(0, &transform_.m_, {}, isClearWhenTransition));
		}

		SetInterval(interval);

		SetNumber(num);

		SetShowZero(shouldShowZero);
	}

	void impl_UINumber::Update()
	{
		transform_.UpdateMatrix();

		for (size_t i = 0; i < digits_.size(); i++)
		{
			digits_[i]->Update();
		}
	}

	void impl_UINumber::Draw(const std::string& shaderTag, const uint16_t priority)
	{
		size_t dSize = shouldShowZero_ ? digits_.size() : digitSize_;

		for (size_t i = 0; i < dSize; i++)
		{
			digits_[i]->Draw(shaderTag, priority);
		}
	}

	void impl_UINumber::InsertConstBuffer(BaseConstBuffer* pCB)
	{
		for (size_t i = 0; i < digits_.size(); i++)
		{
			digits_[i]->InsertConstBuffer(pCB);
		}
	}

	void impl_UINumber::SetNumber(const uint32_t num)
	{
		num_ = num;

		CalcDigitSize();

		SetDigitNumber();

		AdjustOffset();
	}

	void impl_UINumber::SetInterval(const float interval)
	{
		interval_ = interval;
	}

	void impl_UINumber::SetDigitOffset(const size_t digitIndex, const YMath::Vector3& offset)
	{
		assert(0 <= digitIndex && digitIndex < digits_.size());

		digits_[digitIndex]->SetOffset(offset);
	}

	void impl_UINumber::SetShowZero(const bool shouldShowZero)
	{
		shouldShowZero_ = shouldShowZero;

		AdjustOffset();
	}

	void impl_UINumber::SetDigitNumber()
	{
		// 桁数以下の数字が来たら
		// 全桁を 0 にして返す
		if (num_ <= 0)
		{
			for (size_t i = 0; i < digits_.size(); i++)
			{
				digits_[i]->SetNumber(0);
			}

			return;
		}

		// 桁数以上の数字が来たら
		// 全桁を 9 にして返す
		if (static_cast<uint32_t>(std::powf(10.0f, static_cast<float>(digits_.size() + 1))) <= digitSize_)
		{
			for (size_t i = 0; i < digits_.size(); i++)
			{
				digits_[i]->SetNumber(9);
			}

			return;
		}

		uint32_t resultNum = num_;
		for (size_t i = 0; i < digits_.size(); i++)
		{
			// 割った余りがその桁の数字
			uint32_t digitNum = resultNum % 10;
			resultNum /= 10;

			digits_[i]->SetNumber(digitNum);
		}
	}

	void impl_UINumber::CalcDigitSize()
	{
		// 0になるまで割る
		// 割った数が桁数
		uint32_t resultNum = num_;

		for (size_t i = 0; i < digits_.size(); i++)
		{
			resultNum /= 10;

			if (resultNum <= 0) 
			{
				digitSize_ = i + 1;

				break; 
			}
		}
	}

	void impl_UINumber::AdjustOffset()
	{
		// 1列 かつ 中心が桁の半分の位置 になるように整列
		size_t dSize = shouldShowZero_ ? digits_.size() : digitSize_;
		
		float halfRangeSize = static_cast<float>(dSize) * interval_ / 2.0f;
		halfRangeSize -= interval_ / 2.0f;

		for (size_t i = 0; i < digits_.size(); i++)
		{
			Vector3 offset = { halfRangeSize - (interval_ * static_cast<float>(i)), 0.0f, 0.0f };

			digits_[i]->SetOffset(offset);
		}
	}
}

UINumber* UINumber::Create(
	const uint32_t num,
	const size_t maxDigits,
	const float interval,
	const bool shouldShowZero,
	YMath::Matrix4* pParent,
	const bool isClearWhenTransition)
{
	impl_UINumber* newInstance = new impl_UINumber();

	newInstance->Initialize(num, maxDigits, interval, shouldShowZero, pParent, isClearWhenTransition);

	return newInstance;
}
