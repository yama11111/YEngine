#include "Character.h"
#include "CharaConfig.h"
#include "MapChip.h"
#include <cassert>

using YMath::Vector3;
using YGame::SlimeActor;
using YGame::MapChip;
using CharaConfig::GravityPower;

MapChip* Character::pMapChip_ = nullptr;
YGame::ParticleManager* Character::pParticleMan_ = nullptr;

void Character::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pMapChip_);
	assert(state.pParticleMan_);

	pMapChip_ = state.pMapChip_;
	pParticleMan_ = state.pParticleMan_;
}

void Character::Initialize(const CharaStatus::InitStatus& charaState, const YGame::ObjectModel::Status& objState, const YMath::Vector4& color)
{
	obj_.reset(YGame::ObjectModel::Create(objState));
	speed_ = {};
	direction_ = { +1.0f,0.0f,0.0f };
	color_.reset(YGame::Color::Create(color));

	CharaStatus::Initialize(charaState);
	SlimeActor::Initialize();
}

void Character::UpdatePhysics()
{
	// �d�͉��Z
	speed_.y_ -= GravityPower;

	// �}�b�v�`�b�v�Ƃ̃A�^������
	pMapChip_->PerfectPixelCollision(*this);

	// �X�s�[�h���Z
	obj_->pos_ += speed_;

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
}

void Character::Jump(const float jumpSpeed)
{
	// �㏸���Z
	speed_.y_ = jumpSpeed;

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
