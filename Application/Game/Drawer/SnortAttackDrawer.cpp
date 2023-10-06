#include "SnortAttackDrawer.h"
#include "Def.h"

using YGame::SnortAttackDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* SnortAttackDrawer::spModel_ = nullptr;

SnortAttackDrawer* SnortAttackDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	SnortAttackDrawer* newDrawer = new SnortAttackDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SnortAttackDrawer::LoadResource()
{
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void SnortAttackDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);

	slimeActor_.Initialize(0, { {} }, 0);

	rotaEas_.Initialize(0.0f, kPI * 4.0f, 3.0f);

	cbColor_->data_.baseColor = { 0.95f,0.95f,0.95f,0.5f };

	shaderKey_ = "ModelPhong";
}

void SnortAttackDrawer::InsertAnimationTimers()
{
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eAttack), AnimationTimer() });
}

void SnortAttackDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
{
	if (index & static_cast<uint16_t>(AnimationType::eAttack))
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