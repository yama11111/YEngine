#include "BaseParticle.h"
//#include <cassert>
//
//using YGame::BaseParticle;
//
//using YGame::BaseParticleForModel;
//using YGame::BaseParticleForSprite2D;
//using YGame::BaseParticleForSprite3D;
//
//using YGame::Model;
//using YGame::Sprite2D;
//using YGame::Sprite3D;
//
//using YGame::ViewProjection;
//
//using YMath::Ease;
//using YMath::Timer;
//using YMath::Power;
//
//using YMath::Vector3;
//using YMath::Vector4;
//using YMath::Matrix4;
//
//ViewProjection* BaseParticleForModel::spVP_ = nullptr;
//ViewProjection* BaseParticleForSprite3D::spVP_ = nullptr;
//
//#pragma region BaseParticle
//
//BaseParticle::BaseParticle(const uint32_t aliveFrame, const DrawLocation location) :
//	aliveTimer_(aliveFrame, true), 
//	location_(location)
//{
//}
//
//void BaseParticle::Initialize(const uint32_t aliveFrame, const DrawLocation location)
//{
//	isAlive_ = true;
//
//	// �����^�C�}�[������ + �J�n
//	aliveTimer_.Initialize(aliveFrame, true);
//
//	location_ = location;
//}
//
//void BaseParticle::UpdateLife()
//{
//	if (isAlive_ == false) { return; }
//
//	aliveTimer_.Update();
//	
//	// �����^�C�}�[�I����
//	if (aliveTimer_.IsEnd()) 
//	{
//		// ���S
//		isAlive_ = false; 
//	}
//}
//
//#pragma endregion
//
//
//#pragma region BaseParticleForModel
//
//void BaseParticleForModel::StaticInitialize(ViewProjection* pVP)
//{
//	assert(pVP);
//
//	spVP_ = pVP;
//}
//
//BaseParticleForModel::BaseParticleForModel(
//	const uint32_t aliveFrame, 
//	const Transform::Status& status, 
//	Model* pModel, const DrawLocation location) : 
//	BaseParticle(aliveFrame, location), 
//	obj_(status), 
//	pModel_(pModel)
//{
//}
//
//void BaseParticleForModel::Initialize(
//	const uint32_t aliveFrame, 
//	const Transform::Status& status, 
//	Model* pModel, const DrawLocation location)
//{
//}
//
//void BaseParticleModel::Initialize(
//	const uint32_t aliveFrame, 
//	const Transform::Status& status, 
//	Model* pModel, const DrawLocation location)
//{
//
//}
//
//void IParticleModel::CreateObject()
//{
//	// ����
//	color_.reset(CBColor::Create());
//	obj_.reset(Model::Object::Create(Transform::Status::Default(), spVP_, color_.get()));
//}
//
//#pragma endregion
//
//
//#pragma region IParticleSprite3D
//
//void IParticleSprite3D::StaticInitialize(YGame::ViewProjection* pVP)
//{
//	// null�`�F�b�N
//	assert(pVP);
//	// ���
//	spVP_ = pVP;
//}
//
//void IParticleSprite3D::CreateObject(const bool isXAxisBillboard, const bool isYAxisBillboard)
//{
//	// ����
//	color_.reset(CBColor::Create());
//	obj_.reset(Sprite3D::Object::Create(Transform::Status::Default(), isXAxisBillboard, isYAxisBillboard, spVP_, color_.get()));
//}
//
//#pragma endregion
//
//
//void YGame::BaseParticleForSprite2D::Initialize(const uint32_t aliveFrame, const Transform::Status& status, Sprite2D* pSprite2D, const DrawLocation location)
//{
//}
