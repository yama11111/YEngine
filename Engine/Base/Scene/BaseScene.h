#pragma once
#include "InputManager.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "PostEffect.h"
#include "Audio.h"
#include "Camera.h"
#include <memory>

namespace YScene
{
	// ���V�[���N���X
	class BaseScene
	{
	
	public:
		
		/// <summary>
		/// �ǂݍ���
		/// </summary>
		virtual void Load() = 0;
		
		/// <summary>
		/// ������
		/// </summary>
		virtual void Initialize() = 0;
		
		/// <summary>
		/// �I������
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;
		
		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
	
	public:
		
		// �R���X�g���N�^
		BaseScene() = default;
		
		// �f�X�g���N�^
		virtual ~BaseScene() = default;
	
	protected:
		
		// �L�[(�V���O���g��)
		static YInput::Keys* sKeys_;
		
		// �}�E�X(�V���O���g��)
		static YInput::Mouse* sMouse_;
		
		// �p�b�h(�V���O���g��)
		static YInput::Pad* sPad_;
	
	public:
		
		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();
	
	};
}
