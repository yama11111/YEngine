#include "SnortAttackDrawer.h"
#include "DrawObjectForModel.h"
#include "Def.h"

using YGame::SnortAttackDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

namespace
{
	// モデルポインタ
	Model* pModel = nullptr;
}

SnortAttackDrawer* SnortAttackDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	SnortAttackDrawer* newDrawer = new SnortAttackDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SnortAttackDrawer::LoadResource()
{
	pModel = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void SnortAttackDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	SetShaderTag("ModelPhong");
	
	slimeActor_.Initialize(0, { {} }, 0);

	rotaEas_.Initialize(0.0f, kPI * 4.0f, 3.0f);

	cbColor_->data_.baseColor = { 0.95f,0.95f,0.95f,0.5f };
}

void SnortAttackDrawer::InitializeObjects()
{
	InsertObject("Attack", DrawObjectForModel::Create({}, spVP_, pModel));
}

void SnortAttackDrawer::InitializeTimers()
{
	InsertAnimationTimer(static_cast<uint32_t>(AnimationType::eAttack), AnimationTimer());
}

void SnortAttackDrawer::GetReadyForAnimation(const uint32_t index, const uint32_t frame)
{
	if (index & static_cast<uint32_t>(AnimationType::eAttack))
	{
		// ブヨブヨアニメ
		std::vector<Vector3> wobbleScaleValues;
		wobbleScaleValues.push_back(Vector3(-1.0f, -1.0f, -1.0f));
		wobbleScaleValues.push_back(Vector3(+0.4f, +0.4f, +0.4f));
		wobbleScaleValues.push_back(Vector3(+0.0f, +0.0f, +0.0f));

		uint32_t wobbleFrame = frame;

		slimeActor_.Initialize(wobbleFrame, wobbleScaleValues, 3.0f);
		slimeActor_.Wobble();
	}
}

void SnortAttackDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);
	
	animeStatus_.rota_.z_ += rotaEas_.InOut(animationTimers_[static_cast<uint16_t>(AnimationType::eAttack)].timer.Ratio());
}