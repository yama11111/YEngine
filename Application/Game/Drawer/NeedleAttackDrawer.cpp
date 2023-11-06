#include "NeedleAttackDrawer.h"
#include "DrawObjectForModel.h"
#include "Lerp.h"
#include "WaveParticle.h"
#include "CharacterConfig.h"
#include "ColorConfig.h"
#include "Def.h"

using YGame::NeedleAttackDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	// モデルポインタ
	Model* pModel = nullptr;
}

NeedleAttackDrawer* NeedleAttackDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	NeedleAttackDrawer* newDrawer = new NeedleAttackDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void NeedleAttackDrawer::LoadResource()
{
	pModel = Model::LoadObj("needle", true);
}

void NeedleAttackDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	cbOutline_.reset(ConstBufferObject<CBOutline>::Create());
	cbOutline_->data_.color = ColorConfig::skTurquoise[0];
	cbOutline_->data_.range = 0.2f;

	InsertConstBuffer("Attack_O", cbOutline_.get());

	SetShaderTag("ModelToon");
	SetShaderTag("Attack_O", "ModelOutline");

	slimeActor_.Initialize(0, { {} }, 0);

	rotaEas_.Initialize(0.0f, kPI * 4.0f, 3.0f);

	popTimer_.Initialize(8);
	vanishTimer_.Initialize(8);
	
	wavePopTimer_.Initialize(4);
}

void NeedleAttackDrawer::InitializeObjects()
{
	InsertObject("Attack", DrawObjectForModel::Create(Transform::Status::Default(), spVP_, pModel));
	InsertObject("Attack_O", DrawObjectForModel::Create(Transform::Status::Default(), spVP_, pModel));
}

void NeedleAttackDrawer::InitializeTimers()
{
	InsertAnimationTimer(static_cast<uint32_t>(AnimationType::eAttack), AnimationTimer(YMath::Timer(NeedleAttackConfig::kAliveTime), false));
}

void NeedleAttackDrawer::GetReadyForAnimation(const uint32_t index)
{
	// 時間
	const uint32_t frame = animationTimers_[index].timer.EndFrame();

	if (index & static_cast<uint32_t>(AnimationType::eAttack))
	{
		// ブヨブヨアニメ
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(-1.0f, -1.0f, -1.0f));
		wobbleScaleValues.push_back(Vector3(+0.1f, +0.1f, +0.1f));
		wobbleScaleValues.push_back(Vector3(+0.0f, +0.0f, +0.0f));

		uint32_t wobbleFrame = frame / 2;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();

		popTimer_.Reset(true);
		vanishTimer_.Reset();
		
		wavePopTimer_.Reset(true);
	}
}

void NeedleAttackDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	animeStatus_.rota_.z_ += rotaEas_.In(animationTimers_[static_cast<uint32_t>(AnimationType::eAttack)].timer.Ratio());

	popTimer_.Update();
	vanishTimer_.Update();

	uint32_t frame =
		animationTimers_[static_cast<uint32_t>(AnimationType::eAttack)].timer.EndFrame() -
		static_cast<uint32_t>(animationTimers_[static_cast<uint32_t>(AnimationType::eAttack)].timer.Current());

	if (frame <= vanishTimer_.EndFrame())
	{
		vanishTimer_.SetActive(true);
	}
	
	if (popTimer_.IsAct())
	{
		//animeStatus_.scale_ += YMath::EaseOut<Vector3>(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), popTimer_.Ratio(), 2.0f);
		cbColor_->data_.baseColor.a_ = YMath::EaseOut<float>(0.0f, 1.0f, popTimer_.Ratio(), 2.0f);
	}

	if (vanishTimer_.IsAct())
	{
		cbColor_->data_.baseColor.a_ = YMath::EaseIn<float>(1.0f, 0.0f, vanishTimer_.Ratio(), 2.0f);
		animeStatus_.scale_ += YMath::EaseIn<Vector3>(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), vanishTimer_.Ratio(), 2.0f);
	}

	wavePopTimer_.Update();
	if (wavePopTimer_.IsEnd())
	{
		wavePopTimer_.Reset(true);
		WaveParticle::Emit(10, pParent_->pos_, {0.0f, kPI / 2.0f, 0.0f}, 3.0f, ColorConfig::skTurquoise[0], spVP_);
	}
}