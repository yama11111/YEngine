#include "TestScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "DefaultDrawer.h"
#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "SlimeDrawer.h"
#include "SlashAttackDrawer.h"
#include "SnortAttackDrawer.h"
#include "BlockDrawer.h"
#include "GoalDrawer.h"
#include "CloudDrawer.h"
#include "SkydomeDrawer.h"

#pragma region 名前空間宣言

using YGame::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static関連

#pragma endregion 


#pragma region 読み込み
void TestScene::Load()
{
	// 基底クラス
	BaseDrawer::StaticInitialize(&vp_);

	// デフォルト
	DefaultDrawer::LoadResource();

	// プレイヤー
	PlayerDrawer::LoadResource();

	// ウマ
	HorseDrawer::LoadResource();

	// スライム
	SlimeDrawer::LoadResource();

	// 斬撃攻撃
	SlashAttackDrawer::LoadResource();

	// 鼻息攻撃
	SnortAttackDrawer::LoadResource();

	// ブロック
	BlockDrawer::LoadResource();

	// ゴール
	GoalDrawer::LoadResource();

	// 天球
	SkydomeDrawer::LoadResource();

	// 雲
	CloudDrawer::LoadResource();

	pGraph_ = Model::CreateCube({ { "Texture0", Texture::Load("white1x1.png")} });
}
#pragma endregion


#pragma region 初期化
void TestScene::Initialize()
{
	vp_.Initialize();

	Vector3 p0 = { - 16.0f, - 12.0f, 0.0f };
	Vector3 p1 = { - 12.0f, +  6.0f, 0.0f };
	Vector3 p2 = { + 12.0f, -  6.0f, 0.0f };
	Vector3 p3 = { + 16.0f, + 12.0f, 0.0f };

	ease_.Initialize(p0, p3, 3.0f);
	bezier_.Initialize({ p0, p1, p2, p3 }, 3.0f);
	spline_.Initialize({ p0, p1, p2, p3 }, 3.0f);

	timer_.Initialize(120, true);
	power_.Initialize(120);

	lerpIdx = 2;
	ratioIdx = 0;


	obj_.	reset(DrawObjectForModel::Create({}, &vp_, pGraph_));
	start_.	reset(DrawObjectForModel::Create({}, &vp_, pGraph_));
	end_.	reset(DrawObjectForModel::Create({}, &vp_, pGraph_));

	cbColorObj_.	reset(ConstBufferObject<CBColor>::Create());
	cbColorStart_.	reset(ConstBufferObject<CBColor>::Create());
	cbColorEnd_.	reset(ConstBufferObject<CBColor>::Create());
	
	obj_->	InsertConstBuffer(cbColorObj_.get());
	start_->InsertConstBuffer(cbColorStart_.get());
	end_->	InsertConstBuffer(cbColorEnd_.get());

	obj_->transform_.pos_	 = {};
	start_->transform_.pos_	 = p0;
	end_->transform_.pos_	 = p3;
	
	obj_->transform_.scale_		 = { 1.2f,1.2f,1.2f };
	start_->transform_.scale_	 = { 1.0f,1.0f,1.0f };
	end_->transform_.scale_		 = { 1.0f,1.0f,1.0f };

	cbColorObj_->data_.baseColor	 = { 0.0f,1.0f,1.0f,1.0f };
	cbColorStart_->data_.baseColor	 = { 1.0f,0.0f,1.0f,1.0f };
	cbColorEnd_->data_.baseColor	 = { 1.0f,1.0f,0.0f,1.0f };

	ratio_ = 0.0f;
	controlPoint_ = 0.5f;
	
	isStop_ = false;
}
#pragma endregion


#pragma region 終了処理
void TestScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void TestScene::Update()
{
	{
		ImGui::Begin("Lerp");

		if (ImGui::Button("Ease")) { lerpIdx = 0; }
		if (ImGui::Button("Bezier")) { lerpIdx = 1; }
		if (ImGui::Button("Spline")) { lerpIdx = 2; }

		ImGui::Text("----- Lerp -----");

		if (lerpIdx == 0) { ImGui::Text("Type : Ease"); }
		if (lerpIdx == 1) { ImGui::Text("Type : Bezier"); }
		if (lerpIdx == 2) { ImGui::Text("Type : Spline"); }

		ImGui::Text("----------------------");

		if (ImGui::Button("Timer"))
		{
			ratioIdx = 0;
			timer_.Reset(true);
		}

		if (ImGui::Button("Power"))
		{
			ratioIdx = 1;
		}

		ImGui::Text("----- Ratio -----");

		if (ratioIdx == 0) { ImGui::Text("Ratio : Timer"); }
		if (ratioIdx == 1) { ImGui::Text("Ratio : Power"); }

		ImGui::Text("----------------------");

		if (ImGui::Button("Stop")) 
		{
			isStop_ = !isStop_;
		}
		ImGui::Text("Stop : %i", isStop_);

		ImGui::End();
	}

	if (isStop_ == false)
	{
		timer_.Update();
		if (timer_.IsEnd())
		{
			timer_.Reset(true);
		}

		power_.Update(spKeys_->IsDown(DIK_SPACE));

		if (ratioIdx == 0)
		{
			ratio_ = timer_.Ratio();
		}
		if (ratioIdx == 1)
		{
			ratio_ = power_.Ratio();
		}
	}

	ImGui::Begin("Value");

	ImGui::SliderFloat("Ratio", &ratio_, 0.0f, 1.0f);

	ImGui::SliderFloat("ControlPoint", &controlPoint_, 0.0f, 1.0f);

	ImGui::End();

	Vector3 val = {};
	
	if (lerpIdx == 0) { val = ease_.OutIn(ratio_, controlPoint_); }
	if (lerpIdx == 1) { val = bezier_.OutIn(ratio_, controlPoint_); }
	if (lerpIdx == 2) { val = spline_.OutIn(ratio_, controlPoint_); }

	obj_->transform_.pos_ = val;

	obj_->Update();
	start_->Update();
	end_->Update();
}
#pragma endregion


#pragma region 描画
void TestScene::Draw()
{
	obj_->Draw("ModelDefault", 0);
	start_->Draw("ModelDefault", 0);
	end_->Draw("ModelDefault", 0);
}
#pragma endregion