#include "Sprite3DObject.h"
#include <cassert>
#include <memory>

#pragma region ���O���

using YGame::Sprite3DObject;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma endregion


#pragma region Sprite3D

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard, const bool isMutable)
{
	// �C���X�^���X��Ԃ�
	return Create(status, isXAxisBillboard, isYAxisBillboard, nullptr, nullptr, isMutable);
}

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard,
	ViewProjection* pVP, Color* pColor, const bool isMutable)
{
	// �C���X�^���X���� (���I)
	Sprite3DObject* instance = new Sprite3DObject();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������(�f�t�H���g)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);

	// �C���X�^���X��Ԃ�
	return instance;
}

Matrix4 Sprite3DObject::BillboardMatrix()
{
	// �ǂ���� false �Ȃ�
	if (isXAxisBillboard_ == false && isYAxisBillboard_ == false)
	{
		// �P�ʍs���Ԃ�
		return Matrix4::Identity();
	}

	// �r���{�[�h�s��̌v�Z
	Vector3 axisZ = (pVP_->target_ - pVP_->eye_).Normalized();
	Vector3 axisX = (pVP_->up_.Cross(axisZ)).Normalized();
	Vector3 axisY = axisZ.Cross(axisX);

	// Y������r���{�[�h�Ȃ�
	if (isYAxisBillboard_)
	{
		axisY = { 0,1,0 };
		axisZ = axisX.Cross(axisY);
	}

	// �r���{�[�h�s��
	Matrix4 matBillboard(
		axisX.x_, axisX.y_, axisX.z_, 0.0f,
		axisY.x_, axisY.y_, axisY.z_, 0.0f,
		axisZ.x_, axisZ.y_, axisZ.z_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// �r���{�[�h�s���Ԃ�
	return matBillboard;
}

void Sprite3DObject::SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex)
{
	// �V�F�[�_�[�ɒ萔�o�b�t�@(�s��)�𑗂�
	cBuff_.map_->matWorld_ = m_ * pVP_->view_ * pVP_->pro_;
	cBuff_.map_->matBill_ = BillboardMatrix();
	cBuff_.SetDrawCommand(transformRPIndex);

	// �V�F�[�_�[�ɒ萔�o�b�t�@(�F)�𑗂�
	pColor_->SetDrawCommand(colorRPIndex);
}

void Sprite3DObject::SetViewProjection(ViewProjection* pVP)
{
	// null�Ȃ�
	if (pVP == nullptr)
	{
		// �f�t�H���g���
		pVP_ = Default::sVP_.get();
		return;
	}

	// ���
	pVP_ = pVP;
}
void Sprite3DObject::SetColor(Color* pColor)
{
	// null�Ȃ�
	if (pColor == nullptr)
	{
		// �f�t�H���g���
		pColor_ = Default::sColor_.get();
		return;
	}

	// ���
	pColor_ = pColor;
}
void Sprite3DObject::SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard)
{
	isXAxisBillboard_ = isXAxisBillboard;
	isYAxisBillboard_ = isYAxisBillboard;
}

#pragma endregion


#pragma region Default

std::unique_ptr<YGame::ViewProjection> Sprite3DObject::Default::sVP_ = nullptr;
std::unique_ptr<YGame::Color> Sprite3DObject::Default::sColor_ = nullptr;

void Sprite3DObject::Default::StaticInitialize()
{
	// ����
	sVP_.reset(new YGame::ViewProjection());
	sVP_->Initialize({});

	// ���� + ������
	sColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
}

#pragma endregion
