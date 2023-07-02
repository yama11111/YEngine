#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// �I�u�W�F�N�g����
	obj_.reset(Model::Object::Create());

	// �e�ݒ�
	SetParent(pParent);

	// �F
	color_.reset(CBColor::Create());
	obj_->SetColor(color_.get());
	
	// �}�e���A��
	material_.reset(CBMaterial::Create());
	material_->SetAmbient({ 0.2f,0.2f,0.2f });
	obj_->SetMaterial(material_.get());
	
	// �e�N�X�`���ݒ�
	texConfig_.reset(CBTexConfig::Create());
	obj_->SetTexConfig(texConfig_.get());

	// �r���[�v���W�F�N�V�����ݒ�
	obj_->SetViewProjection(spVP_);

	// �`��ʒu
	location_ = location;

	// �`��t���O
	isVisible_ = true;

	// �`�悷�邩�X�V�t���O
	isVisibleUpdate_ = true;
}

void BaseDrawer::Update()
{
	VisibleUpdate();

	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void BaseDrawer::VisibleUpdate()
{
	if (isVisibleUpdate_ == false)
	{
		color_->SetTexColorRateAlpha(1.0f);

		return;
	}

	// ���_�Ƃ̋���
	float distance = YMath::Vector3(spVP_->eye_ - pParent_->pos_).Length();

	// �`��͈�
	static const float kRange = 750.0f;

	float distaceRate = 1.0f - distance / kRange;
	if (distaceRate >= 0.8f) { distaceRate = 1.0f; }

	// ���_�Ƃ̋����̔䗦�ŃA���t�@�l�ω�(�����قǔ���)
	color_->SetTexColorRateAlpha(distaceRate);

	// ���l�ȉ��͕`��؂�
	isVisible_ = (color_->GetTexColorRate().a_ >= 0.25f);
}

void BaseDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	// �`��
	pModel_->SetDrawCommand(obj_.get(), location_, shader_);
}

void BaseDrawer::SetParent(Transform* pParent)
{
	// �e�g�����X�t�H�[���|�C���^�ݒ�
	pParent_ = pParent;

	// null ����Ȃ��Ȃ�
	if (pParent_)
	{
		// �e�q�֌W�ݒ�
		obj_->parent_ = &pParent_->m_;
	}
	// �Ⴄ�Ȃ�
	else
	{
		// �e�q�֌W������
		obj_->parent_ = nullptr;
	}
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);

	// ���
	spVP_ = pVP;
}

BaseDrawer::BaseDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

BaseDrawer::BaseDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void BaseDrawer::DrawDebugTextContent()
{

}
