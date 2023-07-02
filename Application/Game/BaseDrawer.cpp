#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const DrawLocation location)
{
	// オブジェクト生成
	obj_.reset(Model::Object::Create());

	// 親設定
	SetParent(pParent);

	// 色
	color_.reset(CBColor::Create());
	obj_->SetColor(color_.get());
	
	// マテリアル
	material_.reset(CBMaterial::Create());
	material_->SetAmbient({ 0.2f,0.2f,0.2f });
	obj_->SetMaterial(material_.get());
	
	// テクスチャ設定
	texConfig_.reset(CBTexConfig::Create());
	obj_->SetTexConfig(texConfig_.get());

	// ビュープロジェクション設定
	obj_->SetViewProjection(spVP_);

	// 描画位置
	location_ = location;

	// 描画フラグ
	isVisible_ = true;

	// 描画するか更新フラグ
	isVisibleUpdate_ = true;
}

void BaseDrawer::Update()
{
	VisibleUpdate();

	// オブジェクト更新
	obj_->UpdateMatrix();
}

void BaseDrawer::VisibleUpdate()
{
	if (isVisibleUpdate_ == false)
	{
		color_->SetTexColorRateAlpha(1.0f);

		return;
	}

	// 視点との距離
	float distance = YMath::Vector3(spVP_->eye_ - pParent_->pos_).Length();

	// 描画範囲
	static const float kRange = 750.0f;

	float distaceRate = 1.0f - distance / kRange;
	if (distaceRate >= 0.8f) { distaceRate = 1.0f; }

	// 視点との距離の比率でアルファ値変化(遠いほど薄く)
	color_->SetTexColorRateAlpha(distaceRate);

	// 一定値以下は描画切る
	isVisible_ = (color_->GetTexColorRate().a_ >= 0.25f);
}

void BaseDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	// 描画
	pModel_->SetDrawCommand(obj_.get(), location_, shader_);
}

void BaseDrawer::SetParent(Transform* pParent)
{
	// 親トランスフォームポインタ設定
	pParent_ = pParent;

	// null じゃないなら
	if (pParent_)
	{
		// 親子関係設定
		obj_->parent_ = &pParent_->m_;
	}
	// 違うなら
	else
	{
		// 親子関係初期化
		obj_->parent_ = nullptr;
	}
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);

	// 代入
	spVP_ = pVP;
}

BaseDrawer::BaseDrawer(const DrawLocation location)
{
	Initialize(nullptr, location);
}

BaseDrawer::BaseDrawer(Transform* pParent, const DrawLocation location)
{
	Initialize(pParent, location);
}

void BaseDrawer::DrawDebugTextContent()
{

}
