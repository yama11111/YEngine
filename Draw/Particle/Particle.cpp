#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::FireWork;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;

ViewProjection* IParticle::spVP_ = nullptr;
Model* FireWork::spModel_ = nullptr;

void IParticle::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;
}

void FireWork::StaticInitialize(YGame::Model* pModel)
{
	// nullチェック
	assert(pModel);
	// 初期化
	spModel_ = pModel;
}

void FireWork::Emit(
	const uint32_t aliveTime,
	const YMath::Ease<YMath::Vector3>& pos,
	const YMath::Ease<YMath::Vector3>& rota,
	const float scale,
	const YMath::Vector4& color)
{
	// 生存フラグ
	isAlive_ = true;

	// 生存タイマー初期化 + 開始
	aliveTim_.Initialize(aliveTime);
	aliveTim_.SetActive(true);
	
	// 生成
	color_.reset(Color::Create(color));
	obj_.reset(ModelObject::Create({ pos.SetStart(), {}, {scale,scale,scale} }, spVP_, color_.get(), nullptr));

	// 代入
	posEas_ = pos;
	rotaEas_ = rota;
	scaleEas_.Initialize(scale, scale / 2.0f, 3.0f);
	alphaEas_.Initialize(color.a_, 0.0f, 3.0f);

}

void FireWork::Update()
{
	// 死んでいるなら弾く
	if (isAlive_ == false) { return; }

	// 生存タイマー更新
	aliveTim_.Update();
	// 生存タイマー終了 → 死亡
	if (aliveTim_.IsEnd()) { isAlive_ = false; }

	// 位置
	obj_->pos_ = posEas_.In(aliveTim_.Ratio());
	// 回転
	obj_->rota_ = rotaEas_.In(aliveTim_.Ratio());
	// 大きさ
	float scale = scaleEas_.In(aliveTim_.Ratio());
	obj_->scale_ = { scale, scale, scale };

	// Object更新
	obj_->UpdateMatrix();

	// アルファ値
	color_->SetAlpha(alphaEas_.In(aliveTim_.Ratio()));
}

void FireWork::Draw()
{
	// 描画
	spModel_->Draw(obj_.get());
}
