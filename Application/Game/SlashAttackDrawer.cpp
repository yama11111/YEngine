#include "SlashAttackDrawer.h"

#include "Def.h"

using YGame::SlashAttackDrawer;
using YGame::Model;
using YMath::Vector3;
using YMath::Vector4;

Model* SlashAttackDrawer::spModel_ = nullptr;

SlashAttackDrawer* SlashAttackDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	SlashAttackDrawer* newDrawer = new SlashAttackDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void SlashAttackDrawer::LoadResource()
{
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void SlashAttackDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル設定
	obj_->SetModel(spModel_);

	slimeActor_.Initialize(0, { {} }, 0);

	rotaEas_.Initialize(0.0f, PI * 4.0f, 3.0f);

	cbColor_->data_.baseColor = { 0.95f,0.95f,0.95f,0.5f };

	shaderKey_ = "ModelPhong";
}

void SlashAttackDrawer::InsertAnimationTimers()
{
	animationTimers_.insert({ static_cast<uint16_t>(AnimationType::eAttack), AnimationTimer() });
}

void SlashAttackDrawer::PlaySubAnimation(const uint16_t index, const uint32_t frame)
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

void SlashAttackDrawer::UpdateAnimation()
{
	slimeActor_.Update();

	animeStatus_.scale_ += slimeActor_.WobbleScaleValue(SlimeActor::EaseType::eOut);

	animeStatus_.rota_.x_ += rotaEas_.InOut(animationTimers_[static_cast<uint16_t>(AnimationType::eAttack)].timer.Ratio());
}