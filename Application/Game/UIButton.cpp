#include "UIButton.h"
#include <cassert>

using YGame::UIButton;
using YMath::Vector3;

void UIButton::Initialize(BaseDrawObject* obj)
{
	// �I�u�W�F�N�g�����鎞�̂ݐݒ�
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

	// �u���u���A�j���[�V������K��
	obj_->Update({ {}, {}, SlimeActor::WobbleScaleValue() });
}

void UIButton::PressTrigger()
{
	// �u���u���A�j���[�V����
	// �ׂ��
	
	std::vector<Vector3> scaleVals;

	// �ׂ���
	Vector3 squash = obj_->transform_.scale_ / 4.0f;
	squash.y_ *= -1.0f;

	scaleVals.emplace_back(Vector3()); // ����
	scaleVals.emplace_back(squash); // �ׂ��
	scaleVals.emplace_back(Vector3()); // ���ɖ߂�

	static const uint32_t frame = 5;
	
	static const float exponent = 3.0f;

	SlimeActor::Wobble(scaleVals, frame, exponent);
}

void UIButton::Draw(const std::string& shaderTag, const uint16_t priority)
{
	obj_->Draw(shaderTag, priority);
}
