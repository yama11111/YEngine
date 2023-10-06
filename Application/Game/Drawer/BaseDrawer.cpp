#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{	
	if (obj_ == nullptr)
	{
		// �I�u�W�F�N�g + �萔�o�b�t�@����
		obj_.reset(DrawObjectForModel::Create({}, spVP_, nullptr));
		
		cbColor_.reset(ConstBufferObject<CBColor>::Create());

		cbMaterial_.reset(ConstBufferObject<CBMaterial>::Create());
	}

	obj_->Initialize();

	// �I�u�W�F�N�g�ɒ萔�o�b�t�@��ݒ�
	obj_->InsertConstBuffer(cbColor_.get());
	obj_->InsertConstBuffer(cbMaterial_.get());
	
	SetParent(pParent);
	
	// �������Â߂�
	cbMaterial_->data_.ambient = { 0.2f,0.2f,0.2f };

	drawPriority_ = drawPriority;

	isVisible_ = true;

	isVisibleUpdate_ = true;

	animationBitFlag_ = 0;

	// �^�C�}�[�N���A��A�đ}�� + ������
	animationTimers_.clear();

	InsertAnimationTimers();

	for (auto itr = animationTimers_.begin(); itr != animationTimers_.end(); ++itr)
	{
		itr->second.timer.Initialize(0);
	}

	animeStatus_ = {};
}

void BaseDrawer::PlayAnimation(const uint16_t index, const uint32_t frame, const bool isRoop)
{
	assert(animationTimers_.contains(index));

	PlaySubAnimation(index, frame);

	animationTimers_[index].timer.Initialize(frame, true);
	animationTimers_[index].isRoop = isRoop;

	// �t���O�𗧂Ă�
	animationBitFlag_ |= index;
}

void BaseDrawer::AbortAnimation(const uint16_t index)
{
	assert(animationTimers_.contains(index));
	
	animationTimers_[index].timer.Initialize(0);
	
	// �t���O�����낷
	animationBitFlag_ &= ~index;
}

void BaseDrawer::Update()
{
	animeStatus_ = {};

	animeStatus_.pos_ += offset_;

	UpdateAnimationTimer();

	UpdateAnimation();

	obj_->Update(animeStatus_);

	VisibleUpdate();
}

void BaseDrawer::UpdateAnimationTimer()
{
	for (auto itr = animationTimers_.begin(); itr != animationTimers_.end(); ++itr)
	{
		// �A�j���[�V�������Ȃ��Ȃ��΂�
		if ((animationBitFlag_ & itr->first) == 0) { continue; }

		YMath::Timer& timer = itr->second.timer;

		timer.Update();

		if (timer.IsEnd())
		{
			if (itr->second.isRoop)
			{
				// �A�j���[�V������������x�n�߂�
				PlaySubAnimation(itr->first, timer.EndFrame());
				timer.Reset(true);
			}
			else
			{
				timer.Initialize(0);

				// �t���O�����낷
				animationBitFlag_ &= ~itr->first;
			}
		}
	}
}

void BaseDrawer::VisibleUpdate()
{
	if (isVisibleUpdate_ == false) { return; }

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

void BaseDrawer::DrawDebugTextContent()
{
}

void BaseDrawer::SetParent(Transform* pParent)
{
	if (pParent)
	{
		pParent_ = pParent;

		obj_->SetParent(&pParent->m_);
	}
	else
	{
		pParent_ = nullptr;

		obj_->SetParent(nullptr);
	}
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	assert(pVP);

	spVP_ = pVP;
}
