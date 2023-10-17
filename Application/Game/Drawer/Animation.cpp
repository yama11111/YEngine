#include "Animation.h"
#include <cassert>

using YGame::Animation;
using YMath::Timer;

void Animation::Clear()
{
	animationBitFlag_ = 0;
	
	if (animationTimers_.empty() == false)
	{
		animationTimers_.clear();
	}
}

void Animation::InsertAnimationTimer(const uint32_t index, const uint32_t endFrame, const bool isRoop)
{
	AnimationTimer animeTimer;
	animeTimer.timer.Initialize(endFrame);
	animeTimer.isRoop = isRoop;

	// 既にあるなら入れ替え
	if (animationTimers_.contains(index))
	{
		animationTimers_[index] = animeTimer;
	}
	else
	{
		animationTimers_.insert({ index, animeTimer });
	}

	// フラグを降ろす
	animationBitFlag_ &= ~index;
}

void Animation::UpdateTimer()
{
	for (auto itr = animationTimers_.begin(); itr != animationTimers_.end(); ++itr)
	{
		// アニメーションしないなら飛ばす
		if ((animationBitFlag_ & itr->first) == 0) { continue; }

		YMath::Timer& timer = itr->second.timer;

		timer.Update();

		if (timer.IsEnd())
		{
			if (itr->second.isRoop)
			{
				// アニメーションをもう一度始める
				StartTimer(itr->first);
				timer.Reset(true);
			}
			else
			{
				timer.Initialize(0);

				// フラグをおろす
				animationBitFlag_ &= ~itr->first;
			}
		}
	}
}

//void Animation::Update(const Transform::Status& status)
void Animation::Update()
{
	//animeStatus_ = {};

	//animeStatus_.pos_	 += status.pos_;
	//animeStatus_.rota_	 += status.rota_;
	//animeStatus_.scale_	 += status.scale_;

	UpdateTimer();

	//UpdateAnimation();
}

void Animation::ResetTimer(const uint32_t index, const uint32_t endFrame, const bool isRoop)
{
	assert(animationTimers_.contains(index));

	animationTimers_[index].timer.Initialize(endFrame, false);
	animationTimers_[index].isRoop = isRoop;

	// フラグを降ろす
	animationBitFlag_ &= ~index;
}

void Animation::StartTimer(const uint32_t index)
{
	assert(animationTimers_.contains(index));

	animationTimers_[index].timer.Reset(true);

	// フラグを立てる
	animationBitFlag_ |= index;
}

void Animation::StopTimer(const uint32_t index)
{
	assert(animationTimers_.contains(index));

	animationTimers_[index].timer.SetActive(false);

	// フラグを降ろす
	animationBitFlag_ &= ~index;
}

float Animation::TimerRatio(const uint32_t index)
{
	assert(animationTimers_.contains(index));
	
	return animationTimers_[index].timer.Ratio();
}

