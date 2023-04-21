#include "Sprite2DObject.h"
#include "CalcTransform.h"
#include <cassert>
#include <memory>

#pragma region ���O���

using YGame::Sprite2DObject;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma endregion


#pragma region Sprite2DObject

Sprite2DObject* Sprite2DObject::Create(const Status& status, const bool isMutable)
{
	// �C���X�^���X��Ԃ�
	return Create(status, nullptr, isMutable);
}

Sprite2DObject* Sprite2DObject::Create(const Status& status, Color* pColor, const bool isMutable)
{
	// �C���X�^���X���� (���I)
	Sprite2DObject* instance = new Sprite2DObject();

	// �萔�o�b�t�@����
	instance->cBuff_.Create(isMutable);

	// ������(�f�t�H���g)
	instance->Initialize(status);
	instance->SetColor(pColor);

	// �C���X�^���X��Ԃ�
	return instance;
}

void Sprite2DObject::SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex)
{
	// �s��
	cBuff_.map_->matWorld_ = m_ * Default::sProjection_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// �F
	pColor_->SetDrawCommand(colorRPIndex);
}

void Sprite2DObject::SetColor(Color* pColor)
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

#pragma endregion


#pragma region Default

YMath::Matrix4 Sprite2DObject::Default::sProjection_ = YMath::Matrix4::Identity();
std::unique_ptr<YGame::Color> Sprite2DObject::Default::sColor_ = nullptr;

void Sprite2DObject::Default::StaticInitialize()
{
	// �v���W�F�N�V�����s���ݒ�
	sProjection_ = YMath::MatOrthoGraphic();

	// ���� + ������
	sColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
}

#pragma endregion



