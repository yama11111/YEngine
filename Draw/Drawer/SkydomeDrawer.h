#pragma once
#include "Model.h"

class SkydomeDrawerCommon
{
protected:
	// �ÓI���f��
	static YGame::Model* spModel_;
public:
	// �ÓI������
	static void StaticInitialize();
public:
	virtual ~SkydomeDrawerCommon() = default;
};

class SkydomeDrawer :
	public SkydomeDrawerCommon
{
private:
	// �I�u�W�F�N�g
	std::unique_ptr<YGame::ModelObject> obj_;
	// �F
	std::unique_ptr<YGame::Color> color_;

public:
	// ������
	void Initalize(YMath::Matrix4* pParent);
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`��
	void Draw();
};

