#include "Transform.h"
#include "CalcTransform.h"

using YGame::Transform;
using YMath::Matrix4;
using YMath::Vector3;

Transform::Transform() :
	pos_(0.0f, 0.0f, 0.0f),
	rota_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	m_(Matrix4::Identity()),
	parent_(nullptr)
{}

Transform::Status Transform::Status::Default()
{
	// �߂�l�p
	Status result;
	
	// ������
	result.pos_ = Vector3(0.0f, 0.0f, 0.0f);
	result.rota_ = Vector3(0.0f, 0.0f, 0.0f);
	result.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	// �Ԃ�
	return result;
}

void Transform::Initialize(const Status& status)
{
	// ���
	pos_ = status.pos_;
	rota_ = status.rota_;
	scale_ = status.scale_;
	
	// �s��X�V
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	// �A�t�B���ϊ�
	m_ = Matrix4::Identity();
	m_ *= MatScale(scale_) * MatRotation(rota_) * MatTranslation(pos_);
	if (parent_) { m_ *= *parent_; }
}

void Transform::UpdateMatrix(const Status& status)
{
	// �v�Z�p
	Vector3 p, r, s;
	
	// ���Z���đ��
	p = pos_ + status.pos_;
	r = rota_ + status.rota_;
	s = scale_ + status.scale_;

	// �A�t�B���ϊ�
	m_ = Matrix4::Identity();
	m_ *= MatScale(s) * MatRotation(r) * MatTranslation(p);
	if (parent_) { m_ *= *parent_; }
}
