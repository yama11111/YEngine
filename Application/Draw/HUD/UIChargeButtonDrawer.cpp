//#include "UIChargeButtonDrawer.h"
//#include "MathUtil.h"
//
//using YGame::UIChargeButtonDrawer;
//
//YGame::Sprite2D* UIChargeButtonDrawer::spChargeGauge_ = nullptr;
//std::unique_ptr<YGame::CBColor> UIChargeButtonDrawer::sChargeGaugeColor1_;
//std::unique_ptr<YGame::CBColor> UIChargeButtonDrawer::sChargeGaugeColor2_;
//std::unique_ptr<YGame::CBColor> UIChargeButtonDrawer::sChargeGaugeColor3_;
//
//void UIChargeButtonDrawer::Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex, const unsigned int frame)
//{
//	// 初期化
//	UIButtonDrawer::Initialize(pButtonTex, pPressedTex, pDeadTex);
//
//	// パワー初期化
//	chargePower_.Initialize(frame);
//
//	float width = static_cast<float>(pButtonTex->Buffer()->GetDesc().Width);
//	float height = static_cast<float>(pButtonTex->Buffer()->GetDesc().Height) / 8.0f;
//
//	// イージング初期化
//	chargeWidthEase_.Initialize(0.0f, width, 1.0f);
//
//	chargeGaugeObj1_.reset(Sprite2D::Object::Create());
//	chargeGaugeObj1_->SetColor(sChargeGaugeColor1_.get());
//
//	chargeGaugeObj2_.reset(Sprite2D::Object::Create());
//	chargeGaugeObj2_->SetColor(sChargeGaugeColor2_.get());
//
//	chargeGaugeObj3_.reset(Sprite2D::Object::Create());
//	chargeGaugeObj3_->SetColor(sChargeGaugeColor3_.get());
//
//	chargeGaugeObj1_->scale_ = { 0.0f, height, 0.0f };
//	chargeGaugeObj1_->pos_ = { 0.0f, height * 5.0f, 0.0f };
//	
//	chargeGaugeObj2_->scale_ = { width, height, 0.0f };
//	chargeGaugeObj2_->pos_ = { 0.0f, height * 5.0f, 0.0f };
//
//	chargeGaugeObj3_->scale_ = { width * 1.1f, height * 1.1f , 0.0f };
//	chargeGaugeObj3_->pos_ = { 0.0f, height * 5.1f, 0.0f };
//}
//
//void UIChargeButtonDrawer::Update(const bool isPush)
//{
//	UIButtonDrawer::Update(isPush);
//
//	chargePower_.Update(isPush);
//	
//	chargeGaugeObj1_->scale_.x_ = chargeWidthEase_.In(chargePower_.Ratio());
//	chargeGaugeObj1_->pos_.x_ = chargeGaugeObj1_->scale_.x_ / 2.0f - 32.0f;
//
//	chargeGaugeObj1_->UpdateMatrix();
//	chargeGaugeObj2_->UpdateMatrix();
//	chargeGaugeObj3_->UpdateMatrix();
//}
//
//void UIChargeButtonDrawer::Draw(Sprite2D::Object* pObject)
//{
//	// 死んでいたら
//	if (isDead_)
//	{
//		// デッドボタン描画
//		pDeadButtonSpr_->SetDrawCommand(pObject, DrawLocation::eFront);
//	}
//	else
//	{
//		// ボタン描画
//		pButtonSpr_[isPush_]->SetDrawCommand(pObject, DrawLocation::eFront);
//
//		chargeGaugeObj1_->parent_ = &pObject->m_;
//		chargeGaugeObj1_->UpdateMatrix();
//		chargeGaugeObj1_->parent_ = nullptr;
//
//		chargeGaugeObj2_->parent_ = &pObject->m_;
//		chargeGaugeObj2_->UpdateMatrix();
//		chargeGaugeObj2_->parent_ = nullptr;
//
//		chargeGaugeObj3_->parent_ = &pObject->m_;
//		chargeGaugeObj3_->UpdateMatrix();
//		chargeGaugeObj3_->parent_ = nullptr;
//
//		spChargeGauge_->SetDrawCommand(chargeGaugeObj3_.get(), DrawLocation::eFront);
//		spChargeGauge_->SetDrawCommand(chargeGaugeObj2_.get(), DrawLocation::eFront);
//		spChargeGauge_->SetDrawCommand(chargeGaugeObj1_.get(), DrawLocation::eFront);
//	}
//}
//
//void UIChargeButtonDrawer::StaticInitialize()
//{
//	spChargeGauge_ = Sprite2D::Create({}, { Texture::Load("white1x1.png") });
//	sChargeGaugeColor1_.reset(CBColor::Create());
//	sChargeGaugeColor1_->SetRGBA(YMath::GetColor(48, 226, 170, 255));
//	sChargeGaugeColor2_.reset(CBColor::Create());
//	sChargeGaugeColor2_->SetRGBA(YMath::GetColor(0, 0, 0, 255));
//	sChargeGaugeColor3_.reset(CBColor::Create());
//	sChargeGaugeColor3_->SetRGBA(YMath::GetColor(255, 255, 255, 255));
//}
