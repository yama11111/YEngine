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

		// �X�v���C�g�̎��
		enum class SpriteType
		{
			eNone, e2D, e3D,
		};

	public:

		// ������
		void Initialize2D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isClearWhenTransition = true) override;

		// ������
		void Initialize3D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const bool isClearWhenTransition = true) override;

		// �X�V
		void Update(const Transform::Status& status = {}) override;

		// �`��
		void Draw(const std::string& shaderTag, const uint16_t priority) override;

		// �萔�o�b�t�@�}��
		void InsertConstBuffer(BaseConstBuffer* pCB) override;

		// ���ݒ�
		void SetNumber(const uint32_t num) override;

		// �Ԋu�ݒ�
		void SetInterval(const float interval) override;

		// �����Ƃ̃I�t�Z�b�g�ݒ�
		void SetDigitOffset(const size_t digitIndex, const YMath::Vector3& offset) override;

		// �[���\���ݒ�
		void SetShowZero(const bool shouldShowZero) override;

		// �X�v���C�g��ސݒ�
		void SetSpriteType(const SpriteType& type) { type_ = type; }

		// �A�j���[�V�����X�V
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

		// �g�����X�t�H�[�� (�e�����̐e)
		Transform transform_;

		// ����
		std::vector<Digit> digits_;

		// ��
		uint32_t num_ = 0;
		
		// ����
		size_t digitSize_ = 0;

		// �Ԋu
		float interval_ = 0;

		// �[���\�����邩
		bool shouldShowZero_ = false;
	
		// �X�v���C�g�^�C�v
		SpriteType type_ = SpriteType::eNone;

		// �J�ڎ��N���A�t���O
		bool isClearWhenTransition_ = false;

	private:

		// �e�������ɐ����ݒ�
		void SetDigitNumber();

		// �����v�Z
		void CalcDigitSize();

		// �I�t�Z�b�g����
		void AdjustOffset();

	};

	void impl_UINumber::Initialize2D(
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

		SetSpriteType(SpriteType::e2D);

		isClearWhenTransition_ = isClearWhenTransition;
	}

	void impl_UINumber::Initialize3D(
		const uint32_t num, 
		const size_t maxDigits, 
		const float interval, 
		const bool shouldShowZero, 
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

	void impl_UINumber::Draw(const std::string& shaderTag, const uint16_t priority)
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

		AdjustOffset();
	}

	void impl_UINumber::SetAnimationStatus(const size_t digitIndex, const Transform::Status& status)
	{
		assert(0 <= digitIndex && digitIndex < digits_.size());

		digits_[digitIndex].animeStatus = status;
	}

	void impl_UINumber::SetDigitNumber()
	{
		// �����ȉ��̐�����������
		// �S���� 0 �ɂ��ĕԂ�
		if (num_ <= 0)
		{
			for (size_t i = 0; i < digits_.size(); i++)
			{
				digits_[i].ui->SetNumber(0);
			}

			return;
		}

		// �����ȏ�̐�����������
		// �S���� 9 �ɂ��ĕԂ�
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
			// �������]�肪���̌��̐���
			uint32_t digitNum = resultNum % 10;
			resultNum /= 10;

			digits_[i].ui->SetNumber(digitNum);
		}
	}

	void impl_UINumber::CalcDigitSize()
	{
		// 0�ɂȂ�܂Ŋ���
		// ��������������
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
		// 1�� ���� ���S�����̔����̈ʒu �ɂȂ�悤�ɐ���
		size_t dSize = shouldShowZero_ ? digits_.size() : digitSize_;
		
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
	YMath::Matrix4* pParent,
	const bool isClearWhenTransition)
{
	impl_UINumber* newInstance = new impl_UINumber();

	newInstance->Initialize2D(num, maxDigits, interval, shouldShowZero, pParent, isClearWhenTransition);

	return newInstance;
}

UINumber* UINumber::Create3D(
	const uint32_t num, 
	const size_t maxDigits, 
	const float interval, 
	const bool shouldShowZero, 
	YMath::Matrix4* pParent, 
	const bool isXAxisBillboard, const bool isYAxisBillboard, 
	ViewProjection* pVP, 
	const bool isClearWhenTransition)
{
	impl_UINumber* newInstance = new impl_UINumber();

	newInstance->Initialize3D(num, maxDigits, interval, shouldShowZero, pParent, 
		isXAxisBillboard, isYAxisBillboard, pVP, isClearWhenTransition);

	return newInstance;
}