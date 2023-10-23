#include "ShockWaveEmitter.h"
#include "MathVector.h"
#include "ColorConfig.h"
#include "Def.h"
#include <cassert>

using YGame::ShockWaveEmitter;

std::array<ShockWaveEmitter::ShockWave, 10> ShockWaveEmitter::shockWave_;
YGame::ViewProjection* ShockWaveEmitter::spVP_;

namespace
{
	YGame::Sprite3D* pSpr = nullptr;
	const float kScaleValue = 10.0f;
}

void ShockWaveEmitter::LoadResource()
{
	pSpr = Sprite3D::Create({ { "Texture0", Texture::Load("play/circle.png")} });
}

void ShockWaveEmitter::Initialize(ViewProjection* pVP)
{
	for (size_t i = 0; i < shockWave_.size(); i++)
	{
		shockWave_[i].Initialize(pVP);
	}

	spVP_ = pVP;
}

void ShockWaveEmitter::Emit(const YMath::Vector3& pos)
{
	for (size_t i = 0; i < shockWave_.size(); i++)
	{
		if (shockWave_[i].IsAct() == false)
		{
			shockWave_[i].Pop(pos);
			break;
		}
	}
}

void ShockWaveEmitter::Update()
{
	for (size_t i = 0; i < shockWave_.size(); i++)
	{
		shockWave_[i].Update();
	}
}

void ShockWaveEmitter::Draw()
{
	for (size_t i = 0; i < shockWave_.size(); i++)
	{
		shockWave_[i].Draw();
	}
}

void ShockWaveEmitter::ShockWave::Initialize(ViewProjection* pVP)
{
	if (obj_ == nullptr)
	{
		obj_.reset(DrawObjectForSprite3D::Create({}, false, false, pVP, pSpr));
	}
	else
	{
		obj_->Initialize();
	}

	if (cbColor_ == nullptr)
	{
		cbColor_.reset(ConstBufferObject<CBColor>::Create());
	}
	obj_->InsertConstBuffer(cbColor_.get());

	actTim_.Initialize(30);
	scaEas_.Initialize(-kScaleValue, 0.0f, 3.0f);
	alphaEas_.Initialize(1.0f, 0.0f, 2.0f);

	Reset();
}

void ShockWaveEmitter::ShockWave::Reset()
{
	obj_->transform_.Initialize();
	obj_->transform_.scale_ = { kScaleValue, kScaleValue, kScaleValue };
	obj_->transform_.rota_.x_ = kPI / 2.0f;

	cbColor_->data_.baseColor = YGame::ColorConfig::skYellow;
	cbColor_->data_.baseColor.a_ = 0.0f;

	isAct_ = false;

	actTim_.Reset();
}

void ShockWaveEmitter::ShockWave::Update()
{
	if (isAct_ == false) { return; }

	actTim_.Update();

	if (actTim_.IsEnd())
	{
		Reset();
	}

	Transform::Status animeStatus;

	float sca = scaEas_.Out(actTim_.Ratio());
	animeStatus.scale_ += { sca, sca, sca };

	obj_->Update(animeStatus);

	cbColor_->data_.baseColor.a_ = alphaEas_.In(actTim_.Ratio());
}

void ShockWaveEmitter::ShockWave::Draw()
{
	if (isAct_ == false) { return; }

	obj_->Draw("Sprite3DDefault", 1);
}

void ShockWaveEmitter::ShockWave::Pop(const YMath::Vector3& pos)
{
	Reset();

	obj_->transform_.pos_ = pos;

	isAct_ = true;
	actTim_.SetActive(true);
}
