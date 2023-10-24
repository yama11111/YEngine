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

		// スプライトの種類
		enum class SpriteType
		{
			eNone, e2D, e3D,
		};

	public:

		// 初期化
		void Initialize2D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			const bool shouldAdjustCenter,
			YMath::Matrix4* pParent,
			const bool isClearWhenTransition = true) override;

		// 初期化
		void Initialize3D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			const bool shouldAdjustCenter,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const bool isClearWhenTransition = true) override;

		// 更新
		void Update(const Transform::Status& status = {}) override;

		// 描画
		void Draw(const std::string& shaderTag, const size_t priority) override;

		// 定数バッファ挿入
		void InsertConstBuffer(BaseConstBuffer* pCB) override;

		// 桁ごとの定数バッファ挿入
		void InsertConstBuffer(const size_t digitIndex, BaseConstBuffer* pCB) override;

		// 数設定
		void SetNumber(const uint32_t num) override;

		// 間隔設定
		void SetInterval(const float interval) override;

		// 桁ごとのオフセット設定
		void SetDigitOffset(const size_t digitIndex, const YMath::Vector3& offset) override;

		// ゼロ表示設定
		void SetShowZero(const bool shouldShowZero) override;

		// 中心整列設定
		void SetAdjustCenter(const bool shouldAdjustCenter) override;

		// スプライト種類設定
		void SetSpriteType(const SpriteType& type) { type_ = type; }

		// アニメーション更新
		void SetAnimationStatus(const size_t digitIndex, const Transform::Status& status) override;

	public:

		impl_UINumber() = default;

		~impl_UINumber() = default;

	private:

		struct Digit
		{
			std::unique_ptr<UIDigit> ui;
			Transform::Status animeStatus;
		};
	
	private:

		// トランスフォーム (各数字の親)
		Transform transform_;

		// 数字
		std::vector<Digit> digits_;

		// 数
		uint32_t num_ = 0;
		
		// 桁数
		size_t digitSize_ = 0;

		// 間隔
		float interval_ = 0;

		// ゼロ表示するか
		bool shouldShowZero_ = false;

		// 中心に整列するか
		bool shouldAdjustCenter_ = false;
	
		// スプライトタイプ
		SpriteType type_ = SpriteType::eNone;

		// 遷移時クリアフラグ
		bool isClearWhenTransition_ = false;

	private:

		// 各数字毎に数字設定
		void SetDigitNumber();

		// 桁数計算
		void CalcDigitSize();

		// オフセット調整
		void AdjustOffset();

	};

	void impl_UINumber::Initialize2D(
		const uint32_t num,
		const size_t maxDigits,
		const float interval,
		const bool shouldShowZero,
		const bool shouldAdjustCenter,
		YMath::Matrix4* pParent,
		const bool isClearWhenTransition)
	{
		assert(pParent);

		transform_.Initialize();

		transform_.parent_ = pParent;

		if (type_ != SpriteType::e2D ||
			digits_.empty() ||
			isClearWhenTransition_ != isClearWhenTransition)
		{
			for (size_t i = 0; i < maxDigits; i++)
			{
				digits_.emplace_back();
				digits_[i].ui.reset(UIDigit::Create2D(0, &transform_.m_, {}, isClearWhenTransition));
				digits_[i].animeStatus = {};
			}
		}
		else
		{
			for (size_t i = 0; i < digits_.size(); i++)
			{
				digits_[i].ui->Initialize2D(0, &transform_.m_, {}, isClearWhenTransition);;
				digits_[i].animeStatus = {};
			}
		}

		SetInterval(interval);
		SetNumber(num);
		SetShowZero(shouldShowZero);
		SetAdjustCenter(shouldAdjustCenter);
		SetSpriteType(SpriteType::e2D);

		isClearWhenTransition_ = isClearWhenTransition;
	}

	void impl_UINumber::Initialize3D(
		const uint32_t num,
		const size_t maxDigits,
		const float interval,
		const bool shouldShowZero,
		const bool shouldAdjustCenter,
		YMath::Matrix4* pParent, 
		const bool isXAxisBillboard, const bool isYAxisBillboard, 
		ViewProjection* pVP, 
		const bool isClearWhenTransition)
	{
		assert(pParent);

		transform_.Initialize();

		transform_.parent_ = pParent;

		if (type_ != SpriteType::e3D ||
			digits_.empty() ||
			isClearWhenTransition_ != isClearWhenTransition)
		{
			for (size_t i = 0; i < maxDigits; i++)
			{
				digits_.emplace_back();
				digits_[i].ui.reset(UIDigit::Create3D(
					0, &transform_.m_, isXAxisBillboard, isYAxisBillboard, pVP, {}, isClearWhenTransition));
				digits_[i].animeStatus = {};
			}
		}
		else
		{
			for (size_t i = 0; i < digits_.size(); i++)
			{
				digits_[i].ui->Initialize3D(
					0, &transform_.m_, isXAxisBillboard, isYAxisBillboard, pVP, {}, isClearWhenTransition);
				digits_[i].animeStatus = {};
			}
		}

		SetInterval(interval);
		SetNumber(num);
		SetShowZero(shouldShowZero);
		SetAdjustCenter(shouldAdjustCenter);
		SetSpriteType(SpriteType::e3D);

		isClearWhenTransition_ = isClearWhenTransition;
	}

	void impl_UINumber::Update(const Transform::Status& status)
	{
		transform_.UpdateMatrix(status);

		for (size_t i = 0; i < digits_.size(); i++)
		{
			digits_[i].ui->Update(digits_[i].animeStatus);
			digits_[i].animeStatus = {};
		}
	}

	void impl_UINumber::Draw(const std::string& shaderTag, const size_t priority)
	{
		size_t dSize = shouldShowZero_ ? digits_.size() : digitSize_;

		for (size_t i = 0; i < dSize; i++)
		{
			digits_[i].ui->Draw(shaderTag, priority);
		}
	}

	void impl_UINumber::InsertConstBuffer(BaseConstBuffer* pCB)
	{
		for (size_t i = 0; i < digits_.size(); i++)
		{
			digits_[i].ui->InsertConstBuffer(pCB);
		}
	}

	void impl_UINumber::InsertConstBuffer(const size_t digitIndex, BaseConstBuffer* pCB)
	{
		assert(0 <= digitIndex && digitIndex < digits_.size());
		
		digits_[digitIndex].ui->InsertConstBuffer(pCB);
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

		AdjustOffset();
	}

	void impl_UINumber::SetDigitOffset(const size_t digitIndex, const YMath::Vector3& offset)
	{
		assert(0 <= digitIndex && digitIndex < digits_.size());

		digits_[digitIndex].ui->SetOffset(offset);
	}

	void impl_UINumber::SetShowZero(const bool shouldShowZero)
	{
		shouldShowZero_ = shouldShowZero;
	}

	void impl_UINumber::SetAdjustCenter(const bool shouldAdjustCenter)
	{
		shouldAdjustCenter_ = shouldAdjustCenter;

		AdjustOffset();
	}

	void impl_UINumber::SetAnimationStatus(const size_t digitIndex, const Transform::Status& status)
	{
		assert(0 <= digitIndex && digitIndex < digits_.size());

		digits_[digitIndex].animeStatus = status;
	}

	void impl_UINumber::SetDigitNumber()
	{
		// 桁数以下の数字が来たら
		// 全桁を 0 にして返す
		if (num_ <= 0)
		{
			for (size_t i = 0; i < digits_.size(); i++)
			{
				digits_[i].ui->SetNumber(0);
			}

			return;
		}

		// 桁数以上の数字が来たら
		// 全桁を 9 にして返す
		if (static_cast<uint32_t>(std::powf(10.0f, static_cast<float>(digits_.size() + 1))) <= digitSize_)
		{
			for (size_t i = 0; i < digits_.size(); i++)
			{
				digits_[i].ui->SetNumber(9);
			}

			return;
		}

		uint32_t resultNum = num_;
		for (size_t i = 0; i < digits_.size(); i++)
		{
			// 割った余りがその桁の数字
			uint32_t digitNum = resultNum % 10;
			resultNum /= 10;

			digits_[i].ui->SetNumber(digitNum);
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
		size_t dSize = shouldAdjustCenter_ ? digitSize_ : digits_.size();
		
		float halfRangeSize = static_cast<float>(dSize) * interval_ / 2.0f;
		halfRangeSize -= interval_ / 2.0f;

		for (size_t i = 0; i < digits_.size(); i++)
		{
			Vector3 offset = { halfRangeSize - (interval_ * static_cast<float>(i)), 0.0f, 0.0f };

			digits_[i].ui->SetOffset(offset);
		}
	}
}

UINumber* UINumber::Create2D(
	const uint32_t num,
	const size_t maxDigits,
	const float interval,
	const bool shouldShowZero,
	const bool shouldAdjustCenter,
	YMath::Matrix4* pParent,
	const bool isClearWhenTransition)
{
	impl_UINumber* newInstance = new impl_UINumber();

	newInstance->Initialize2D(num, maxDigits, interval, shouldShowZero, shouldAdjustCenter, pParent, isClearWhenTransition);

	return newInstance;
}

UINumber* UINumber::Create3D(
	const uint32_t num,
	const size_t maxDigits,
	const float interval,
	const bool shouldShowZero,
	const bool shouldAdjustCenter,
	YMath::Matrix4* pParent, 
	const bool isXAxisBillboard, const bool isYAxisBillboard, 
	ViewProjection* pVP, 
	const bool isClearWhenTransition)
{
	impl_UINumber* newInstance = new impl_UINumber();

	newInstance->Initialize3D(num, maxDigits, interval, shouldShowZero, shouldAdjustCenter, pParent, 
		isXAxisBillboard, isYAxisBillboard, pVP, isClearWhenTransition);

	return newInstance;
}
