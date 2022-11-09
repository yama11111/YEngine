#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "PipelineSet.h"
#include "RootParameterManager.h"
#include "Sprite.h"
#include "Model.h"
#include <memory>

class Game
{
public:
	// ----- ���\�[�X ----- //
	
	// ���n�摜
	UINT plainTex = 0;
	
	// model
	std::unique_ptr<Object::Model> m1 = nullptr;
	
	// sprite
	std::unique_ptr<Object::Sprite> s1 = nullptr;

	// ----- �I�u�W�F�N�g ----- //

	// Transform1
	Object::Transform t1;
	// Transform2
	Object::Transform t2;
	// Transform3
	Object::Transform t3;

	// �]���p�r���[�v���W�F�N�V����
	Object::ViewProjection vp;

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �R���X�g���N�^
	Game();
	// �f�X�g���N�^
	~Game();
private:
	// �L�[(�V���O���g��)
	static Input::Keys* keys_;
	// �}�E�X(�V���O���g��)
	static Input::Mouse* mouse_;
	// �p�b�h(�V���O���g��)
	static Input::Pad* pad_;
private:
	// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
	static DX::TextureManager* pTexManager_;
public:
	// �ÓI������
	static void StaticInitialize(DX::TextureManager* pTexManager);
};

