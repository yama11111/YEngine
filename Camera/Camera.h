#pragma once
#include "Object.h"
#include "ViewProjection.h"
#include "Shake.h"

class Camera
{
public:
	// �ʒu
	YMath::Vec3 pos_;
	// ��]
	YMath::Vec3 rota_;
private:
	// �I�u�W�F�N�g
	YGame::Object obj_;
	// �r���[�v���W�F�N�V����
	YGame::ViewProjection vp_;
	// �J�����V�F�C�N
	YMath::Shake shake_;
public:
	// ������
	void Initialize(YGame::Object::Status state);
	// ������(�J�����V�F�C�N�ȊO)
	void SetStatus(YGame::Object::Status state);
	// �J�����V�F�C�N
	void Shaking(const int swing, const int dekey);
	// trfm �� vp
	void Update();
public:
	// �r���[�v���W�F�N�V����
	YGame::ViewProjection GetViewProjection();
	// �J��������
	YMath::Vec3 Verocity();
	// �h��Ă��邩
	bool IsShake() { return shake_.IsShake(); }
};

