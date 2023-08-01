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

		// �ׂ���
		YMath::Vector3 squash_;

	private:

		// ���� (�u��)
		void PressAnimation(const bool isDown);

	};
	
	void impl_UIButton::Initialize(BaseDrawObject* obj, const bool isClearWhenTransition)
	{
		obj_.reset(obj);

		cbColor_.reset(ConstBufferObject<CBColor>::Create(isClearWhenTransition));
		obj->InsertConstBuffer(cbColor_.get());

		SlimeActor::Initialize();

		// �A�j���[�V�����Œׂ���
		squash_ = YMath::DivAtComponent(obj_->transform_.scale_, Vector3(+2.0f, -4.0f, +2.0f));
	}
	
	void impl_UIButton::Update(const bool isDown)
	{
		assert(obj_);

		//PressAnimation(isDown);

		SlimeActor::Update();

		// �u���u���A�j���[�V������K��
		obj_->Update({ {}, {}, SlimeActor::WobbleScaleValue() });
	}
	
	void impl_UIButton::Draw(const std::string& shaderTag, const uint16_t priority)
	{
		obj_->Draw(shaderTag, priority);
	}
	
	void impl_UIButton::PressAnimation(const bool isDown)
	{
		// �u���u���A�j���[�V����
		// �X�P�[���̑J�ڂ�}�����Ă���
		std::vector<Vector3> scaleVals;

		Vector3 currentScale = obj_->transform_.scale_ + SlimeActor::WobbleScaleValue();
		scaleVals.emplace_back(currentScale);
		
		if(isDown)
		{
			// �ׂ��
			scaleVals.emplace_back(squash_);

			// �Â��F�ɂ���
			cbColor_->data_.baseColor = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else
		{
			// ���ɖ߂�
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