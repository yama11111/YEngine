#include "Character.h"
#include "CharaConfig.h"
#include "MapChip.h"
#include "MathUtillity.h"
#include <cassert>

using YMath::Vector3;
using YGame::SlimeActor;
using YGame::MapChip;

MapChip* Character::pMapChip_ = nullptr;
YGame::ParticleManager* Character::pParticleMan_ = nullptr;

void Character::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pMapChip_);
	assert(state.pParticleMan_);

	pMapChip_ = state.pMapChip_;
	pParticleMan_ = state.pParticleMan_;
}

void Character::Initialize(
	const CharaStatus::InitStatus& charaStatus, const YGame::Transform::Status& objStatus,
	const YMath::Vector3& acceleration, const YMath::Vector3& max,
	const YMath::Vector4& color)
{
	obj_.reset(YGame::ModelObject::Create(objStatus));
	speed_.Initialize(acceleration, max);
	color_.reset(YGame::Color::Create(color));

	Reset(charaStatus, objStatus);
}

void Character::Reset(const CharaStatus::InitStatus& charaStatus, const YGame::Transform::Status& objStatus, const YMath::Vector4& color)
{
	CharaStatus::Initialize(charaStatus);
	SlimeActor::Initialize();

	obj_->Initialize(objStatus);
	speed_.Reset();
	direction_ = { +1.0f,0.0f,0.0f };
	color_->Initialize(color);
}

void Character::UpdatePhysics()
{
	// �͈͐���
	move_.x_ = YMath::Clamp(move_.x_, -1.0f, 1.0f);
	move_.y_ = YMath::Clamp(move_.y_, -1.0f, 1.0f);
	move_.z_ = YMath::Clamp(move_.z_, -1.0f, 1.0f);

	// �X�s�[�h���Z
	speed_.Update(move_);

	// �}�b�v�`�b�v�Ƃ̃A�^������
	pMapChip_->PerfectPixelCollision(*this);

	// �X�s�[�h���Z
	obj_->pos_ += speed_.Value();

	// ���n�����u��
	if (IsElderLanding() == false && IsLanding())
	{
		Vector3 squash = obj_->scale_ * CharaConfig::SlimeAct::SquashValue;
		squash.y_ *= -1.0f;

		unsigned int frame = CharaConfig::SlimeAct::Frame;
		float pow = CharaConfig::SlimeAct::Power;

		SlimeActor::Activate(
			{
				{{}, frame, pow},
				{squash, frame, pow},
				{{}, frame, pow}
			}
		);
	}

	// �ړ�����������
	move_.x_ = 0.0f;
	move_.y_ = 0.0f;
	move_.z_ = 0.0f;
}

void Character::Jump()
{
	// �㏸
	move_.y_ = 1.0f;

	Vector3 val = obj_->scale_ * CharaConfig::SlimeAct::ElasticityValue;
	val.y_ *= -1.0f;

	Vector3 squash = +val;
	Vector3 streach = -val;

	unsigned int frame = CharaConfig::SlimeAct::Frame;
	float pow = CharaConfig::SlimeAct::Power;

	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}

void Character::Update()
{
	CharaStatus::Update();
	SlimeActor::Update();
	
	if (obj_->pos_.y_ <= -200.0f)
	{
		Hit(1000);
	}

	if (isAlive()) 
	{
		
	}
}
