#include "BaseDrawer.h"
#include <cassert>

using YGame::BaseDrawer;

YGame::ViewProjection* BaseDrawer::spVP_ = nullptr;

void BaseDrawer::Initialize(Transform* pParent, const uint16_t drawPriority)
{	
	// オブジェクト + 定数バッファ生成
	// 生成後、オブジェクトに挿入
	obj_.reset(DrawObjectForModel::Create(Transform::Status::Default(), spVP_, nullptr));

	// 親設定
	SetParent(pParent);

	cbColor_.reset(ConstBufferObject<CBColor>::Create());
	obj_->InsertConstBuffer(cbColor_.get());

	cbMaterial_.reset(ConstBufferObject<CBMaterial>::Create());
	cbMaterial_->data_.ambient = { 0.2f,0.2f,0.2f };
	obj_->InsertConstBuffer(cbMaterial_.get());

	cbLightGroup_.reset(ConstBufferObject<CBLightGroup>::Create());
	cbLightGroup_->data_.direLights[0].active = 1.0f;
	obj_->InsertConstBuffer(cbLightGroup_.get());

	cbTexConfig_.reset(ConstBufferObject<CBTexConfig>::Create());
	obj_->InsertConstBuffer(cbTexConfig_.get());


	drawPriority_ = drawPriority;

	isVisible_ = true;

	isVisibleUpdate_ = true;

	animationBitFlag_ = 0;

	animeStatus_ = {};
}

void BaseDrawer::Update()
{
	obj_->Update(animeStatus_);
}

void BaseDrawer::VisibleUpdate()
{
	if (isVisibleUpdate_ == false)
	{
		cbColor_->data_.texColorRate.a_ = 1.0f;

		return;
	}

	// 視点との距離
	float distance = YMath::Vector3(spVP_->eye_ - pParent_->pos_).Length();

	// 描画範囲
	static const float kRange = 750.0f;

	// 視点との距離の比率でアルファ値変化(遠いほど薄く)
	float distanceRate = 1.0f - distance / kRange;
	if (distanceRate >= 0.8f) { distanceRate = 1.0f; }

	cbColor_->data_.texColorRate.a_ = distanceRate;

	// 一定値以下は描画切る
	isVisible_ = (distanceRate >= 0.25f);
}

void BaseDrawer::Draw()
{
	if (isVisible_ == false) { return; }

	obj_->Draw(shaderKey_, drawPriority_);
}

void BaseDrawer::SetParent(Transform* pParent)
{
	pParent_ = pParent;

	obj_->SetParent(pParent);
}

void BaseDrawer::StaticInitialize(ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);

	// 代入
	spVP_ = pVP;
}

BaseDrawer::BaseDrawer(const uint16_t drawPriority)
{
	Initialize(nullptr, drawPriority);
}

BaseDrawer::BaseDrawer(Transform* pParent, const uint16_t drawPriority)
{
	Initialize(pParent, drawPriority);
}

void BaseDrawer::DrawDebugTextContent()
{

}
