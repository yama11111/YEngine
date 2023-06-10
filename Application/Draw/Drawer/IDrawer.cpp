#include "IDrawer.h"
#include <cassert>

using YGame::IDrawer;

void IDrawer::Initialize(Transform* pParent)
{
	// オブジェクト生成
	obj_.reset(Model::Object::Create());

	// 親子関係設定
	obj_->parent_ = &pParent->m_;
}