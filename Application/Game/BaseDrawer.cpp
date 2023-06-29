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
