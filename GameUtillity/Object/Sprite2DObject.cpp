#include "Sprite2DObject.h"
#include "CalcTransform.h"
#include <cassert>
#include <memory>

#pragma region 名前空間

using YGame::Sprite2DObject;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma endregion


#pragma region Sprite2DObject

Sprite2DObject* Sprite2DObject::Create(const Status& status, const bool isMutable)
{
	// インスタンスを返す
	return Create(status, nullptr, isMutable);
}

Sprite2DObject* Sprite2DObject::Create(const Status& status, Color* pColor, const bool isMutable)
{
	// インスタンス生成 (動的)
	Sprite2DObject* instance = new Sprite2DObject();

	// 定数バッファ生成
	instance->cBuff_.Create(isMutable);

	// 初期化(デフォルト)
	instance->Initialize(status);
	instance->SetColor(pColor);

	// インスタンスを返す
	return instance;
}

void Sprite2DObject::SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex)
{
	// 行列
	cBuff_.map_->matWorld_ = m_ * Default::sProjection_;
	cBuff_.SetDrawCommand(transformRPIndex);

	// 色
	pColor_->SetDrawCommand(colorRPIndex);
}

void Sprite2DObject::SetColor(Color* pColor)
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

#pragma endregion


#pragma region Default

YMath::Matrix4 Sprite2DObject::Default::sProjection_ = YMath::Matrix4::Identity();
std::unique_ptr<YGame::Color> Sprite2DObject::Default::sColor_ = nullptr;

void Sprite2DObject::Default::StaticInitialize()
{
	// プロジェクション行列を設定
	sProjection_ = YMath::MatOrthoGraphic();

	// 生成 + 初期化
	sColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
}

#pragma endregion



