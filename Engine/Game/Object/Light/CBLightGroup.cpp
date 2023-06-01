#include "CBLightGroup.h"
#include "MathUtillity.h"
#include <cassert>

#pragma region 名前空間

using YGame::CBLightGroup;
using YMath::Vector3;
using YMath::Clamp;

#pragma endregion

static const std::array<Vector3, CBLightGroup::DireLightNum_> DefaultDirection1 =
{
	Vector3( 0.0f,-1.0f, 0.0f),
	Vector3(+0.5f,+0.1f,+0.2f),
	Vector3(-0.5f,+0.1f,-0.2f),
};

static const std::array<Vector3, CBLightGroup::PointLightNum_> DefaultPos1 =
{
	Vector3( 0.0f,+5.0f, 0.0f),
	Vector3(+5.0f,-2.5f, 0.0f),
	Vector3(-5.0f,-2.5f, 0.0f),
};

static const std::array<Vector3, CBLightGroup::SpotLightNum_> DefaultPos2 =
{
	Vector3(  0.0f,+15.0f, 0.0f),
	//Vector3(+15.0f,+15.0f,  0.0f),
	//Vector3(-15.0f,+15.0f,  0.0f),
};

CBLightGroup* CBLightGroup::Create(
	const YMath::Vector3& ambientColor,
	const bool isMutable)
{
	// インスタンス生成 (動的)
	CBLightGroup* instance = new CBLightGroup();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化
	instance->Initialize(ambientColor);

	// インスタンスを返す
	return instance;
}

void CBLightGroup::Initialize(const Vector3& ambientColor)
{
	SetAmbientColor(ambientColor);

	// ----- 平行光源 ----- //
	for (size_t i = 0; i < DireLightNum_; i++)
	{
		direLights_[i].Initialize(DefaultDirection1[i]);
		direLights_[i].SetActive(false);
	}
	// ----- 点光源 ----- //
	for (size_t i = 0; i < PointLightNum_; i++)
	{
		pointLights_[i].Initialize(DefaultPos1[i]);
		pointLights_[i].SetActive(false);
	}
	// ----- スポットライト光源 ----- //
	for (size_t i = 0; i < SpotLightNum_; i++)
	{
		spotLights_[i].Initialize(DefaultPos2[i]);
		spotLights_[i].SetActive(false);
	}
}

void CBLightGroup::SetDrawCommand(const UINT rootParamIndex)
{
	// 定数バッファに設定
	cBuff_.map_->ambientColor_ = ambientColor_;
	for (size_t i = 0; i < DireLightNum_; i++)
	{
		cBuff_.map_->direLights_[i] = direLights_[i].GetData();
	}
	for (size_t i = 0; i < PointLightNum_; i++)
	{
		cBuff_.map_->pointLights_[i] = pointLights_[i].GetData();
	}
	//for (size_t i = 0; i < SpotLightNum_; i++)
	//{
	//	cBuff_.map_->spotLights_[i] = spotLights_[i].GetData();
	//}

	// シェーダーに送る
	cBuff_.SetDrawCommand(rootParamIndex);
}

void CBLightGroup::SetAmbientColor(const Vector3& color)
{
	// 0.0f ~ 1.0f の間になるように
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);
	
	// 代入
	ambientColor_ = Vector3(r, g, b);
}

// ----- 平行光源 ----- //
void CBLightGroup::SetDirectionalLightDirection(const size_t index, const Vector3& direction)
{
	assert(index < DireLightNum_);
	direLights_[index].SetDirection(direction);
}
void CBLightGroup::SetDirectionalLightColor(const size_t index, const Vector3& color)
{
	assert(index < DireLightNum_);
	direLights_[index].SetColor(color);
}
void CBLightGroup::SetDirectionalLightActive(const size_t index, const bool isAct)
{
	assert(index < DireLightNum_);
	direLights_[index].SetActive(isAct);
}

// ----- 点光源 ----- //
void CBLightGroup::SetPointLightPos(const size_t index, const Vector3& pos)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetPos(pos);
}
void CBLightGroup::SetPointLightColor(const size_t index, const Vector3& color)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetColor(color);
}
void CBLightGroup::SetPointLightAtten(const size_t index, const Vector3& atten)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetAtten(atten);
}
void CBLightGroup::SetPointLightActive(const size_t index, const bool isAct)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetActive(isAct);
}

// ----- スポットライト光源 ----- //
void CBLightGroup::SetSpotLightPos(const size_t index, const Vector3& pos)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetPos(pos);
}
void CBLightGroup::SetSpotLightDirection(const size_t index, const Vector3& direction)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetDirection(direction);
}
void CBLightGroup::SetSpotLightColor(const size_t index, const Vector3& color)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetColor(color);
}
void CBLightGroup::SetSpotLightAtten(const size_t index, const Vector3& atten)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetAtten(atten);
}
void CBLightGroup::SetSpotLightFactorAngleCos(const size_t index, const float start, const float end)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetStartFactorAngleCos(start);
	spotLights_[index].SetEndFactorAngleCos(end);
}
void CBLightGroup::SetSpotLightActive(const size_t index, const bool isAct)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetActive(isAct);
}
