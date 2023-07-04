#include "SkydomeDrawer.h"

using YGame::SkydomeDrawer;
using YGame::Model;

using YMath::Vector3;

Model* SkydomeDrawer::spModel_ = nullptr;

void SkydomeDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト初期化
	BaseDrawer::Initialize(pParent, location);

	isVisibleUpdate_ = false;

	material_->SetAmbient(Vector3(0.8f, 0.8f, 0.8f));

	// モデル挿入
	pModel_ = spModel_;

	shader_ = Model::ShaderType::eDefault;
}

void SkydomeDrawer::Update()
{
	obj_->UpdateMatrix();
}

void SkydomeDrawer::Draw()
{
	BaseDrawer::Draw();
}

void SkydomeDrawer::PlayAnimation(const uint16_t index, const uint32_t frame)
{

}

SkydomeDrawer::SkydomeDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

SkydomeDrawer::SkydomeDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}


void SkydomeDrawer::StaticInitialize()
{
	// モデル設定
	spModel_ = Model::LoadObj("skydome", true);
}