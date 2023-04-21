#include "ModelObject.h"

#pragma region ���O���

using YGame::ModelObject;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma endregion


#pragma region Model

ModelObject* ModelObject::Create(const Status& status, const bool isMutable)
{
	// �C���X�^���X��Ԃ�
	return Create(status, nullptr, nullptr, nullptr, nullptr, isMutable);
}

ModelObject* ModelObject::Create(
	const Status& status,
	ViewProjection* pVP,
	Color* pColor,
	LightGroup* pLightGroup,
	Material* pMaterial,
	const bool isMutable)
{
	// �C���X�^���X���� (���I)
	ModelObject* instance = new ModelObject();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������(�f�t�H���g)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);
	instance->SetLightGroup(pLightGroup);
	instance->SetMaterial(pMaterial);

	// �C���X�^���X��Ԃ�
	return instance;
}

void ModelObject::SetDrawCommand(
	const UINT transformRPIndex,
	const UINT colorRPIndex,
	const UINT lightRPIndex,
	const UINT materialRPIndex)
{
	// �s��
	cBuff_.map_->matWorld_ = m_;
	cBuff_.map_->matViewProj_ = pVP_->view_ * pVP_->pro_;
	cBuff_.map_->cameraPos_ = pVP_->eye_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// �F
	pColor_->SetDrawCommand(colorRPIndex);

	// ��
	pLightGroup_->SetDrawCommand(lightRPIndex);

	// �}�e���A��
	pMaterial_->SetDrawCommand(materialRPIndex);
}

void ModelObject::SetViewProjection(ViewProjection* pVP)
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
void ModelObject::SetColor(Color* pColor)
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
void ModelObject::SetLightGroup(LightGroup* pLightGroup)
{
	// null�Ȃ�
	if (pLightGroup == nullptr)
	{
		// �f�t�H���g���
		pLightGroup_ = Default::sLightGroup_.get();
		return;
	}

	// ���
	pLightGroup_ = pLightGroup;
}
void ModelObject::SetMaterial(Material* pMaterial)
{
	// null�Ȃ�
	if (pMaterial == nullptr)
	{
		// �f�t�H���g���
		pMaterial_ = Default::sMaterial_.get();
		return;
	}

	// ���
	pMaterial_ = pMaterial;
}

#pragma endregion


#pragma region Default

std::unique_ptr<YGame::ViewProjection> ModelObject::Default::sVP_ = nullptr;
std::unique_ptr<YGame::LightGroup> ModelObject::Default::sLightGroup_ = nullptr;
std::unique_ptr<YGame::Color> ModelObject::Default::sColor_ = nullptr;
std::unique_ptr<YGame::Material> ModelObject::Default::sMaterial_ = nullptr;

void ModelObject::Default::StaticInitialize()
{
	// ���� + ������ (�r���[�v���W�F�N�V�����|�C���^)
	sVP_.reset(new YGame::ViewProjection());
	sVP_->Initialize({});

	// ���� + ������ (�F)
	sColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));

	// ���� + ������ (�����|�C���^)
	sLightGroup_.reset(LightGroup::Create(false));

	// ���� + ������ (�}�e���A��)
	sMaterial_.reset(Material::Create({ 1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f }, 1.0f, false));
}

#pragma endregion


