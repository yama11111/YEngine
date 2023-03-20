#include "Sprite3D.h"

#pragma region ���O���

using YGame::Sprite3DCommon;
using YGame::Sprite3D;
using YGame::ObjectSprite3D;
using YGame::TextureManager;
using YMath::Vector3;
using YMath::Matrix4;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT ObjIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::ObjCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite3DCommon::RootParameterIndex::TexDT); // tex

#pragma endregion

ObjectSprite3D* ObjectSprite3D::Create(const Status& state)
{
	// �C���X�^���X���� (���I)
	ObjectSprite3D* instance = new ObjectSprite3D();

	// �萔�o�b�t�@����
	instance->cBuff_.Create();
	// ������
	instance->Initialize(state);

	// �C���X�^���X��Ԃ�
	return instance;
}

void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor, const UINT tex)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// �V�F�[�_�[�ɒ萔�o�b�t�@(�s��)�𑗂�
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * vp.view_ * vp.pro_;
	pObj->cBuff_.map_->matBill_ = BillboardMatrix(vp);
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// �V�F�[�_�[�ɒ萔�o�b�t�@(�F)�𑗂�
	pColor->SetDrawCommand(ColIndex);

	// �V�F�[�_�[�Ƀe�N�X�`���𑗂�
	pTexManager_->SetDrawCommand(TexIndex, tex);
	
	// �V�F�[�_�[�ɒ��_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}
void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp, const UINT tex)
{
	// �f�t�H���g�̐F��n���ĕ`��
	Draw(pObj, vp, defColor_.get(), tex);
}
void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp, Color* pColor)
{
	// �`�悵�Ȃ��Ȃ�e��
	if (isInvisible_) { return; }

	// �V�F�[�_�[�ɒ萔�o�b�t�@(�s��)�𑗂�
	pObj->cBuff_.map_->matWorld_ = pObj->m_ * vp.view_ * vp.pro_;
	pObj->cBuff_.map_->matBill_ = BillboardMatrix(vp);
	pObj->cBuff_.SetDrawCommand(ObjIndex);

	// �V�F�[�_�[�ɒ萔�o�b�t�@(�F)�𑗂�
	pColor->SetDrawCommand(ColIndex);

	// �V�F�[�_�[�Ƀe�N�X�`���𑗂�
	pTexManager_->SetDrawCommand(TexIndex, tex_);
	
	// �V�F�[�_�[�ɒ��_�o�b�t�@�𑗂� + �`��R�}���h
	vt_.Draw();
}
void Sprite3D::Draw(ObjectSprite3D* pObj, const ViewProjection& vp)
{
	// �f�t�H���g�̐F��n���ĕ`��
	Draw(pObj, vp, defColor_.get());
}
YMath::Matrix4 Sprite3D::BillboardMatrix(const ViewProjection& vp)
{
	// �ǂ���� false �Ȃ�
	if (isXAxisBillboard_ == false && isYAxisBillboard_ == false) 
	{
		// �P�ʍs���Ԃ�
		return Matrix4::Identity();
	}

	// �r���{�[�h�s��̌v�Z
	Vector3 axisZ = (vp.target_ - vp.eye_).Normalized();
	Vector3 axisX = (vp.up_.Cross(axisZ)).Normalized();
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

Sprite3D* Sprite3D::Create(const Status& state, const UINT texIndex)
{
	// �C���X�^���X���� (���I)
	Sprite3D* instance = new Sprite3D();
	
	// ������
	instance->vt_.Initialize({{}});
	
	//  �F (���̂܂�)
	instance->defColor_.reset(Color::Create());
	
	// �r���{�[�h��
	instance->isXAxisBillboard_ = state.isXAxisBillboard_; // X��
	instance->isYAxisBillboard_ = state.isYAxisBillboard_; // Y��
	
	// �e�N�X�`���ԍ�
	instance->tex_ = texIndex;

	// �`�悷��
	instance->isInvisible_  = false;
	
	
	// �C���X�^���X��Ԃ�
	return instance;
}
