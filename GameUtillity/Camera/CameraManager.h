#pragma once
#include "Camera.h"
#include "Lerp.h"
#include "Timer.h"
#include "Keys.h"
#include "Mouse.h"
#include "Pad.h"

namespace YGame
{
	// �J�����}�l�[�W���[�R�����N���X
	class CameraManagerCommon
	{
	private:
		// �L�[(�V���O���g��)
		static YInput::Keys* keys_;
		// �}�E�X(�V���O���g��)
		static YInput::Mouse* mouse_;
		// �p�b�h(�V���O���g��)
		static YInput::Pad* pad_;
	public:
		// �ÓI������
		static void StaticInitialize();
	};

	// �J�����}�l�[�W���[
	class CameraManager : private CameraManagerCommon
	{
	private:
		// �J����
		Camera camera_;
		// �Ǐ]�_
		YMath::Vector3* pFollowPoint_ = nullptr;
	public:
		// �������p�X�e�[�^�X
		struct InitStatus
		{
			// �g�����X�t�H�[���ݒ�X�e�[�^�X
			Transform::Status traState_;
			// �Ǐ]�_�|�C���^
			YMath::Vector3* pFollowPoint_ = nullptr;
			// �Ǐ]���邩
			bool isFollow_ = false;
		};
	public:
		// ������
		void Initialize(const std::vector<InitStatus>& statuses);
		// �X�V
		void Update();
	public:
		// �J�����V�F�C�N
		void Shaking(const int swing, const int dekey);
		// �r���[�v���W�F�N�V�����擾
		ViewProjection GetViewProjection();
		// �Ǐ]�_�|�C���^�ݒ�
		void SetFollowPoint(YMath::Vector3* pFollowPoint);
	};
}
