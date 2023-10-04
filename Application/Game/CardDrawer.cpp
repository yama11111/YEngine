#include "CardDrawer.h"
#include "MathVector.h"
#include <cassert>

using YGame::CardDrawer;
using YMath::Vector3;

YGame::Sprite2D* CardDrawer::spCardSpr_ = nullptr;

void CardDrawer::LoadResource()
{
	spCardSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("select/card.png")} });
}

void CardDrawer::Initialize(Transform* pParent, const int32_t number, const bool isClear)
{
	assert(0 < number);
	number_ = number;

	// ----- ���� ----- //

	// �j
	core_ = Transform::Status::Default();
	core_.parent_ = &pParent->m_;

	// �F
	color_.reset(ConstBufferObject<CBColor>::Create());

	// �N���A�F
	//clearCharaColor_.reset(CBColor::Create());

	// �X�e�[�W�J�[�h�I�u�W�F�N�g
	cardObj_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spCardSpr_));
	cardObj_->SetParent(&core_.m_);

	// ����
	numberTra_.Initialize({ {}, {}, {0.5f,0.5f,0.0f} });
	numberTra_.parent_ = &core_.m_;
	numberUI_.reset(UINumber::Create2D(static_cast<uint32_t>(number_), 2, 64.0f, false, &numberTra_.m_));

	// ���Z�b�g
	Reset(isClear);
}

void CardDrawer::Reset(const bool isClear)
{
	// ----- �I�u�W�F�N�g������ ----- //

	// �j
	core_.Initialize();

	// ����
	numberTra_.Initialize({ {}, {}, {0.5f,0.5f,0.0f} });
	
	// �J�[�h
	cardObj_->Initialize();
	cardObj_->SetParent(&core_.m_);

	// �F������
	color_->data_.baseColor = { 1.0f,1.0f,1.0f,1.0f };

	// �F������
	//clearCharaColor_->SetRGBA({ 1.0f,1.0f,0.0f,1.0f });

	// ----- �A�j���[�V���� ----- //

	// �I������Ă��邩
	isSelected_ = false;
	// �I������Ă�����
	isElderSelected_ = false;
	// ���肳�ꂽ��
	isDecided_ = false;

	// �ړ��p�C�[�W���O
	moveEas_.Initialize(0.0f, -128.0f, 1.2f);
	// �g��p�C�[�W���O
	scaleEas_.Initialize(0.0f, 0.25f, 1.2f);
	// �I��p�p���[
	selectPow_.Initialize(10);

	// �N���A������
	isClear_ = isClear;
}

void CardDrawer::UpdateSelectAnimation()
{
	// ----- �u���u���A�j���[�V���� ----- //
	
	//// �I�����ꂽ�u��
	//if (isSelected_ && isElderSelected_ == false)
	//{
	//	// �L�k��
	//	Vector3 val = core_->scale_ * SlimeAction::Value;

	//	// �ׂ��L�΂�
	//	Vector3 squash = +val;
	//	Vector3 streach = -val;

	//	// ����
	//	unsigned int frame = SlimeAction::Frame;
	//	// �w��
	//	float exponent = SlimeAction::Exponent;

	//	// ���삷��
	//	SlimeActor::Activate(
	//		{ 
	//			{ {}, frame, exponent},
	//			{ streach, frame, exponent },
	//			{ squash, frame, exponent },
	//			{ {}, frame, exponent }
	//		}
	//	);
	//}

	// �I�����L�^
	isElderSelected_ = isSelected_;


	// -------- �A�j���[�V���� --------- //

	// �I�𒆂Ȃ�p���[�X�V
	selectPow_.Update(isSelected_);
	
	// ----- �ړ� ----- //

	// �ړ���
	float moveVal = 0.0f;
	
	// �I�΂�Ă���Ȃ�
	if (isSelected_)
	{
		// �C�[�Y�C�����
		moveVal = moveEas_.In(selectPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�A�E�g���
		moveVal = moveEas_.Out(selectPow_.Ratio());
	}

	// �ړ��ʑ��
	core_.pos_.x_ = moveVal;

	
	// ----- �g�� ----- //

	// �ړ���
	float scaleVal = 0.0f;

	// �I�΂�Ă���Ȃ�
	if (isSelected_)
	{
		// �C�[�Y�C�����
		scaleVal = scaleEas_.In(selectPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�A�E�g���
		scaleVal = scaleEas_.Out(selectPow_.Ratio());
	}

	// �ړ��ʑ��
	core_.scale_ = Vector3(1.0f, 1.0f, 1.0f) + Vector3(scaleVal, scaleVal, 0.0f);

	
	// -------------- �F -------------- //

	// �F�̒l
	Vector3 colorVal = {};
	Vector3 clearColorVal = {};

	// �I�΂�Ă���Ȃ�
	if (isSelected_)
	{
		// �ʏ�F��
		colorVal = { 1.0f,1.0f,1.0f };
		clearColorVal = { 0.25f,1.0f,0.75f };
	}
	// ����ȊO�Ȃ�
	else
	{
		// �Â��F��
		colorVal = { 0.25f,0.25f,0.25f };
		clearColorVal = Vector3(0.25f, 1.0f, 0.75f) * 0.25f;
	}

	// �F�ݒ�
	YMath::Vector4 color = { colorVal.x_,colorVal.y_,colorVal.z_,color_->data_.baseColor.a_ };
	color_->data_.baseColor = color;
	//clearCharaColor_->SetRGB(clearColorVal);
}

void CardDrawer::Update()
{
	// �I���A�j���[�V�����X�V
	UpdateSelectAnimation();

	// �j
	core_.UpdateMatrix();

	// ����
	numberTra_.UpdateMatrix();
	numberUI_->Update();

	// �J�[�h
	cardObj_->Update();
}

void CardDrawer::Draw(uint16_t p)
{
	cardObj_->Draw("Sprite2DDefault", p + 2);
	numberUI_->Draw("Sprite2DDefault", p + 1);
}
