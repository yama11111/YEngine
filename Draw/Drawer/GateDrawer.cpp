#include "GateDrawer.h"
#include "CalcTransform.h"
#include "CharaConfig.h"
#include <cassert>

#pragma region 名前空間

using YGame::Model;
using YGame::Color;
using YGame::ObjectModel;
using YGame::SlimeActor;
using YMath::Vector3;

#pragma endregion

#pragma region Static

// 静的 モデル配列 初期化
std::array<std::unique_ptr<Model>, GateDrawerCommon::PartsNum_> GateDrawerCommon::sModels_ =
{ nullptr, nullptr, };

void GateDrawerCommon::StaticInitialize()
{
	// ----- モデル読み込み ----- //

	// 体
	sModels_[static_cast<size_t>(Parts::Frame)].reset(Model::LoadObj("player/player_body", true));
	sModels_[static_cast<size_t>(1)].reset(Model::LoadObj("player/player_body", true));
}

#pragma endregions

void GateDrawer::Initialize(YMath::Matrix4* pParent)
{
	// nullチェック
	assert(pParent);

	// オブジェクト生成 + 親行列挿入
	obj_.reset(ObjectModel::Create({}));
	obj_->parent_ = pParent;

	// オブジェクト生成 + 親行列挿入 (パーツの数)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i].reset(ObjectModel::Create({}));
		modelObjs_[i]->parent_ = &obj_->m_;
	}

	// リセット
	Reset();
}

void GateDrawer::Reset()
{
	// 初期化
	SlimeActor::Initialize();

	obj_->Initialize({});

	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->Initialize({});
	}

	idelTim_.Initialize(CharaConfig::Player::IdleIntervalFrame);
	idelTim_.SetActive(true);
}

void GateDrawer::Update()
{
	// 立ちモーションタイマー更新
	idelTim_.Update();

	// タイマーが終わったら
	if (idelTim_.IsEnd())
	{
		// 立ちモーション再生
		IdleAnimation();
		// タイマーリセット
		idelTim_.Reset(true);
	}

	// 行列更新 (親)
	obj_->UpdateMatrix(
		{
			-SlimeActor::JiggleValue(),
			{},
			SlimeActor::JiggleValue()
		}
	);

	// 行列更新 (子)
	for (size_t i = 0; i < modelObjs_.size(); i++)
	{
		modelObjs_[i]->UpdateMatrix();
	}
}

void GateDrawer::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup)
{
	// 描画
	for (size_t i = 0; i < sModels_.size(); i++)
	{
		sModels_[i]->Draw(modelObjs_[i].get(), vp, lightGroup);
	}
}

void GateDrawer::IdleAnimation()
{
	// 伸縮量
	Vector3 val = obj_->scale_ * CharaConfig::SlimeAct::ElasticityValue;
	val.y_ *= -1.0f;

	// つぶれる量
	Vector3 squash = +val;
	// のびる量
	Vector3 streach = -val;

	// 時間 (フレーム)
	unsigned int frame = CharaConfig::SlimeAct::Frame;
	// 指数 (緩急)
	float pow = CharaConfig::SlimeAct::Power;

	// ぷよぷよアニメーション
	SlimeActor::Activate(
		{
			{{}, frame, pow},
			{squash, frame, pow},
			{streach, frame, pow},
			{{}, frame, pow },
		}
	);
}
