#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::FireWork;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;

ViewProjection* IParticle::spVP_ = nullptr;
Model* FireWork::spModel_ = nullptr;

void IParticle::StaticInitialize(YGame::ViewProjection* pVP)
{
	// null�`�F�b�N
	assert(pVP);
	// ���
	spVP_ = pVP;
}

void FireWork::StaticInitialize(YGame::Model* pModel)
{
	// null�`�F�b�N
	assert(pModel);
	// ������
	spModel_ = pModel;
}

void FireWork::Emit(
	const uint32_t aliveTime,
	const YMath::Ease<YMath::Vector3>& pos,
	const YMath::Ease<YMath::Vector3>& rota,
	const float scale,
	const YMath::Vector4& color)
{
	// �����t���O
	isAlive_ = true;

	// �����^�C�}�[������ + �J�n
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);
	
	// ����
	color_.reset(Color::Create(color));
	obj_.reset(ModelObject::Create({ pos.SetStart(), {}, {scale,scale,scale} }, spVP_, color_.get(), nullptr));

	// ���
	posEas_ = pos;
	rotaEas_ = rota;
	scaleEas_.Initialize(scale, scale / 2.0f, 3.0f);
	alphaEas_.Initialize(color.a_, 0.0f, 3.0f);

}

void FireWork::Update()
{
	// ����ł���Ȃ�e��
	if (isAlive_ == false) { return; }

	// �����^�C�}�[�X�V
	aliveTim_.Update();
	// �����^�C�}�[�I�� �� ���S
	if (aliveTim_.IsEnd()) { isAlive_ = false; }

	// �ʒu
	obj_->pos_ = posEas_.In(aliveTim_.Ratio());
	// ��]
	obj_->rota_ = rotaEas_.In(aliveTim_.Ratio());
	// �傫��
	float scale = scaleEas_.In(aliveTim_.Ratio());
	obj_->scale_ = { scale, scale, scale };

	// Object�X�V
	obj_->UpdateMatrix();

	// �A���t�@�l
	color_->SetAlpha(alphaEas_.In(aliveTim_.Ratio()));
}

void FireWork::Draw()
{
	// �`��
	spModel_->Draw(obj_.get());
}
