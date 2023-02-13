#include "Object.h"
#include "CalcTransform.h"
#include "Sprite2DCommon.h"
#include "Sprite3DCommon.h"
#include "ModelCommon.h"

using YGame::Object;
using YDX::ConstBuffer;
using YMath::Matrix4;
using YMath::Vector4;

template<typename T>
Object<T>::Object() :
	pos_(0.0f, 0.0f, 0.0f), 
	rota_(0.0f, 0.0f, 0.0f), 
	scale_(1.0f, 1.0f, 1.0f), 
	m_(Matrix4::Identity()),
	parent_(nullptr)
{}

template<typename T>
Object<T>* Object<T>::Create(const Status& state)
{
	Object<T>* instance = new Object<T>();
	instance->cBuff_.Create();
	instance->Initialize(state);

	return instance;
}

template<typename T>
void Object<T>::Initialize(const Status& state)
{
	pos_ = state.pos_;
	rota_ = state.rota_;
	scale_ = state.scale_;
	UpdateMatrix();
}

template<typename T>
void Object<T>::UpdateMatrix()
{
	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(scale_) * MatRotation(rota_) * MatTranslation(pos_);
	if (parent_) { m_ *= *parent_; }
}

template<typename T>
void Object<T>::UpdateMatrix(const Status& state)
{
	Status s = { pos_,rota_,scale_ };
	s.pos_ += state.pos_;
	s.rota_ += state.rota_;
	s.scale_ += state.scale_;

	// アフィン変換
	m_ = Matrix4::Identity();
	m_ *= MatScale(s.scale_) * MatRotation(s.rota_) * MatTranslation(s.pos_);
	if (parent_) { m_ *= *parent_; }
}

template class Object<YGame::Sprite2DCommon::CBData>;
template class Object<YGame::Sprite3DCommon::CBData>;
template class Object<YGame::ModelCommon::CBData>;