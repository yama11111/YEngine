#pragma once
#include "Camera.h"
#include "Lerp.h"
#include "Timer.h"

class CameraManager
{
private:
	// �J����
	Camera camera_;
	// �Ǐ]�t���O
	bool isFollow_ = false;
	// �Ǐ]�_�|�C���^
	YMath::Vec3* pFollowPoint_ = nullptr;
public:
	// ������
	void Initialize();
	// �X�V
	void Update();
private:
	// �Ǐ]�X�V
	void UpdateFollow();
public:
	// �J�����V�F�C�N
	void Shaking(const int swing, const int dekey);
	// �r���[�v���W�F�N�V�����擾
	YGame::ViewProjection GetViewProjection();
	// �Ǐ]�_�|�C���^�ݒ�
	void SetFollowPoint(YMath::Vec3* pFollowPoint);
};

