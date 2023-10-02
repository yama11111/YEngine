#include "SelectDrawer.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "Def.h"
#include "Keys.h"
#include "Pad.h"
#include <cassert>

using YGame::SelectDrawer;
using YMath::Vector3;

YGame::Sprite2D* SelectDrawer::spLogoSpr_ = nullptr;
YGame::Sprite2D* SelectDrawer::spStickSpr_ = nullptr;
YGame::Sprite2D* SelectDrawer::spButtonSpr_ = nullptr;

void SelectDrawer::StaticInitialize()
{
	spLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("select/stage_logo.png")} });

	spStickSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/stick_L.png")} });

	spButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });
}

void SelectDrawer::Initialize()
{
	core_ = Transform::Status::Default();

	// 地球
	earthTra_.Initialize();
	earthTra_.parent_ = &core_.m_;
	earthDra_.reset(EarthDrawer::Create(&earthTra_, 1));

	// ステージトランスフォーム (使う用)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i].Initialize();
		aliveStages_[i].parent_ = &core_.m_;
	}

	// ステージトランスフォーム (使わない用)
	deadStage_.Initialize();

	size_t stageNum = 10;

	// ステージ描画クラス
	stageDras_.resize(stageNum); // リサイズ
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i].reset(StageDrawer::Create(nullptr, 0));

		// 番号がトランスフォームの数より小さいなら
		if (i < aliveStages_.size())
		{
			// 使う用のトランスフォームを代入
			stageDras_[i]->Initialize(&aliveStages_[i], 1);
		}
		// それ以外なら
		else
		{
			// 使わない用のトランスフォームを代入
			stageDras_[i]->Initialize(&deadStage_, 1);
		}
	}


	// ステージカード
	cards_.resize(stageNum);
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i].Initialize();
	}

	// ステージカード描画クラス
	cardDras_.resize(stageNum);
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i].reset(new CardDrawer());
		cardDras_[i]->Initialize(&cards_[i], static_cast<int>(i + 1));
	}

	letterBox_.reset(new UILetterBox());
	letterBox_->Initialize(WinSize, 96.0f, 96.0f);

	// ウィンドウサイズ を 3次元ベクトルにしておく
	Vector3 win = YMath::ConvertToVector3(WinSize);

	// ロゴ初期化
	Vector3 logoPos = (win / 2.0f) - Vector3(288.0f, 288.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, spLogoSpr_));

	Vector3 stickPos = (win / 2.0f) + Vector3(-448.0f, 288.0f, 0.0f);
	stickObj_.reset(DrawObjectForSprite2D::Create({ stickPos, {}, {1.0f,1.0f,1.0f} }, spStickSpr_));

	Vector3 buttonPos = (win / 2.0f) + Vector3(-288.0f, 308.0f, 0.0f);
	DrawObjectForSprite2D* newStartButton = DrawObjectForSprite2D::Create({ buttonPos, {}, {1.0f,1.0f,0.0f} }, spButtonSpr_);
	startButton_.reset(UIButton::Create(newStartButton));


	// 天球
	skydomeTra_.Initialize();
	skydomeTra_.scale_ = { 32.0f,32.0f,32.0f };
	skydomeTra_.parent_ = &core_.m_;
	skydome_.reset(SkydomeDrawer::Create(&skydomeTra_, 3));

	// ----- イージング ----- //

	// ステージ回転用パワー
	int32_t staNum = static_cast<int32_t>(stageNum) - 1;
	stageRotaPows_.resize(static_cast<size_t>(staNum)); // リサイズ
	
	// リセット
	Reset();
}

void SelectDrawer::Reset()
{
	// ----- オブジェクト初期化 ----- //

	// 核
	core_.Initialize();

	// 大きさの量
	float earthScaleVal = 32.0f;
	// 回転の量
	float rotaVal = (PI * 2.0f) / static_cast<float>(aliveStages_.size());

	// 地球
	earthTra_.Initialize({ {},{},{earthScaleVal,earthScaleVal,earthScaleVal} });

	// ----- ステージ ----- //

	// トランスフォーム (使う用)
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		// 位置
		float pos = earthScaleVal - 0.5f;

		// 回転 ((360 / size) * idx)
		float rota = rotaVal * i;

		// 回転量に合わせた位置になるように
		aliveStages_[i].Initialize(
			{
				{ 0.0f, +pos * cosf(rota), +pos * sinf(rota) }, // 位置
				{ rota, 0, 0 }, // 回転
				{ 1.0f, 1.0f, 1.0f } // 大きさ
			}
		);
	}
	// トランスフォーム (使わない用)
	deadStage_.Initialize({ {-2000,-2000,-2000}, {}, {} });

	// 描画クラス
	//for (size_t i = 0; i < stageDras_.size(); i++)
	//{
	//	// 種類
	//	TowerDrawerCommon::Type type = TowerDrawerCommon::Type::eBlack;

	//	// クリアしているなら変更
	//	if (spStageConfig_->GetIsClearStage((int)i))
	//	{
	//		// クリアしているなら変更
	//		type = TowerDrawerCommon::Type::eWhite;
	//	}

	//	stageDras_[i]->Reset(type);
	//}

	// ----- ステージカード ----- //

	// 高さの幅
	float heightVal = 448.0f / static_cast<float>(10 - 1);

	// トランスフォーム (親)
	for (size_t i = 0; i < cards_.size(); i++)
	{
		// y の位置
		float y = WinSize.y_ / 2.0f + 8.0f + (448 / 2.0f)
			- heightVal * static_cast<float>(i);

		cards_[i].Initialize(
			{
				{WinSize.x_ - 96.0f, y, 0.0f },
				{},
				{ 1.0f, 1.0f, 1.0f }
			}
		);
	}
	// 描画クラス
	//for (size_t i = 0; i < cardDras_.size(); i++)
	//{
	//	// クリアしているなら変更
	//	cardDras_[i]->Reset(spStageConfig_->GetIsClearStage((int)i));
	//}

	// 天球

	// ----- その他初期化 ----- //

	// 動作中か
	isAct_ = false;

	// 開始時回転用イージング
	startRotaEas_.Initialize(0.0f, -rotaVal / 2.0f, 1.4f);

	// 開始時回転用タイマー
	startRotaTim_.Initialize(20);
	startRotaTim_.SetActive(true);


	// ステージ回転用イージング
	stageRotaEas_.Initialize(0.0f, -rotaVal, 1.4f);

	// ステージ回転用パワー
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		stageRotaPows_[i].Initialize(30);
	}
}

void SelectDrawer::UpdateRotaAnimation()
{
	// 回転量
	float rotaVal = 0.0f;

	// 開始時回転タイマー更新
	startRotaTim_.Update();
	// 開始時回転を代入
	rotaVal += startRotaEas_.In(startRotaTim_.Ratio());

	// ステージ数分回転させる
	// 回転をその分スタート
	for (size_t i = 0; i < stageRotaPows_.size(); i++)
	{
		//回転させるか
		bool isRotaAct = false;

		// 現在のステージ数より番号が小さいなら
		if (i < static_cast<size_t>(stageIndex_))
		{
			// 動作する
			isRotaAct = true;
		}

		// 更新
		stageRotaPows_[i].Update(isRotaAct);

		// 回転させるならイーズイン
		if (isRotaAct) { rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio()); }
		// それ以外ならイーズアウト
		else { rotaVal += stageRotaEas_.Out(stageRotaPows_[i].Ratio()); }

		//rotaVal += stageRotaEas_.In(stageRotaPows_[i].Ratio());
	}

	// 核に代入 (回転)
	core_.rota_.x_ = rotaVal;
}

void SelectDrawer::Update()
{
	// 動作中じゃないなら弾く
	//if (isAct_ == false) { return; }

	// アニメーションの回転更新
	UpdateRotaAnimation();

	// 核
	core_.UpdateMatrix();

	// 地球
	earthDra_->Update();

	// ----- ステージ ----- //

	// トランスフォーム
	for (size_t i = 0; i < aliveStages_.size(); i++)
	{
		aliveStages_[i].UpdateMatrix();
	}
	// 描画クラス
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Update();
	}

	// ----- ステージカード ----- //

	// トランスフォーム
	for (size_t i = 0; i < cards_.size(); i++)
	{
		cards_[i].UpdateMatrix();
	}
	// 描画クラス
	for (size_t i = 0; i < cardDras_.size(); i++)
	{
		cardDras_[i]->Update();

		// 選択中か
		bool isSelect = false;

		// 選択中のステージ番号のとき
		int staIdx = stageIndex_;
		if (i == staIdx)
		{
			// 選択
			isSelect = true;
		}

		// 選択中か設定
		cardDras_[i]->SetSelect(isSelect);
	}

	skydome_->Update();

	letterBox_->Update();
	logoObj_->Update();
	stickObj_->Update();
	startButton_->Update(
		YInput::Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
		YInput::Pad::GetInstance()->IsTrigger(YInput::PadButton::XIP_A));

}

void SelectDrawer::Draw()
{
	// 天球
	skydome_->Draw();

	// ステージ描画
	for (size_t i = 0; i < stageDras_.size(); i++)
	{
		stageDras_[i]->Draw();
	}

	// 地球
	earthDra_->Draw();

	// レターボックス描画
	letterBox_->Draw("Sprite2DDefault", 40);

	// カード描画 (後ろから)
	for (int i = static_cast<int>(cardDras_.size()) - 1; i >= 0; i--)
	{
		cardDras_[i]->Draw(i * 2);
	}

	logoObj_->Draw("Sprite2DDefault", 1);
	stickObj_->Draw("Sprite2DDefault", 1);
	startButton_->Draw("Sprite2DDefault", 1);
}
