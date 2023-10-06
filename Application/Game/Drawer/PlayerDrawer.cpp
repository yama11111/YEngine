#include "PlayerDrawer.h"
#include "AnimationConfig.h"
#include "DustParticle.h"
#include "DebriParticle.h"
#include <cmath>
#include "Def.h"

using YGame::PlayerDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Timer;
namespace Anime = YGame::PlayerAnimationConfig;

std::array<Model*, 3> PlayerDrawer::spModels_ = { nullptr, nullptr, nullptr };

PlayerDrawer* PlayerDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	PlayerDrawer* newDrawer = new PlayerDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void PlayerDrawer::LoadResource()
{
	// ���f���ݒ�
	spModels_[1] = Model::LoadObj("player/body", true);
	spModels_[0] = Model::LoadObj("player/leg_L", true);
	spModels_[2] = Model::LoadObj("player/leg_R", true);
}

void PlayerDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// �I�u�W�F�N�g������
	BaseDrawer::Initialize(pParent, drawPriority);

	// ���f���ݒ�
	obj_->SetModel(spModels_[0]);

	shaderKey_ = "ModelToon";

	slimeActor_.Initialize(0, { {} }, 0);
	hitActor_.Initialize();
}

void PlayerDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	for (size_t i = 0; i < spModels_.size(); i++)
	{
		obj_->Draw(shaderKey_, drawPriority_, spModels_[i]);
	}
}

void PlayerDrawer::InsertAnimationTimers()
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

void PlayerDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
	// ����
	if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eIdle))
	{
	}
	// �ړ�
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eMove))
	{
		// �y���𔭐�
		// �����̑���
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// ���ʂƋt���� ���� �����
		float rad = pParent_->rota_.y_;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, +0.1f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// �W�����v
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eJump))
	{
		// �u���u���A�j��
		// �L�т�
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));
		wobbleScaleValues.push_back(Vector3(-0.25f, +0.5f, -0.25f));
		wobbleScaleValues.push_back(Vector3(0.0f, 0.0f, 0.0f));

		uint32_t wobbleFrame = frame;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();

		// �y���𔭐�
		// �����̑���
		float height = 0.5f;
		Vector3 pos = pParent_->pos_ - Vector3(0.0f, height, 0.0f);

		// ���ʂƋt���� ���� ������
		float rad = pParent_->rota_.y_;
		Vector3 front = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();
		Vector3 powerDirection = -front + Vector3(0.0f, -0.5f, 0.0f);

		DustParticle::Emit(Anime::Move::kDustNum, pParent_->pos_, powerDirection, spVP_);
	}
	// ���n
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eLanding))
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
			float rad = (2.0f * kPI / static_cast<float>(Anime::Landing::kDirectionNum)) * i;
			Vector3 surrounding = Vector3(std::sinf(rad), 0.0f, std::cosf(rad)).Normalized();

			Vector3 powerDirection = surrounding + Vector3(0.0f, +0.1f, 0.0f);

			DustParticle::Emit(Anime::Landing::kDustNum, pParent_->pos_, powerDirection, spVP_);
		}
	}
	// �U��
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eAttack))
	{
	}
	// ��e
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eHit))
	{
		hitActor_.Hit(
			Anime::Hit::kSwing,
			Anime::Hit::kSwing / static_cast<float>(frame),
			100.0f);
	}
	// ���S
	else if (index & static_cast<uint16_t>(PlayerDrawer::AnimationType::eDead))
	{
		DebriParticle::Emit(Anime::Dead::kDebriNum, pParent_->pos_, spVP_);
	}
}

void PlayerDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);
	
	cbColor_->data_.texColorRate = hitActor_.ColorValue();
}