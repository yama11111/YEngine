#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"
#include "Sprite.h"
#include "Model.h"
#include <memory>

namespace Game
{
	class GameScene
	{
	public:
		// ----- ���\�[�X ----- //

		// ���n�摜
		UINT plainTex = 0;

		// model
		std::unique_ptr<Model> m1 = nullptr;

		// sprite
		std::unique_ptr<Sprite> s1 = nullptr;

		// ----- �I�u�W�F�N�g ----- //

		// Transform1
		Transform t1;
		// Transform2
		Transform t2;
		// Transform3
		Transform t3;

		// �]���p�r���[�v���W�F�N�V����
		ViewProjection vp;
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
		static TextureManager* pTexManager_;
	public:
		// �ÓI������
		static void StaticInitialize(TextureManager* pTexManager);
	};
}
