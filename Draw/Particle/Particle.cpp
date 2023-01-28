#include "Particle.h"

using YParticle::Dust;

void Dust::Emit(const EmitStatus& state)
{
	YMath::Vec3 scale = { state.scale_, state.scale_, state.scale_ };

	speed_.Initialize(state.speed_, state.speed_ * 0.25f, 3.0f);
	scale_.Initialize(scale, scale * 1.25f, 3.0f);

	obj_.Initialize({ state.pos_, state.rota_});
	alpha_.Initialize(0.75f, 0.0f, 2.0f);

	timer_.Initialize(state.frame_);
	timer_.SetActive(true);
}

void Dust::Update()
{
	if (isAlive_ == false) { return; }

	timer_.Update();
	if (timer_.IsEnd())
	{
		isAlive_ = false;
	}

	obj_.pos_ += speed_.In(timer_.Ratio());
	obj_.scale_ = scale_.In(timer_.Ratio());
	obj_.color_ = { 0.75f, 0.75f, 0.75f, alpha_.In(timer_.Ratio()) };

	obj_.Update();
}

using YParticle::Exprosion;

void Exprosion::Emit(const EmitStatus& state)
{
	YMath::Vec3 scale = { state.scale_, state.scale_, state.scale_ };

	speed_.Initialize(state.speed_, state.speed_ * 0.25f, 3.0f);
	scale_.Initialize(scale, scale * 0.5f, 3.0f);

	obj_.Initialize({ state.pos_, {}});
	color_ = state.color_;
	alpha_.Initialize(0.75f, 0.0f, 2.0f);

	timer_.Initialize(state.frame_);
	timer_.SetActive(true);
}

void Exprosion::Update()
{
	if (isAlive_ == false) { return; }

	timer_.Update();
	if (timer_.IsEnd())
	{
		isAlive_ = false;
	}

	obj_.pos_ += speed_.In(timer_.Ratio());
	obj_.scale_ = scale_.In(timer_.Ratio());

	obj_.color_ = color_;
	obj_.color_.a_ = alpha_.In(timer_.Ratio());

	obj_.Update();
}
