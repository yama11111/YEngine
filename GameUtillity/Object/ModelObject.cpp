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
	return Create(status, nullptr, nullptr, nullptr, isMutable);
}

ModelObject* ModelObject::Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup, const bool isMutable)
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

	// �C���X�^���X��Ԃ�
	return instance;
}

void ModelObject::SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex, const UINT lightRPIndex)
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
}

void ModelObject::SetViewProjection(ViewProjection* pVP)
{
	// null�Ȃ�
	if (pVP == nullptr)
	{
		// �f�t�H���g���
		pVP_ = common_.sDefVP_.get();
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
		pColor_ = common_.sDefColor_.get();
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
		pLightGroup_ = common_.sDefLightGroup_.get();
		return;
	}

	// ���
	pLightGroup_ = pLightGroup;
}

#pragma endregion

#pragma region Common

std::unique_ptr<YGame::ViewProjection> ModelObject::Common::sDefVP_ = nullptr;
std::unique_ptr<YGame::LightGroup> ModelObject::Common::sDefLightGroup_ = nullptr;
std::unique_ptr<YGame::Color> ModelObject::Common::sDefColor_ = nullptr;

void ModelObject::Common::StaticInitialize()
{
	// ����
	sDefVP_.reset(new YGame::ViewProjection());
	sDefVP_->Initialize({});

	sDefLightGroup_.reset(LightGroup::Create(false));

	sDefColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
}

#pragma endregion


