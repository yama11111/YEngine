#include "Material.h"
#include "MathUtillity.h"

#pragma region 名前空間

using YGame::Material;
using YMath::Vector3;
using YMath::Clamp;

#pragma endregion

Material* Material::Create(
	const Vector3& ambient,
	const Vector3& diffuse,
	const Vector3& specular,
	const float alpha,
	const bool isMutable)
{
	// インスタンス生成 (動的)
	Material* instance = new Material();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化
	instance->Initialize(ambient, diffuse, specular, alpha);

	// インスタンスを返す
	return instance;
}

void Material::Initialize(
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

void Material::SetDrawCommand(const UINT rpIndex)
{
	// 定数バッファに設定
	cBuff_.map_->ambient_ = ambient_;
	cBuff_.map_->diffuse_ = diffuse_;
	cBuff_.map_->specular_ = specular_;
	cBuff_.map_->alpha_ = alpha_;

	// マテリアル
	cBuff_.SetDrawCommand(rpIndex);
}

void Material::SetAmbient(const Vector3& ambient)
{
	// 0.0f ~ 1.0f の間になるように
	float x = Clamp<float>(ambient.x_, 0.0f, 1.0f);
	float y = Clamp<float>(ambient.y_, 0.0f, 1.0f);
	float z = Clamp<float>(ambient.z_, 0.0f, 1.0f);

	// 定数バッファごと代入
	cBuff_.map_->ambient_ = ambient_ = Vector3(x, y, z);
}

void Material::SetDiffuse(const Vector3& diffuse)
{
	// 0.0f ~ 1.0f の間になるように
	float x = Clamp<float>(diffuse.x_, 0.0f, 1.0f);
	float y = Clamp<float>(diffuse.y_, 0.0f, 1.0f);
	float z = Clamp<float>(diffuse.z_, 0.0f, 1.0f);

	// 定数バッファごと代入
	cBuff_.map_->diffuse_ = diffuse_ = Vector3(x, y, z);
}

void Material::SetSpecular(const Vector3& specular)
{
	// 0.0f ~ 1.0f の間になるように
	float x = Clamp<float>(specular.x_, 0.0f, 1.0f);
	float y = Clamp<float>(specular.y_, 0.0f, 1.0f);
	float z = Clamp<float>(specular.z_, 0.0f, 1.0f);

	// 定数バッファごと代入
	cBuff_.map_->specular_ = specular_ = Vector3(x, y, z);
}

void Material::SetAlpha(const float alpha)
{
	// 0.0f ~ 1.0f の間になるように
	float alp = Clamp<float>(alpha, 0.0f, 1.0f);

	// 定数バッファごと代入
	cBuff_.map_->alpha_ = alpha_ = alp;
}
