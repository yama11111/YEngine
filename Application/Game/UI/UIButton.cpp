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
		public UIButton
	{
	
	public:

		// ������
		void Initialize(BaseDrawObject* obj, const bool isClearWhenTransition = true) override;

		// �X�V
		void Update(const bool isDown) override;

		// �`��
		void Draw(const std::string& shaderTag, const uint16_t priority) override;
	
	public:
		
		impl_UIButton() = default;
		
		~impl_UIButton() = default;

	private:

		// �I�u�W�F�N�g
		std::unique_ptr<BaseDrawObject> obj_;

		// �F�萔�o�b�t�@
		std::unique_ptr<ConstBufferObject<CBColor>> cbColor_;

		// �X���C���A�j���[�V����
		SlimeActor slimeActor_;

		// �ׂ���
		Transform::Status animeStatus_;

	private:

		// ���� (�u��)
		void PressAnimation(const bool isDown);

	};
	
	void impl_UIButton::Initialize(BaseDrawObject* obj, const bool isClearWhenTransition)
	{
		obj_.reset(obj);

		cbColor_.reset(ConstBufferObject<CBColor>::Create(isClearWhenTransition));
		obj->InsertConstBuffer(cbColor_.get());

		static const uint32_t kFrame = 4;

		static const float kExponent = 3.0f;

		// �A�j���[�V�����Œׂ���
		Vector3 squashVal = YMath::DivAtComponent(obj_->transform_.scale_, Vector3(+4.0f, -4.0f, +4.0f));

		slimeActor_.Initialize(kFrame, { {}, squashVal }, kExponent);

		animeStatus_ = {};
	}
	
	void impl_UIButton::Update(const bool isDown)
	{
		assert(obj_);

		animeStatus_ = {};

		PressAnimation(isDown);

		// �u���u���A�j���[�V������K��
		obj_->Update(animeStatus_);
	}
	
	void impl_UIButton::Draw(const std::string& shaderTag, const uint16_t priority)
	{
		obj_->Draw(shaderTag, priority);
	}
	
	void impl_UIButton::PressAnimation(const bool isDown)
	{
		// �u���u���A�j���[�V����

		if (isDown)
		{
			// �ׂ�� (�C�[�Y�C��)
			animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

			// �Â��F�ɂ���
			cbColor_->data_.baseColor = Vector4(0.25f, 0.25f, 0.25f, 1.0f);
		}
		else
		{
			// �߂� (�C�[�Y�A�E�g)
			animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eIn);
			
			// ���̐F�ɖ߂�
			cbColor_->data_.baseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);			
		}
		
		animeStatus_.pos_ += Vector3(0.0f, -animeStatus_.scale_.y_, 0.0f) * 32.0f;
		
		slimeActor_.Update(isDown);
	}
}

UIButton* UIButton::Create(BaseDrawObject* obj, const bool isClearWhenTransition)
{
	impl_UIButton* newInstance = new impl_UIButton();

	newInstance->Initialize(obj);

	return newInstance;
}