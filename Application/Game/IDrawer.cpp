#include "IDrawer.h"
#include <cassert>

using YGame::IDrawer;

YGame::ViewProjection* IDrawer::spVP_ = nullptr;

void IDrawer::Initialize(Transform* pParent)
{
	// オブジェクト生成
	obj_.reset(Model::Object::Create());

	// 親子関係設定
	obj_->parent_ = &pParent->m_;

	// ビュープロジェクション設定
	obj_->SetViewProjection(spVP_);
}

void IDrawer::StaticInitialize(ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);

	// 代入
	spVP_ = pVP;
}
