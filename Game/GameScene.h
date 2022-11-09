#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "PipelineSet.h"
#include "RootParameterManager.h"
#include "Sprite.h"
#include "Model.h"
#include <memory>

class GameScene
{
public:
	// ----- ���\�[�X ----- //
	
	// ���n�摜
	UINT plainTex = 0;
	
	// model
	std::unique_ptr<Game::Model> m1 = nullptr;
	
	// sprite
	std::unique_ptr<Game::Sprite> s1 = nullptr;

	// ----- �I�u�W�F�N�g ----- //

	// Transform1
	Game::Transform t1;
	// Transform2
	Game::Transform t2;
	// Transform3
	Game::Transform t3;

	// �]���p�r���[�v���W�F�N�V����
	Game::ViewProjection vp;

public:
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �R���X�g���N�^
	GameScene();
	// �f�X�g���N�^
	~GameScene();
private:
	// �L�[(�V���O���g��)
	static Input::Keys* keys_;
	// �}�E�X(�V���O���g��)
	static Input::Mouse* mouse_;
	// �p�b�h(�V���O���g��)
	static Input::Pad* pad_;
private:
	// �ÓI�e�N�X�`���}�l�[�W���[�|�C���^
	static Game::TextureManager* pTexManager_;
public:
	// �ÓI������
	static void StaticInitialize(Game::TextureManager* pTexManager);
};

