#pragma once
#include "SkydomeDrawer.h"

class Skydome
{
private:
	// �g�����X�t�H�[��
	YGame::Transform transform_;
	// �`��p�N���X
	SkydomeDrawer drawer_;
public:
	// ������
	void Initialize();
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
};
