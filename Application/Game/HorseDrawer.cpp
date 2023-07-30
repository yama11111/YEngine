#include "HorseDrawer.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "Def.h"
#include <cmath>

using YGame::HorseDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::HorseAnimationConfig;

Model* HorseDrawer::spModel_ = nullptr;

HorseDrawer* HorseDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	HorseDrawer* newDrawer = new HorseDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void HorseDrawer::StaticInitialize()
{
	// ���f���ݒ�
	spModel_ = Model::LoadObj("horse", true);
}

void HorseDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	// ���f���ݒ�
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";

	HitActor::Initialize();
	SlimeActor::Initialize();
}

void HorseDrawer::InsertAnimationTimers()
{
	// �A�j���[�V�����̐������^�C�}�[�쐬
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eIdle), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eMove), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eJump), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eLanding), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eAttack), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eHit), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eDead), AnimationTimer() });
}

void HorseDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
	// ����
	if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eIdle))
	{
	}
	// �ړ�
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eMove))
	{
		// �y���𔭐�
		// �����̑���
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// ���ʂƋt���� ���� �����
		float rad = pParent_->rota_.y_;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, +0.3f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// �W�����v
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eJump))
	{
		// �u���u���A�j��
		// �L�т�
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(-0.25f, +0.5f, -0.25f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);

		// �y���𔭐�
		// �����̑���
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// ���ʂƋt���� ���� ������
		float rad = pParent_->rota_.y_;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, -1.0f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// ���n
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding))
	{
		// �u���u���A�j��
		// �ׂ��
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.5f, -0.25f, +0.5f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame / static_cast<uint32_t>(wobbleScaleValues.size());

		SlimeActor::Wobble(wobbleScaleValues, wobbleFrame, 3.0f);

		// �y���𔭐�
		// �����̑���
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// �����̎��� ���� �����
		for (size_t i = 0; i < Anime::Landing::kDirectionNum; i++)
		{
			// �p�x = 2�� (360) / �����̐� * index
			float rad = (2.0f * PI / static_cast<float>(Anime::Landing::kDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.3f, 0.0f);

			DustParticle::Emit(Anime::Landing::kDustNum, pParent_->pos_, powerDirection, spVP_);
		}
	}
	// �U��
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eAttack))
	{
	}
	// ��e
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eHit))
	{
		HitActor::Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// ���S
	else if (index & static_cast<uint16_t>(HorseDrawer::AnimationType::eDead))
	{
	}
}

void HorseDrawer::UpdateAnimtion()
{
	HitActor::Update();

	SlimeActor::Update();

	animeStatus_.pos_ += HitActor::ShakePosValue();

	animeStatus_.scale_ += SlimeActor::WobbleScaleValue();

	cbColor_->data_.texColorRate = HitActor::ColorValue();
}