#include "IDrawer.h"
#include <cassert>

using YGame::IDrawer;

void IDrawer::Initialize(Transform* pParent)
{
	// �I�u�W�F�N�g����
	obj_.reset(Model::Object::Create());

	// �e�q�֌W�ݒ�
	obj_->parent_ = &pParent->m_;
}