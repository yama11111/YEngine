#include "LightGroup.h"
#include "MathUtillity.h"
#include <cassert>

using YGame::LightGroup;
using YMath::Vector3;
using YMath::Clamp;

const std::array<Vector3, LightGroup::DireLightNum_> DefaultDirection1 =
{
	Vector3( 0.0f,-1.0f, 0.0f),
	Vector3(+0.5f,+0.1f,+0.2f),
	Vector3(-0.5f,+0.1f,-0.2f),
};

const std::array<Vector3, LightGroup::PointLightNum_> DefaultPos1 =
{
	Vector3( 0.0f,+5.0f, 0.0f),
	Vector3(+5.0f,-2.5f, 0.0f),
	Vector3(-5.0f,-2.5f, 0.0f),
};

const std::array<Vector3, LightGroup::SpotLightNum_> DefaultPos2 =
{
	Vector3(  0.0f,+15.0f, 0.0f),
	//Vector3(+15.0f,+15.0f,  0.0f),
	//Vector3(-15.0f,+15.0f,  0.0f),
};

LightGroup::LightGroup() :
	ambientColor_(1.0f, 1.0f, 1.0f),
	direLights_(), pointLights_()//, spotLights_()
{}

LightGroup* LightGroup::Create()
{
	LightGroup* instance = new LightGroup();
	instance->cBuff_.Create();
	instance->Initialize();

	return instance;
}

void LightGroup::Initialize(const YMath::Vector3& ambientColor)
{
	SetAmbientColor(ambientColor);

	// ----- 平行光源 ----- //
	for (size_t i = 0; i < DireLightNum_; i++)
	{
		direLights_[i].Initialize(DefaultDirection1[i]);
		direLights_[i].SetActive(true);
	}
	// ----- 点光源 ----- //
	for (size_t i = 0; i < PointLightNum_; i++)
	{
		pointLights_[i].Initialize(DefaultPos1[i]);
		pointLights_[i].SetActive(true);
	}
	// ----- スポットライト光源 ----- //
	for (size_t i = 0; i < SpotLightNum_; i++)
	{
		spotLights_[i].Initialize(DefaultPos2[i]);
		//spotLights_[i].SetActive(true);
	}
}

void LightGroup::SetDrawCommand(const UINT rootParamIndex)
{
	cBuff_.map_->ambientColor_ = ambientColor_;
	
	// ----- 平行光源 ----- //
	for (size_t i = 0; i < DireLightNum_; i++)
	{
		if (direLights_[i].IsActive())
		{
			cBuff_.map_->direLights_[i].lightVec_	 = direLights_[i].Direction();
			cBuff_.map_->direLights_[i].lightColor_	 = direLights_[i].Color();
			cBuff_.map_->direLights_[i].active_ = 1;
		}
		else
		{
			cBuff_.map_->direLights_[i].active_ = 0;
		}
	}
	
	// ----- 点光源 ----- //
	for (size_t i = 0; i < PointLightNum_; i++)
	{
		if (pointLights_[i].IsActive())
		{
			cBuff_.map_->pointLights_[i].lightPos_	 = pointLights_[i].Pos();
			cBuff_.map_->pointLights_[i].lightColor_ = pointLights_[i].Color();
			cBuff_.map_->pointLights_[i].lightAtten_ = pointLights_[i].Atten();
			cBuff_.map_->pointLights_[i].active_ = 1;
		}
		else
		{
			cBuff_.map_->pointLights_[i].active_ = 0;
		}
	}

	// ----- スポットライト光源 ----- //
	//for (size_t i = 0; i < SpotLightNum_; i++)
	//{
	//	if (spotLights_[i].IsActive())
	//	{
	//		cBuff_.map_->spotLights_[i].lightPos_ = spotLights_[i].Pos();
	//		cBuff_.map_->spotLights_[i].lightVec_ = spotLights_[i].Direction();
	//		cBuff_.map_->spotLights_[i].lightColor_ = spotLights_[i].Color();
	//		cBuff_.map_->spotLights_[i].lightAtten_ = spotLights_[i].Atten();
	//		cBuff_.map_->spotLights_[i].lightStartFactorAngleCos_ = spotLights_[i].StartFactorAngleCos();
	//		cBuff_.map_->spotLights_[i].lightEndFactorAngleCos_ = spotLights_[i].EndFactorAngleCos();
	//		cBuff_.map_->spotLights_[i].active_ = 1;
	//	}
	//	else
	//	{
	//		cBuff_.map_->spotLights_[i].active_ = 0;
	//	}
	//}

	cBuff_.SetDrawCommand(rootParamIndex);
}

void LightGroup::SetAmbientColor(const YMath::Vector3& color)
{
	float r = Clamp<float>(color.x_, 0.0f, 1.0f);
	float g = Clamp<float>(color.y_, 0.0f, 1.0f);
	float b = Clamp<float>(color.z_, 0.0f, 1.0f);

	cBuff_.map_->ambientColor_ = ambientColor_ = Vector3(r, g, b);
}
void LightGroup::SetAmbientColor(const UINT R, const UINT G, const UINT B)
{
	float r = R <= 255 ? R / 255.0f : 1.0f;
	float g = G <= 255 ? G / 255.0f : 1.0f;
	float b = B <= 255 ? B / 255.0f : 1.0f;
	Vector3 c = Vector3(r, g, b);

	SetAmbientColor(c);
}

// ----- 平行光源 ----- //
void LightGroup::SetDirectionalLightDirection(const size_t index, const YMath::Vector3& direction)
{
	assert(index < DireLightNum_);
	direLights_[index].SetDirection(direction);
}
void LightGroup::SetDirectionalLightColor(const size_t index, const YMath::Vector3& color)
{
	assert(index < DireLightNum_);
	direLights_[index].SetColor(color);
}
void LightGroup::SetDirectionalLightActive(const size_t index, const bool isAct)
{
	assert(index < DireLightNum_);
	direLights_[index].SetActive(isAct);
}

// ----- 点光源 ----- //
void LightGroup::SetPointLightPos(const size_t index, const YMath::Vector3& pos)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetPos(pos);
}
void LightGroup::SetPointLightColor(const size_t index, const YMath::Vector3& color)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetColor(color);
}
void LightGroup::SetPointLightAtten(const size_t index, const YMath::Vector3& atten)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetAtten(atten);
}
void LightGroup::SetPointLightActive(const size_t index, const bool isAct)
{
	assert(index < PointLightNum_);
	pointLights_[index].SetActive(isAct);
}

// ----- スポットライト光源 ----- //
void LightGroup::SetSpotLightPos(const size_t index, const YMath::Vector3& pos)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetPos(pos);
}
void LightGroup::SetSpotLightDirection(const size_t index, const YMath::Vector3& direction)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetDirection(direction);
}
void LightGroup::SetSpotLightColor(const size_t index, const YMath::Vector3& color)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetColor(color);
}
void LightGroup::SetSpotLightAtten(const size_t index, const YMath::Vector3& atten)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetAtten(atten);
}
void LightGroup::SetSpotLightFactorAngleCos(const size_t index, const float start, const float end)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetStartFactorAngleCos(start);
	spotLights_[index].SetEndFactorAngleCos(end);
}
void LightGroup::SetSpotLightActive(const size_t index, const bool isAct)
{
	assert(index < SpotLightNum_);
	spotLights_[index].SetActive(isAct);
}
