#include "PlayerDrawer.h"
#include "CalcTransform.h"
#include "CharaConfig.h"
#include <cassert>

#pragma region ���O���

using YGame::Model;
using YGame::Color;
using YGame::ObjectModel;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

#pragma region Static

// �ÓI ���f���z�� ������
std::array<std::unique_ptr<Model>, PlayerDrawerCommon::PartsNum_> PlayerDrawerCommon::models_ =
{ nullptr, nullptr, };

void PlayerDrawerCommon::StaticInitialize()
{
	// ----- ���f���ǂݍ��� ----- //

	// ��
	models_[static_cast<size_t>(Parts::Body)].reset(Model::LoadObj("player/player_body", true));
	models_[static_cast<size_t>(1)].reset(Model::LoadObj("player/player_body", true));
}

#pragma endregion

void PlayerDrawer::Initialize(YMath::Matrix4* pParent, Vector3* pDirection)
{
	// null�`�F�b�N
	assert(pParent);
	assert(pDirection);

	// �I�u�W�F�N�g���� + �e�s��}��
	obj_.reset(ObjectModel::Create({}));
	obj_->parent_ = pParent;

	// �I�u�W�F�N�g���� + �e�s��}�� (�p�[�c�̐�)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ObjectModel::Create({}));
		modelObjs_[i]->parent_ = &obj_->m_;
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

	obj_->Initialize({});

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	idelTim_.Initialize(CharaConfig::Player::IdleIntervalFrame);
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
	obj_->UpdateMatrix(
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

void PlayerDrawer::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup)
{
	// �`��
	for (size_t i = 0; i < models_.size(); i++)
	{
		models_[i]->Draw(modelObjs_[i].get(), vp, lightGroup);
	}
}

void PlayerDrawer::IdleAnimation()
{
	// �L�k��
	Vector3 val = obj_->scale_ * CharaConfig::SlimeAct::ElasticityValue;
	val.y_ *= -1.0f;

	// �Ԃ���
	Vector3 squash = +val;
	// �̂т��
	Vector3 streach = -val;

	// ���� (�t���[��)
	unsigned int frame = CharaConfig::SlimeAct::Frame;
	// �w�� (�ɋ})
	float pow = CharaConfig::SlimeAct::Power;

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
	Vector3 squash = obj_->scale_ * CharaConfig::SlimeAct::SquashValue;
	squash.y_ *= -1.0f;

	// ���� (�t���[��)
	unsigned int frame = CharaConfig::SlimeAct::Frame;
	// �w�� (�ɋ})
	float exponent = CharaConfig::SlimeAct::Power;

	// �Ղ�Ղ�A�j���[�V����
	SlimeActor::Activate(
		{
			{{}, frame, exponent},
			{squash, frame, exponent},
			{{}, frame, exponent}
		}
	);
}

void PlayerDrawer::JumpAnimation()
{
	// �L�k��
	Vector3 val = obj_->scale_ * CharaConfig::SlimeAct::ElasticityValue;
	val.y_ *= -1.0f;

	// �Ԃ���
	Vector3 squash = +val;
	// �̂т��
	Vector3 streach = -val;

	// ���� (�t���[��)
	unsigned int frame = CharaConfig::SlimeAct::Frame;
	// �w�� (�ɋ})
	float pow = CharaConfig::SlimeAct::Power;

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

