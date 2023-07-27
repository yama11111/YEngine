#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{	
	// �I�u�W�F�N�g + �萔�o�b�t�@����
	// ������A�I�u�W�F�N�g�ɑ}��
	obj_.reset(DrawObjectForModel::Create(Transform::Status::Default(), spVP_, nullptr));

	// �e�ݒ�
	SetParent(pParent);

	cbColor_.reset(ConstBufferObject<CBColor>::Create());
	obj_->InsertConstBuffer(cbColor_.get());

	cbMaterial_.reset(ConstBufferObject<CBMaterial>::Create());
	cbMaterial_->data_.ambient = { 0.2f,0.2f,0.2f };
	obj_->InsertConstBuffer(cbMaterial_.get());

	cbLightGroup_.reset(ConstBufferObject<CBLightGroup>::Create());
	cbLightGroup_->data_.direLights[0].active = 1.0f;
	obj_->InsertConstBuffer(cbLightGroup_.get());

	cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create());
	obj_->InsertConstBuffer(cbTexConfig_.get());


	drawPriority_ = drawPriority;

	isVisible_ = true;

	isVisibleUpdate_ = true;

	animationBitFlag_ = 0;

	animeStatus_ = {};
}

void BaseDrawer::Update()
{
	obj_->Update(animeStatus_);
}

void BaseDrawer::VisibleUpdate()
{
	if (isVisibleUpdate_ == false)
	{
		cbColor_->data_.texColorRate.a_ = 1.0f;

		return;
	}

	// ���_�Ƃ̋���
	float distance = YMath::Vector3(spVP_->eye_ - pParent_->pos_).Length();

	// �`��͈�
	static const float kRange = 750.0f;

	// ���_�Ƃ̋����̔䗦�ŃA���t�@�l�ω�(�����قǔ���)
	float distanceRate = 1.0f - distance / kRange;
	if (distanceRate >= 0.8f) { distanceRate = 1.0f; }

	cbColor_->data_.texColorRate.a_ = distanceRate;

	// ���l�ȉ��͕`��؂�
	isVisible_ = (distanceRate >= 0.25f);
}

void BaseDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	obj_->Draw(shaderKey_, drawPriority_);
}

void BaseDrawer::SetParent(Transform* pParent)
{
	pParent_ = pParent;

	obj_->SetParent(pParent);
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);

	// ���
	spVP_ = pVP;
}

BaseDrawer::BaseDrawer(const uint16_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

BaseDrawer::BaseDrawer(Transform* pParent, const uint16_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void BaseDrawer::DrawDebugTextContent()
{

}
