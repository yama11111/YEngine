#include "InfectionBlocks.h"
#include "MathUtil.h"
#include "Def.h"
#include <cassert>

using YScene::InfectionBlocks;
using YGame::Transform;
using YGame::Sprite2D;
using YGame::CBColor;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YGame::Sprite2D* InfectionBlocks::spBlockSpr_ = nullptr;
YMath::Vector2 InfectionBlocks::sLeftTop_;
YMath::Vector2 InfectionBlocks::sNum_;
YMath::Vector2 InfectionBlocks::sAnchor_;
float InfectionBlocks::sSize_ = 0.0f;

void InfectionBlocks::StaticInitialize(YGame::Texture* pBlockTex)
{
	// スプライト生成
	spBlockSpr_ = Sprite2D::Create({}, { pBlockTex });

	// 左上
	sLeftTop_ = {};

	// 数
	sNum_ = { 15.0f,8.0f };

	// アンカーポイント
	sAnchor_ = { 0.0f,1.0f };

	// 大きさ
	sSize_ = 128.0f;
}

void InfectionBlocks::Initialize()
{
	// クリア + リサイズ
	blocks_.clear();
	blocks_.resize(static_cast<size_t>(sNum_.y_));
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		blocks_[y].resize(static_cast<size_t>(sNum_.x_));
	}

	// 初期化
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			// ブロック生成 + 初期化
			blocks_[y][x].reset(new Block());

			blocks_[y][x]->color_.reset(CBColor::Create({ 0.0f,0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
			blocks_[y][x]->obj_.reset(Sprite2D::Object::Create(Transform::Status::Default(), blocks_[y][x]->color_.get(), nullptr, false));

			// 2ブロック間の距離
			Vector2 dist = { sSize_ * x, sSize_ * y };
			// 位置
			Vector2 p = sLeftTop_ + dist;
			// 代入
			blocks_[y][x]->obj_->pos_ = { p.x_, p.y_, 0.0f };
		}
	}

	scaleEas_[0].Initialize(0.0f, sSize_, 4.0f);
	scaleEas_[1].Initialize(sSize_, 0.0f, 4.0f);

	rotaEas_[0].Initialize(-PI, 0.0f, 4.0f);
	rotaEas_[1].Initialize(0.0f, +PI, 4.0f);

	colorEas_[0].Initialize(0.7f, 0.0f, 2.0f);
	colorEas_[1].Initialize(0.0f, 0.0f, 2.0f);

	alphaEas_[0].Initialize(0.5f, 1.0f, 2.0f);
	alphaEas_[1].Initialize(1.0f, 0.5f, 2.0f);

	Reset();
}

void InfectionBlocks::Reset()
{
	// リセット
	step_ = Step::Narrow;

	isAct_ = false;
	isFalling_ = false;
	isChangeMoment_ = false;
	isRising_ = false;
	isEnd_ = false;

	loadTim_.Reset(false);

	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			blocks_[y][x]->obj_->rota_ = {};
			blocks_[y][x]->obj_->scale_ = {};
			blocks_[y][x]->actTim_.Reset(false);
			blocks_[y][x]->colorStartTim_.Reset(false);
			blocks_[y][x]->colorEndTim_.Reset(false);
		}
	}

	stepIndex_ = 0;

	start_ = {};
}

void InfectionBlocks::Finalize()
{
}

void InfectionBlocks::Activate(const uint32_t changeFrame, const uint32_t loadFrame)
{
	// リセット
	Reset();

	// 読み込みタイマー初期化
	loadTim_.Initialize(loadFrame);


	// タイマー初期化 + 開始
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			blocks_[y][x]->actTim_.Initialize(changeFrame);

			blocks_[y][x]->colorStartTim_.Initialize(changeFrame * 4);

			blocks_[y][x]->colorEndTim_.Initialize(changeFrame / 4);
		}
	}

	// 動作開始
	isAct_ = true;
	isFalling_ = true;

	// 配列の x y の大きさ
	Vector2 size =
	{
		static_cast<float>(blocks_[0].size() - 1),
		static_cast<float>(blocks_.size() - 1)
	};


	// アンカーポイント基準の位置 を 始点 とする
	float sX = sAnchor_.x_ * size.x_;
	float sY = sAnchor_.y_ * size.y_;

	// 始点
	start_ = { sX,sY };

	// 始点のタイマー開始
	blocks_[static_cast<size_t>(sY)][static_cast<size_t>(sX)]->SetTimerActive(true);


	// 半分の地点
	Vector2 halfSize =
	{
		size.x_ / 2.0f,
		size.y_ / 2.0f
	};

	// 始点の逆側 を 終点 とする
	float eX = 0, eY = 0;
	if (sX <= halfSize.x_) { eX = size.x_; }
	if (sY <= halfSize.y_) { eY = size.y_; }

	// 終点
	end_ = { eX, eY };
}

void InfectionBlocks::UpdateChange()
{
	// 動作中じゃないなら弾く
	if (isAct_ == false) { return; }

	// 瞬間フラグをfalseに
	isChangeMoment_ = false;

	// 狭まっている なら
	if (step_ == Step::Narrow)
	{
		// 要素番号
		size_t x = blocks_[0].size() - 1;
		size_t y = blocks_.size() - 1;

		// タイマーが終了したなら
		if (blocks_[y][x]->actTim_.IsEnd())
		{
			// 段階 → 読み込み
			step_ = Step::Load;
			

			// 幕開けフラグをtfalseに
			isFalling_ = false;

			// 瞬間フラグをtrueに
			isChangeMoment_ = true;
						
			
			// 読み込みタイマー開始
			loadTim_.SetActive(true);
		
		}
	
	}
	// 読み込み中 なら
	else if (step_ == Step::Load)
	{
		// 読み込みタイマー更新
		loadTim_.Update();

		// 読み込みタイマーが終了したら
		if (loadTim_.IsEnd())
		{
			// 段階 → 明転
			step_ = Step::Spread;

			// 現段階のインデックスを 1 に
			stepIndex_ = 1;


			// 瞬間フラグをfalseに
			isChangeMoment_ = false;

			// 幕開けフラグをtrueに
			isRising_ = true;


			// ブロックごとに
			for (size_t i = 0; i < blocks_.size(); i++)
			{
				for (size_t j = 0; j < blocks_[i].size(); j++)
				{
					// タイマーリセット
					blocks_[i][j]->actTim_.Reset(false);
					blocks_[i][j]->colorStartTim_.Reset(false);
					blocks_[i][j]->colorEndTim_.Reset(false);
				}
			}

			// 要素番号
			size_t x = static_cast<size_t>(start_.x_);
			size_t y = static_cast<size_t>(start_.y_);

			// タイマースタート
			blocks_[y][x]->SetTimerActive(true);
		}
	}
	// 広がっている なら
	else if (step_ == Step::Spread)
	{
		// ブロックの終端
		size_t x = static_cast<size_t>(end_.x_);
		size_t y = static_cast<size_t>(end_.y_);

		// ブロック終端のタイマーが終了したら
		if (blocks_[y][x]->actTim_.IsEnd())
		{
		
			// 終了
			Reset();

			// 終了フラグをtrueに
			isEnd_ = true;

		}
	}
}

void InfectionBlocks::PropagateBlock(const size_t x, const size_t y)
{
	// X 範囲制限用
	bool moreX = (x >= blocks_[y].size() - 1);
	bool lessX = (x <= 0);
	// Y 範囲制限用
	bool moreY = (y >= blocks_.size() - 1);
	bool lessY = (y <= 0);

	// 全てのパターンでタイマー開始 (総当たり)
	// 範囲内なら 要素 + 1 or 要素 - 1
	if (!moreX) { blocks_[y][x + 1]->SetTimerActive(true); }
	if (!moreY && !moreX) { blocks_[y + 1][x + 1]->SetTimerActive(true); }
	if (!moreY) { blocks_[y + 1][x]->SetTimerActive(true); }
	if (!moreY && !lessX) { blocks_[y + 1][x - 1]->SetTimerActive(true); }
	if (!lessX) { blocks_[y][x - 1]->SetTimerActive(true); }
	if (!lessY && !lessX) { blocks_[y - 1][x - 1]->SetTimerActive(true); }
	if (!lessY) { blocks_[y - 1][x]->SetTimerActive(true); }
	if (!lessY && !moreX) { blocks_[y - 1][x + 1]->SetTimerActive(true); }
}

void InfectionBlocks::UpdateBlock()
{
	// 動作中じゃないなら弾く
	if (isAct_ == false) { return; }

	// ブロックの数だけ
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			// タイマーが終了したら
			if (blocks_[y][x]->actTim_.IsEnd())
			{
				// 隣のブロックに伝播
				PropagateBlock(x, y);
			}

			// ブロックのタイマー更新
			blocks_[y][x]->actTim_.Update();
			blocks_[y][x]->colorStartTim_.Update();
			blocks_[y][x]->colorEndTim_.Update();

			// イージング
			// stepIndex_ が 0 ならイーズアウト
			// stepIndex_ が 1 ならイーズイン

			// 拡縮
			float s = 0.0f;
			if (stepIndex_ == 0) { s = scaleEas_[0].Out(blocks_[y][x]->actTim_.Ratio()); }
			if (stepIndex_ == 1) { s = scaleEas_[1].In(blocks_[y][x]->actTim_.Ratio()); }

			// 回転
			float r = 0.0f;
			if (stepIndex_ == 0) { r = rotaEas_[0].Out(blocks_[y][x]->actTim_.Ratio()); }
			if (stepIndex_ == 1) { r = rotaEas_[1].In(blocks_[y][x]->actTim_.Ratio()); }

			// オブジェクトに代入 + 更新
			blocks_[y][x]->obj_->scale_ = { s, s, 0.0f };
			blocks_[y][x]->obj_->rota_.z_ = r;

			blocks_[y][x]->obj_->UpdateMatrix();


			// 色 (青)
			float blue = 0.0f;
			if (stepIndex_ == 0) { blue = colorEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { blue = colorEas_[1].In(blocks_[y][x]->colorEndTim_.Ratio()); }

			// アルファ値
			float alpha = 0.0f;
			if (stepIndex_ == 0) { alpha = alphaEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { alpha = alphaEas_[1].In(blocks_[y][x]->colorEndTim_.Ratio()); }

			// 色代入
			blocks_[y][x]->color_->SetRGBA({ 0.0f, 0.0f, blue, alpha });
		}
	}
}

void InfectionBlocks::Update()
{
	UpdateChange();
	UpdateBlock();
}

void InfectionBlocks::Draw()
{
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			spBlockSpr_->SetDrawCommand(blocks_[y][x]->obj_.get(), YGame::DrawLocation::eFront);
		}
	}
}
