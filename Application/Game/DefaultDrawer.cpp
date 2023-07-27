#include "DefaultDrawer.h"

using YGame::DefaultDrawer;
using YGame::Model;

Model* DefaultDrawer::spModel_ = nullptr;

void DefaultDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, drawPriority);

	// モデル挿入
	obj_->SetModel(spModel_);

	shaderKey_ = "ModelToon";
}

void DefaultDrawer::Update()
{
	BaseDrawer::Update();
	
	VisibleUpdate();
}

void DefaultDrawer::Draw()
{
	BaseDrawer::Draw();
}

void DefaultDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

DefaultDrawer::DefaultDrawer(const uint16_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

DefaultDrawer::DefaultDrawer(Transform* pParent, const uint16_t drawPriority)
{
	Initialize(pParent, drawPriority);
}


void DefaultDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}