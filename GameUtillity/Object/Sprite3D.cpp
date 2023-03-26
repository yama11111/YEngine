#include "Sprite3D.h"
#include <cassert>

#pragma region ���O���

using YGame::Sprite3DObject;
using YGame::Sprite3DCommon;
using YGame::Sprite3D;
using YGame::TextureManager;
using YMath::Vector3;
using YMath::Matrix4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::TransformCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::TexDT); // tex

#pragma endregion


#pragma region Sprite3DCBSet

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard)
{
	// �C���X�^���X��Ԃ�
	return Create(status, isXAxisBillboard, isYAxisBillboard, nullptr, nullptr);
}

Sprite3DObject* Sprite3DObject::Create(const Status& status, bool isXAxisBillboard, bool isYAxisBillboard, 
	ViewProjection* pVP, Color* pColor)
{
	// �C���X�^���X���� (���I)
	Sprite3DObject* instance = new Sprite3DObject();

	// �萔�o�b�t�@����
	instance->cBuff_.Create();

	// ������(�f�t�H���g)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);

	// �C���X�^���X��Ԃ�
	return instance;
}

void Sprite3DObject::SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard)
{
	isXAxisBillboard_ = isXAxisBillboard;
	isYAxisBillboard_ = isYAxisBillboard;
}
void Sprite3DObject::SetViewProjection(ViewProjection* pVP)
{
	// null�Ȃ�
	if (pVP == nullptr)
	{
		// �f�t�H���g���
		pVP_ = sDefVP_.get();
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
		pColor_ = sDefColor_.get();
		return;
	}

	// ���
	pColor_ = pColor;
}

void Sprite3DObject::SetDrawCommand()
{
	// �V�F�[�_�[�ɒ萔�o�b�t�@(�s��)�𑗂�
	cBuff_.map_->matWorld_ = m_ * pVP_->view_ * pVP_->pro_;
	cBuff_.map_->matBill_ = BillboardMatrix();
	cBuff_.SetDrawCommand(TraIndex);

	// �V�F�[�_�[�ɒ萔�o�b�t�@(�F)�𑗂�
	pColor_->SetDrawCommand(ColIndex);
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

#pragma endregion


#pragma region Sprite3D

Sprite3D* Sprite3D::Create(const UINT texIndex)
{
	// �C���X�^���X���� (���I)
	Sprite3D* instance = new Sprite3D();
	
	// ������
	instance->vt_.Initialize({{}});
	
	// �e�N�X�`���ԍ�
	instance->tex_ = texIndex;

	// �`�悷��
	instance->isInvisible_  = false;
	
	
	// �C���X�^���X��Ԃ�
	return instance;
}

void Sprite3D::Draw(Sprite3DObject* pObj)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj->SetDrawCommand();

	// �e�N�X�`��
	spTexManager_->SetDrawCommand(TexIndex, tex_);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}

#pragma endregion