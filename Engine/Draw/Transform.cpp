#include "Transform.h"
#include "MathVector.h"

using YGame::Transform;
using YMath::Matrix4;
using YMath::Vector3;

Transform::Transform() :
	pos_(0.0f, 0.0f, 0.0f),
	rota_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	m_(Matrix4::Identity()),
	parent_(nullptr)
{
	// 行列更新
	UpdateMatrix();
}

Transform::Transform(const Status & status) :
	pos_(status.pos_),
	rota_(status.rota_),
	scale_(status.scale_),
	m_(Matrix4::Identity()),
	parent_(nullptr)
{
	// 行列更新
	UpdateMatrix();
}

Transform::Status Transform::Status::Default()
{
	// 戻り値用
	Status result;
	
	// 初期化
	result.pos_ = Vector3(0.0f, 0.0f, 0.0f);
	result.rota_ = Vector3(0.0f, 0.0f, 0.0f);
	result.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	// 返す
	return result;
}

void Transform::Initialize(const Status& status)
{
	// 代入
	pos_ = status.pos_;
	rota_ = status.rota_;
	scale_ = status.scale_;
	
	// 行列更新
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(scale_) * MatRotation(rota_) * MatTranslation(pos_);
	if (parent_) { m_ *= *parent_; }
}

void Transform::UpdateMatrix(const Status& status)
{
	// 計算用
	Vector3 p, r, s;
	
	// 加算して代入
	p = pos_ + status.pos_;
	r = rota_ + status.rota_;
	s = scale_ + status.scale_;

	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(s) * MatRotation(r) * MatTranslation(p);
	if (parent_) { m_ *= *parent_; }
}
