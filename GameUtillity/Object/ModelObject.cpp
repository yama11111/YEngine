#include "ModelObject.h"

#pragma region 名前空間

using YGame::ModelObject;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma endregion

#pragma region Model

ModelObject* ModelObject::Create(const Status& status, const bool isMutable)
{
	// インスタンスを返す
	return Create(status, nullptr, nullptr, nullptr, isMutable);
}

ModelObject* ModelObject::Create(const Status& status, ViewProjection* pVP, Color* pColor, LightGroup* pLightGroup, const bool isMutable)
{
	// インスタンス生成 (動的)
	ModelObject* instance = new ModelObject();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetViewProjection(pVP);
	instance->SetColor(pColor);
	instance->SetLightGroup(pLightGroup);

	// インスタンスを返す
	return instance;
}

void ModelObject::SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex, const UINT lightRPIndex)
{
	// 行列
	cBuff_.map_->matWorld_ = m_;
	cBuff_.map_->matViewProj_ = pVP_->view_ * pVP_->pro_;
	cBuff_.map_->cameraPos_ = pVP_->eye_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// 色
	pColor_->SetDrawCommand(colorRPIndex);

	// 光
	pLightGroup_->SetDrawCommand(lightRPIndex);
}

void ModelObject::SetViewProjection(ViewProjection* pVP)
{
	// nullなら
	if (pVP == nullptr)
	{
		// デフォルト代入
		pVP_ = Default::sVP_.get();
		return;
	}

	// 代入
	pVP_ = pVP;
}
void ModelObject::SetColor(Color* pColor)
{
	// nullなら
	if (pColor == nullptr)
	{
		// デフォルト代入
		pColor_ = Default::sColor_.get();
		return;
	}

	// 代入
	pColor_ = pColor;
}
void ModelObject::SetLightGroup(LightGroup* pLightGroup)
{
	// nullなら
	if (pLightGroup == nullptr)
	{
		// デフォルト代入
		pLightGroup_ = Default::sLightGroup_.get();
		return;
	}

	// 代入
	pLightGroup_ = pLightGroup;
}

#pragma endregion

#pragma region Common

std::unique_ptr<YGame::ViewProjection> ModelObject::Default::sVP_ = nullptr;
std::unique_ptr<YGame::LightGroup> ModelObject::Default::sLightGroup_ = nullptr;
std::unique_ptr<YGame::Color> ModelObject::Default::sColor_ = nullptr;

void ModelObject::Default::StaticInitialize()
{
	// 生成
	sVP_.reset(new YGame::ViewProjection());
	sVP_->Initialize({});

	sLightGroup_.reset(LightGroup::Create(false));

	sColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
}

#pragma endregion


