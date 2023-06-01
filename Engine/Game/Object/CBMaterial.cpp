#include "CBMaterial.h"
#include "MathUtillity.h"

#pragma region ���O���

using YGame::CBMaterial;
using YMath::Vector3;
using YMath::Clamp;

#pragma endregion

CBMaterial* CBMaterial::Create(
	const Vector3& ambient,
	const Vector3& diffuse,
	const Vector3& specular,
	const float alpha, 
	const bool isMutable)
{
	// �C���X�^���X���� (���I)
	CBMaterial* instance = new CBMaterial();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������
	instance->Initialize(ambient, diffuse, specular, alpha);

	// �C���X�^���X��Ԃ�
	return instance;
}

void CBMaterial::Initialize(
	const Vector3& ambient,
	const Vector3& diffuse,
	const Vector3& specular,
	const float alpha)
{
	SetAmbient(ambient);
	SetDiffuse(diffuse);
	SetSpecular(specular);
	SetAlpha(alpha);
}

void CBMaterial::SetDrawCommand(const UINT rootParamIndex)
{
	// �萔�o�b�t�@�ɐݒ�
	cBuff_.map_->ambient_ = ambient_;
	cBuff_.map_->diffuse_ = diffuse_;
	cBuff_.map_->specular_ = specular_;
	cBuff_.map_->alpha_ = alpha_;

	// �V�F�[�_�[�ɑ���
	cBuff_.SetDrawCommand(rootParamIndex);
}

void CBMaterial::SetAmbient(const Vector3& ambient)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float x = Clamp<float>(ambient.x_, 0.0f, 1.0f);
	float y = Clamp<float>(ambient.y_, 0.0f, 1.0f);
	float z = Clamp<float>(ambient.z_, 0.0f, 1.0f);

	// ���
	ambient_ = Vector3(x, y, z);
}

void CBMaterial::SetDiffuse(const Vector3& diffuse)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float x = Clamp<float>(diffuse.x_, 0.0f, 1.0f);
	float y = Clamp<float>(diffuse.y_, 0.0f, 1.0f);
	float z = Clamp<float>(diffuse.z_, 0.0f, 1.0f);

	// ���
	diffuse_ = Vector3(x, y, z);
}

void CBMaterial::SetSpecular(const Vector3& specular)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float x = Clamp<float>(specular.x_, 0.0f, 1.0f);
	float y = Clamp<float>(specular.y_, 0.0f, 1.0f);
	float z = Clamp<float>(specular.z_, 0.0f, 1.0f);

	// ���
	specular_ = Vector3(x, y, z);
}

void CBMaterial::SetAlpha(const float alpha)
{
	// 0.0f ~ 1.0f �̊ԂɂȂ�悤��
	float alp = Clamp<float>(alpha, 0.0f, 1.0f);

	// ���
	alpha_ = alp;
}
