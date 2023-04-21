#include "SkydomeDrawer.h"

using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

Model* SkydomeDrawerCommon::spModel_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize()
{
	// ���f���ǂݍ���
	spModel_ = Model::Load("skydome", true);
}

void SkydomeDrawer::Initalize(YMath::Matrix4* pParent)
{
	// �F����
	color_.reset(Color::Create());

	// �I�u�W�F�N�g����
	obj_.reset(ModelObject::Create({}, nullptr, color_.get(), nullptr, nullptr));
	
	// �e�s����
	obj_->parent_ = pParent;

	// ���Z�b�g
	Reset();
}

void SkydomeDrawer::Reset()
{
	// �I�u�W�F�N�g������
	obj_->Initialize(
		{
			{},
			{},
			{ 200.0f, 200.0f, 200.0f }
		}
	);
}

void SkydomeDrawer::Update()
{
	// �I�u�W�F�N�g�X�V
	obj_->UpdateMatrix();
}

void SkydomeDrawer::Draw()
{
	// �`��
	spModel_->Draw(obj_.get());
}
