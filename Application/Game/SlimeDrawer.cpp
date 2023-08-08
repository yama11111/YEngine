#include "SlimeDrawer.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "DebriParticle.h"
#include "Def.h"
#include <cmath>

using YGame::SlimeDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::SlimeAnimationConfig;

Model* SlimeDrawer::spModel_ = nullptr;

SlimeDrawer* SlimeDrawer::Create(Transform* pParent, const uint16_t drawPriority)
{
	SlimeDrawer* newDrawer = new SlimeDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SlimeDrawer::StaticInitialize()
{
	spModel_ = Model::LoadObj("slime", true);
}

void SlimeDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	// ���f���ݒ�
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";

	hitActor_.Initialize();
	slimeActor_.Initialize(0, { {} }, 0);
}

void SlimeDrawer::InsertAnimationTimers()
{
	// �A�j���[�V�����̐������^�C�}�[�쐬
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eIdle), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eLanding), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eHit), AnimationTimer() });
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eDead), AnimationTimer() });
}

void SlimeDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
	// ����
	if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eIdle))
	{
	}
	// ���n
	else if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eLanding))
	{
		// �u���u���A�j��
		// �ׂ��
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(+0.5f, -0.25f, +0.5f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();

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
	// ��e
	else if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eHit))
	{
		hitActor_.Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// ���S
	else if (index & static_cast<uint16_t>(SlimeDrawer::AnimationType::eDead))
	{
		DebriParticle::Emit(Anime::Dead::kDebriNum, pParent_->pos_, spVP_);
	}
}

void SlimeDrawer::UpdateAnimtion()
{
	hitActor_.Update();

	slimeActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	cbColor_->data_.texColorRate = hitActor_.ColorValue();
}