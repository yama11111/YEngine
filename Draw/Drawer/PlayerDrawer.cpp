#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include <cassert>

#pragma region ���O���

using YGame::Transform;
using YGame::ModelObject;
using YGame::Model;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

#pragma region Static

// �ÓI ���f���z�� ������
std::array<std::unique_ptr<Model>, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::sModels_ =
{ nullptr, nullptr, };

void PlayerDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// ��
	sModels_[static_cast<size_t>(Parts::Body)].reset(Model::LoadObj("player/player_body", true));
	sModels_[static_cast<size_t>(1)].reset(Model::LoadObj("player/player_body", true));
}

#pragma endregion

void PlayerDrawer::Initialize(YMath::Matrix4* pParent, Vector3* pDirection)
{
	// null�`�F�b�N
	assert(pParent);
	assert(pDirection);

	// �I�u�W�F�N�g���� + �e�s��}��
	transform_.reset(new Transform());
	transform_->Initialize({});
	transform_->parent_ = pParent;

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ModelObject::Create({}));
		modelObjs_[i]->parent_ = &transform_->m_;
	}

	// �����|�C���^�}��
	pDirection_ = pDirection;

	// ���Z�b�g
	Reset();
}

void PlayerDrawer::Reset()
{
	// ������
	SlimeActor::Initialize();

	transform_->Initialize({});

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	idelTim_.Initialize(DrawerConfig::Player::Idle::IntervalTime);
	idelTim_.SetActive(true);
}

void PlayerDrawer::Update()
{
	// �������[�V�����^�C�}�[�X�V
	idelTim_.Update();

	// �^�C�}�[���I�������
	if (idelTim_.IsEnd())
	{
		// �������[�V�����Đ�
		IdleAnimation();
		// �^�C�}�[���Z�b�g
		idelTim_.Reset(true);
	}

	// �������킹
	Vector3 dire = YMath::AdjustAngle(*pDirection_);

	// �s��X�V (�e)
	transform_->UpdateMatrix(
		{
			-SlimeActor::JiggleValue(),
			dire,
			SlimeActor::JiggleValue()
		}
	);

	// �s��X�V (�q)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void PlayerDrawer::Draw()
{
	// �`��
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i]->Draw(modelObjs_[i].get());
	}
}

void PlayerDrawer::IdleAnimation()
{
	// �L�k��
	Vector3 val = transform_->scale_ * DrawerConfig::Player::Idle::SlimeAction::Value;
	val.y_ *= -1.0f;

	// �Ԃ���
	Vector3 squash = +val;
	// �̂т��
	Vector3 streach = -val;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Idle::SlimeAction::Frame;
	// �w�� (�ɋ})
	float pow = DrawerConfig::Player::Idle::SlimeAction::Power;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}

void PlayerDrawer::JumpAnimation()
{
	// �L�k��
	Vector3 val = transform_->scale_ * DrawerConfig::Player::Jump::SlimeAction::Value;
	val.y_ *= -1.0f;

	// �Ԃ���
	Vector3 squash = +val;
	// �̂т��
	Vector3 streach = -val;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Jump::SlimeAction::Frame;
	// �w�� (�ɋ})
	float pow = DrawerConfig::Player::Jump::SlimeAction::Power;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}

void PlayerDrawer::LandingAnimation()
{
	// �Ԃ���
	Vector3 squash = transform_->scale_ * DrawerConfig::Player::Landing::SlimeAction::Value;
	squash.y_ *= -1.0f;

	// ���� (�t���[��)
	unsigned int frame = DrawerConfig::Player::Landing::SlimeAction::Frame;
	// �w�� (�ɋ})
	float exponent = DrawerConfig::Player::Landing::SlimeAction::Power;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);
}


