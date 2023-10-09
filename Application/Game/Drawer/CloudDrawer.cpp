#include "CloudDrawer.h"

using YGame::CloudDrawer;
using YGame::Model;

Model* CloudDrawer::spModel_ = nullptr;

CloudDrawer* CloudDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	CloudDrawer* newDrawer = new CloudDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void CloudDrawer::LoadResource()
{
	// モデル設定
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void CloudDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	cbColor_->data_.baseColor.a_ = 0.4f;

	// モデル挿入
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";

	posXTim_.Initialize(60000, true);

	posXEas_.Initialize(0.0f, -100.0f, 1.0f);
}

void CloudDrawer::InsertAnimationTimers()
{
}

void CloudDrawer::UpdateAnimation()
{
	posXTim_.Update();
	if (posXTim_.IsEnd()) { posXTim_.Reset(true); }
	
	animeStatus_.pos_.x_ = posXEas_.InOut(posXTim_.Ratio());
}