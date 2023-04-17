#include "Skydome.h"
#include <cassert>

void Skydome::Initialize()
{
	// ������
	transform_.Initialize({});
	drawer_.Initalize(&transform_.m_);

	// ���Z�b�g
	Reset();
}

void Skydome::Reset()
{
	transform_.Initialize({});
	drawer_.Reset();
}

void Skydome::Update()
{
	// �X�V
	transform_.UpdateMatrix();

	drawer_.Update();
}

void Skydome::Draw()
{
	// �`��
	drawer_.Draw();
}