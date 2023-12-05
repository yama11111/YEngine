#include "GateDrawer.h"
#include "DrawObjectForModel.h"
#include "ColorConfig.h"

using YGame::GateDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Timer;

namespace
{
	Model* pModel = nullptr;

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
	pModel = Model::CreateCube({ {"Texture0", Texture::Load("white1x1.png", false)} });
}

void GateDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	transform_.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	cbColor_->data_.baseColor = ColorConfig::skYellow;
	cbColor_->data_.baseColor.a_ = 0.4f;
	cbMaterial_->data_.ambient = Vector3(0.8f, 0.8f, 0.8f);
	SetShaderTag("Gate", "ModelToon");
}

void GateDrawer::InitializeObjects()
{
	InsertObject("Gate", DrawObjectForModel::Create({}, spVP_, pModel));
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
}