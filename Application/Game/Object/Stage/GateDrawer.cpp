#include "GateDrawer.h"
#include "DrawObjectForSprite3D.h"
#include "ViewProjectionManager.h"
#include "ColorConfig.h"
#include "MathVector.h"
#include "Def.h"

using YGame::GateDrawer;
using YGame::Sprite3D;
using YGame::ViewProjectionManager;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Timer;

namespace
{
	Sprite3D* pFrameSpr = nullptr;
	Sprite3D* pInsideSpr = nullptr;

	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
	
	// アニメーション番号
	const uint32_t kIdleIndex = static_cast<uint32_t>(GateDrawer::AnimationType::eIdle);
	const uint32_t kExtendIndex = static_cast<uint32_t>(GateDrawer::AnimationType::eExtend);
	const uint32_t kShrinkIndex = static_cast<uint32_t>(GateDrawer::AnimationType::eShrink);
}

std::unique_ptr<GateDrawer> GateDrawer::Create(const DrawerInitSet& init)
{
	std::unique_ptr<GateDrawer> newDrawer = std::make_unique<GateDrawer>();

	newDrawer->Initialize(init);

	return std::move(newDrawer);
}

void GateDrawer::LoadResource()
{
	pFrameSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/gate_frame.png", false)} });
	pInsideSpr = Sprite3D::Create({ {"Texture0", Texture::Load("play/gate_inside.png", false)} });
}

void GateDrawer::Initialize(const DrawerInitSet& init)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(init);


	if (cbInsideColor_ == nullptr)
	{
		cbInsideColor_.reset(ConstBufferObject<CBColor>::Create());
		InsertConstBuffer("Gate_Inside", cbInsideColor_.get());
	}

	transform_.rota_ = YMath::AdjustAngle(Vector3(1.0f, 0.0f, 0.0f));
	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	cbColor_->data_.baseColor = ColorConfig::skYellow;
	cbInsideColor_->data_.baseColor = ColorConfig::skMagenta;
	//cbInsideColor_->data_.baseColor = {};
	
	SetShaderTag("Sprite3DDefault");

	extendRotaEas_.Initialize(0.0f, 4.0f * kPI, 3.0f);
	extendScaleEas_.Initialize(0.0f, 15.0f, 2.0f);
	
	shrinkRotaEas_.Initialize(0.0f, 4.0f * kPI, 3.0f);
	shrinkScaleEas_.Initialize(0.0f, -15.0f, 2.0f);
}

void GateDrawer::InitializeObjects()
{
	InsertObject("Gate_Frame", DrawObjectForSprite3D::Create({}, false, false, 
		pVPMan->ViewProjectionPtr(vpKey_), pFrameSpr));
	InsertObject("Gate_Inside", DrawObjectForSprite3D::Create({}, false, false, 
		pVPMan->ViewProjectionPtr(vpKey_), pInsideSpr));
}

void GateDrawer::InitializeTimers()
{
	// アニメーションの数だけタイマー作成
	InsertAnimationTimer(kIdleIndex, AnimationTimer(Timer(120), true));
	InsertAnimationTimer(kExtendIndex, AnimationTimer(Timer(30), false));
	InsertAnimationTimer(kShrinkIndex, AnimationTimer(Timer(30), false));
}

void GateDrawer::GetReadyForAnimation(const uint32_t index)
{
	if (index & static_cast<uint32_t>(AnimationType::eIdle))
	{
	}
	else if (index & static_cast<uint32_t>(AnimationType::eExtend))
	{
	}
	else if (index & static_cast<uint32_t>(AnimationType::eShrink))
	{
	}
}

void GateDrawer::UpdateAnimation()
{
	float ratioE = animationTimers_[kExtendIndex].timer.Ratio();
	float ratioS = animationTimers_[kShrinkIndex].timer.Ratio();
	
	float rota = extendRotaEas_.Out(ratioE) + shrinkRotaEas_.In(ratioS);
	float scale = extendScaleEas_.Out(ratioE) + shrinkScaleEas_.In(ratioS);

	animeStatus_.scale_.x += scale;
	animeStatus_.scale_.y += scale;

	objs_["Gate_Frame"]->transform_.rota_.z = rota;
	objs_["Gate_Inside"]->transform_.rota_.z = rota;
}