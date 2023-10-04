#include "CardDrawer.h"
#include "MathVector.h"
#include <cassert>

using YGame::CardDrawer;
using YMath::Vector3;

YGame::Sprite2D* CardDrawer::spCardSpr_ = nullptr;

void CardDrawer::LoadResource()
{
	spCardSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("select/card.png")} });
}

void CardDrawer::Initialize(Transform* pParent, const int32_t number, const bool isClear)
{
	assert(0 < number);
	number_ = number;

	// ----- 生成 ----- //

	// 核
	core_ = Transform::Status::Default();
	core_.parent_ = &pParent->m_;

	// 色
	color_.reset(ConstBufferObject<CBColor>::Create());

	// クリア色
	//clearCharaColor_.reset(CBColor::Create());

	// ステージカードオブジェクト
	cardObj_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), spCardSpr_));
	cardObj_->SetParent(&core_.m_);

	// 数字
	numberTra_.Initialize({ {}, {}, {0.5f,0.5f,0.0f} });
	numberTra_.parent_ = &core_.m_;
	numberUI_.reset(UINumber::Create2D(static_cast<uint32_t>(number_), 2, 64.0f, false, &numberTra_.m_));

	// リセット
	Reset(isClear);
}

void CardDrawer::Reset(const bool isClear)
{
	// ----- オブジェクト初期化 ----- //

	// 核
	core_.Initialize();

	// 数字
	numberTra_.Initialize({ {}, {}, {0.5f,0.5f,0.0f} });
	
	// カード
	cardObj_->Initialize();
	cardObj_->SetParent(&core_.m_);

	// 色初期化
	color_->data_.baseColor = { 1.0f,1.0f,1.0f,1.0f };

	// 色初期化
	//clearCharaColor_->SetRGBA({ 1.0f,1.0f,0.0f,1.0f });

	// ----- アニメーション ----- //

	// 選択されているか
	isSelected_ = false;
	// 選択されていたか
	isElderSelected_ = false;
	// 決定されたか
	isDecided_ = false;

	// 移動用イージング
	moveEas_.Initialize(0.0f, -128.0f, 1.2f);
	// 拡大用イージング
	scaleEas_.Initialize(0.0f, 0.25f, 1.2f);
	// 選択用パワー
	selectPow_.Initialize(10);

	// クリアしたか
	isClear_ = isClear;
}

void CardDrawer::UpdateSelectAnimation()
{
	// ----- ブヨブヨアニメーション ----- //
	
	//// 選択された瞬間
	//if (isSelected_ && isElderSelected_ == false)
	//{
	//	// 伸縮量
	//	Vector3 val = core_->scale_ * SlimeAction::Value;

	//	// 潰し伸ばし
	//	Vector3 squash = +val;
	//	Vector3 streach = -val;

	//	// 時間
	//	unsigned int frame = SlimeAction::Frame;
	//	// 指数
	//	float exponent = SlimeAction::Exponent;

	//	// 動作する
	//	SlimeActor::Activate(
	//		{ 
	//			{ {}, frame, exponent},
	//			{ streach, frame, exponent },
	//			{ squash, frame, exponent },
	//			{ {}, frame, exponent }
	//		}
	//	);
	//}

	// 選択を記録
	isElderSelected_ = isSelected_;


	// -------- アニメーション --------- //

	// 選択中ならパワー更新
	selectPow_.Update(isSelected_);
	
	// ----- 移動 ----- //

	// 移動量
	float moveVal = 0.0f;
	
	// 選ばれているなら
	if (isSelected_)
	{
		// イーズイン代入
		moveVal = moveEas_.In(selectPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズアウト代入
		moveVal = moveEas_.Out(selectPow_.Ratio());
	}

	// 移動量代入
	core_.pos_.x_ = moveVal;

	
	// ----- 拡大 ----- //

	// 移動量
	float scaleVal = 0.0f;

	// 選ばれているなら
	if (isSelected_)
	{
		// イーズイン代入
		scaleVal = scaleEas_.In(selectPow_.Ratio());
	}
	// それ以外なら
	else
	{
		// イーズアウト代入
		scaleVal = scaleEas_.Out(selectPow_.Ratio());
	}

	// 移動量代入
	core_.scale_ = Vector3(1.0f, 1.0f, 1.0f) + Vector3(scaleVal, scaleVal, 0.0f);

	
	// -------------- 色 -------------- //

	// 色の値
	Vector3 colorVal = {};
	Vector3 clearColorVal = {};

	// 選ばれているなら
	if (isSelected_)
	{
		// 通常色に
		colorVal = { 1.0f,1.0f,1.0f };
		clearColorVal = { 0.25f,1.0f,0.75f };
	}
	// それ以外なら
	else
	{
		// 暗い色に
		colorVal = { 0.25f,0.25f,0.25f };
		clearColorVal = Vector3(0.25f, 1.0f, 0.75f) * 0.25f;
	}

	// 色設定
	YMath::Vector4 color = { colorVal.x_,colorVal.y_,colorVal.z_,color_->data_.baseColor.a_ };
	color_->data_.baseColor = color;
	//clearCharaColor_->SetRGB(clearColorVal);
}

void CardDrawer::Update()
{
	// 選択アニメーション更新
	UpdateSelectAnimation();

	// 核
	core_.UpdateMatrix();

	// 数字
	numberTra_.UpdateMatrix();
	numberUI_->Update();

	// カード
	cardObj_->Update();
}

void CardDrawer::Draw(uint16_t p)
{
	cardObj_->Draw("Sprite2DDefault", p + 2);
	numberUI_->Draw("Sprite2DDefault", p + 1);
}
