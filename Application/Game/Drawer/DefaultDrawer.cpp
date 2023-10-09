#include "DefaultDrawer.h"

using YGame::DefaultDrawer;
using YGame::Model;

Model* DefaultDrawer::spModel_ = nullptr;

DefaultDrawer* DefaultDrawer::Create(Transform* pParent, const size_t drawPriority)
{
	DefaultDrawer* newDrawer = new DefaultDrawer();

	newDrawer->Initialize(pParent, drawPriority);

	return newDrawer;
}

void DefaultDrawer::LoadResource()
{
	// モデル設定
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}

void DefaultDrawer::Initialize(Transform* pParent, const size_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル挿入
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";
}

void DefaultDrawer::InsertAnimationTimers()
{
}

void DefaultDrawer::UpdateAnimation()
{
}