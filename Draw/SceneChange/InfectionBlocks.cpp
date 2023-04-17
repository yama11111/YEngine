#include "InfectionBlocks.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>

using YGame::InfectionBlocks;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Clamp;

YGame::Sprite2D* InfectionBlocks::spBlockSpr_ = nullptr;

void InfectionBlocks::StaticInitialize()
{
	// テクスチャ読み込み
	Texture* pTex = Texture::Load("white1x1.png", false);

	// スプライト生成
	spBlockSpr_ = Sprite2D::Create({}, { pTex });
}

void InfectionBlocks::Initialize(
	const uint32_t changeFrame, const uint32_t loadFrame, 
	const YMath::Vector2& leftTop, const float size, const YMath::Vector2& num, 
	const YMath::Vector2& anchor)
{
	// 要素数が 0未満 なら弾く
	assert(num.x_ > 0 && num.y_ > 0);

	// クリア + リサイズ
	blocks_.clear();
	blocks_.resize(static_cast<size_t>(num.y_));
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		blocks_[y].resize(static_cast<size_t>(num.x_));
	}

	// 初期化
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			// 2ブロック間の距離
			Vector2 dist = { size * x, size * y };

			// 位置
			Vector2 p = leftTop + dist;

			// ブロック生成 + 初期化
			blocks_[y][x].reset(new Block());

			blocks_[y][x]->color_.reset(Color::Create({ 0.0f,0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f,1.0f }, false));
			blocks_[y][x]->obj_.reset(Sprite2DObject::Create({}, blocks_[y][x]->color_.get(), false));
			blocks_[y][x]->obj_->pos_ = { p.x_, p.y_, 0.0f };
			blocks_[y][x]->actTim_.Initialize(changeFrame);
			blocks_[y][x]->colorStartTim_.Initialize(changeFrame * 4);
			blocks_[y][x]->colorEndTim_.Initialize(changeFrame / 4);
		}
	}

	scaleEas_[0].Initialize(0.0f, size, 4.0f);
	scaleEas_[1].Initialize(size, 0.0f, 4.0f);

	rotaEas_[0].Initialize(-PI, 0.0f, 4.0f);
	rotaEas_[1].Initialize(0.0f, +PI, 4.0f);

	colorEas_[0].Initialize(0.8f, 0.0f, 2.0f);
	colorEas_[1].Initialize(0.0f, 0.0f, 2.0f);
	
	alphaEas_[0].Initialize(0.5f, 1.0f, 2.0f);
	alphaEas_[1].Initialize(1.0f, 0.5f, 2.0f);

	loadTim_.Initialize(loadFrame);

	SetAnchorPoint(anchor);

	Reset();
}

void InfectionBlocks::Reset()
{
	// リセット
	step_ = Step::Narrow;

	isAct_ = false;
	isPreChange_ = false;
	isChangeMoment_ = false;
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

void InfectionBlocks::Activate()
{
	// リセット
	Reset();

	// 動作開始
	isAct_ = true;
	isPreChange_ = true;

	// 配列の x y の大きさ
	Vector2 size =
	{
		static_cast<float>(blocks_[0].size() - 1),
		static_cast<float>(blocks_.size() - 1)
	};


	// アンカーポイント基準の位置 を 始点 とする
	float sX = anchor_.x_ * size.x_;
	float sY = anchor_.y_ * size.y_;

	// 始点のタイマー開始
	blocks_[static_cast<size_t>(sY)][static_cast<size_t>(sX)]->SetTimerActive(true);

	// 始点
	start_ = { sX,sY };


	// 半分の地点
	size_t halfSizeX = static_cast<size_t>(size.x_ / 2.0f);
	size_t halfSizeY = static_cast<size_t>(size.y_ / 2.0f);

	// 始点の逆側 を 終点 とする
	size_t eX = 0, eY = 0;
	if (sX <= halfSizeX) { eX = static_cast<size_t>(size.x_); }
	if (sY <= halfSizeY) { eY = static_cast<size_t>(size.y_); }

	// 終点
	end_ =
	{
		static_cast<float>(eX),
		static_cast<float>(eY)
	};
}

void InfectionBlocks::SetAnchorPoint(const YMath::Vector2& anchor)
{
	// 0.0f ~ 1.0f になるように
	anchor_.x_ = Clamp<float>(anchor.x_, 0.0f, 1.0f);
	anchor_.y_ = Clamp<float>(anchor.y_, 0.0f, 1.0f);
}

void InfectionBlocks::ChangeUpdate()
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
			// 瞬間フラグをtrueに
			isChangeMoment_ = true;
			// 遷移中フラグをfalseに
			isPreChange_ = false;
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
		}
	}

}

void InfectionBlocks::BlockUpdate()
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
				BlockPropagate(x, y);
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


			// 色 (赤)
			float red = 0.0f;
			if (stepIndex_ == 0) { red = colorEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { red = colorEas_[1].Out(blocks_[y][x]->colorEndTim_.Ratio()); }			
			
			// アルファ値
			float alpha = 0.0f;
			if (stepIndex_ == 0) { alpha = alphaEas_[0].Out(blocks_[y][x]->colorStartTim_.Ratio()); }
			if (stepIndex_ == 1) { alpha = alphaEas_[1].Out(blocks_[y][x]->colorEndTim_.Ratio()); }

			// 色代入
			blocks_[y][x]->color_->SetRGBA({red, 0.0f,0.0f,alpha});
		}
	}
}

void InfectionBlocks::BlockPropagate(const size_t x, const size_t y)
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

void InfectionBlocks::Update()
{
	ChangeUpdate();
	BlockUpdate();
}

void InfectionBlocks::Draw()
{
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			spBlockSpr_->Draw(blocks_[y][x]->obj_.get());
		}
	}
}