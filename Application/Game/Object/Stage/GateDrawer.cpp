#include "GateDrawer.h"
#include "DrawObjectForSprite3D.h"
#include "ColorConfig.h"
#include "MathVector.h"
#include "Def.h"

using YGame::GateDrawer;
using YGame::Sprite3D;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Timer;

namespace
{
	Sprite3D* pFrameSpr = nullptr;
	Sprite3D* pInsideSpr = nullptr;

	// アニメーション番号
	const uint32_t kIdleIndex = static_cast<uint32_t>(GateDrawer::AnimationType::eIdle);
	const uint32_t kPassIndex = static_cast<uint32_t>(GateDrawer::AnimationType::ePass);
}

std::unique_ptr<GateDrawer> GateDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	std::unique_ptr<GateDrawer> newDrawer = std::make_unique<GateDrawer>();

	newDrawer->Initialize(pParent, drawPriority);

	return std::move(newDrawer);
}

void GateDrawer::LoadResource()
{
	pFrameSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/gate_frame.png", false)} });
	pInsideSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/gate_inside.png", false)} });
}

void GateDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	if (cbInsideColor_ == nullptr)
	{
		cbInsideColor_.reset(ConstBufferObject<CBColor>::Create());
		InsertConstBuffer("Gate_Inside", cbInsideColor_.get());
	}

	transform_.rota_ = YMath::AdjustAngle(Vector3(1.0f, 0.0f, 0.0f));
	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	cbColor_->data_.baseColor = ColorConfig::skYellow;
	cbInsideColor_->data_.baseColor = ColorConfig::skMagenta;
	
	SetShaderTag("Sprite3DDefault");

	passRotaEas_.Initialize(0.0f, 4.0f * kPI, 3.0f);
	passScaleEas_.Initialize(0.0f, 15.0f, 2.0f);
}

void GateDrawer::InitializeObjects()
{
	InsertObject("Gate_Frame", DrawObjectForSprite3D::Create({}, false, false, spVP_, pFrameSpr));
	InsertObject("Gate_Inside", DrawObjectForSprite3D::Create({}, false, false, spVP_, pInsideSpr));
}

void GateDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, AnimationTimer(Timer(120), true));
	InsertAnimationTimer(kPassIndex, AnimationTimer(Timer(30), false));
}

void GateDrawer::GetReadyForAnimation(const uint32_t index)
{
	if (index & static_cast<uint32_t>(AnimationType::eIdle))
	{

	}
	else if (index & static_cast<uint32_t>(AnimationType::ePass))
	{
	}
}

void GateDrawer::UpdateAnimation()
{
	float ratio = animationTimers_[kPassIndex].timer.Ratio();
	
	float rota = passRotaEas_.Out(ratio);
	float scale = passScaleEas_.Out(ratio);

	animeStatus_.scale_.x_ += scale;
	animeStatus_.scale_.y_ += scale;

	objs_["Gate_Frame"]->transform_.rota_.z_ += 0.01f + rota;
	objs_["Gate_Inside"]->transform_.rota_.z_ += 0.01f + rota;
}