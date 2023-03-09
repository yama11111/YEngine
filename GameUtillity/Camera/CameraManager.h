#pragma once
#include "Camera.h"
#include "Lerp.h"
#include "Timer.h"
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"

namespace YGame
{
	class CameraManager
	{
	private:
		// �J����
		Camera camera_;
		// �Ǐ]�_
		YMath::Vector3* pFollowPoint_ = nullptr;
	public:
		// ������
		void Initialize(YMath::Vector3* pFollowPoint);
		// �X�V
		void Update();
	public:
		// �J�����V�F�C�N
		void Shaking(const int swing, const int dekey);
		// �r���[�v���W�F�N�V�����擾
		YGame::ViewProjection GetViewProjection();
		// �Ǐ]�_�|�C���^�ݒ�
		void SetFollowPoint(YMath::Vector3* pFollowPoint);
	private:
		// �L�[(�V���O���g��)
		static YInput::Keys* keys_;
		// �}�E�X(�V���O���g��)
		static YInput::Mouse* mouse_;
		// �p�b�h(�V���O���g��)
		static YInput::Pad* pad_;
	public:
		static void StaticInitialize();
	};
}
