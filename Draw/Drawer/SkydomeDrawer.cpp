#include "SkydomeDrawer.h"

using YGame::ModelObject;
using YGame::Model;
using YGame::Color;

Model* SkydomeDrawerCommon::spModel_ = nullptr;

void SkydomeDrawerCommon::StaticInitialize()
{
	// モデル読み込み
	spModel_ = Model::Load("skydome", true);
}

void SkydomeDrawer::Initalize(YMath::Matrix4* pParent)
{
	// 色生成
	color_.reset(Color::Create());

	// オブジェクト生成
	obj_.reset(ModelObject::Create({}, nullptr, color_.get(), nullptr, nullptr));
	
	// 親行列代入
	obj_->parent_ = pParent;

	// リセット
	Reset();
}

void SkydomeDrawer::Reset()
{
	// オブジェクト初期化
	obj_->Initialize(
		{
			{},
			{},
			{ 200.0f, 200.0f, 200.0f }
		}
	);
}

void SkydomeDrawer::Update()
{
	// オブジェクト更新
	obj_->UpdateMatrix();
}

void SkydomeDrawer::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}
