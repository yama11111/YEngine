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
	Sprite3D* pSpr = nullptr;

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
	pSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/gate.png", false)} });
}

void GateDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	transform_.rota_ = YMath::AdjustAngle(Vector3(1.0f, 0.0f, 0.0f));
	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	cbColor_->data_.baseColor = ColorConfig::skYellow;
	//cbColor_->data_.baseColor.a_ = 0.4f;
	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);
	SetShaderTag("Sprite3DDefault");

	passRotaEas_.Initialize(0.0f, 4.0f * kPI, 3.0f);
	passScaleEas_.Initialize(0.0f, 15.0f, 2.0f);
}

void GateDrawer::InitializeObjects()
{
	InsertObject("Gate_F", DrawObjectForSprite3D::Create({}, false, false, spVP_, pSpr));
	//InsertObject("Gate_B", DrawObjectForSprite3D::Create({}, false, false, spVP_, pSpr));
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

	objs_["Gate_F"]->transform_.rota_.z_ += 0.01f + rota;
	//objs_["Gate_B"]->transform_.rota_.z_ -= 0.01f + rota;
}