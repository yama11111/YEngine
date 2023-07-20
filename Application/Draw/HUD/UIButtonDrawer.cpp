//#include "UIButtonDrawer.h"
//
//using YGame::UIButtonDrawer;
//
//void UIButtonDrawer::Initialize(Texture* pButtonTex, Texture* pPressedTex, Texture* pDeadTex)
//{
//	// ----- スプライト生成 ----- //
//
//	// ボタン
//	pButtonSpr_[0] = Sprite2D::Create({}, { pButtonTex });
//
//	// 押されたボタン
//	pButtonSpr_[1] = Sprite2D::Create({}, { pPressedTex });
//
//	// 死んだボタン
//	if (pDeadTex)
//	{
//		pDeadButtonSpr_ = Sprite2D::Create({}, { pDeadTex });
//	}
//
//	// ----- その他 ----- //
//
//	// 押されたか
//	isPush_ = false;
//
//	// 押せないか
//	isDead_ = false;
//}
//
//void UIButtonDrawer::Update(const bool isPush)
//{
//	// フラグ更新
//	isPush_ = isPush;
//}
//
//void UIButtonDrawer::Draw(Sprite2D::Object* pObject)
//{
//	// ボタン描画
//	pButtonSpr_[isPush_]->SetDrawCommand(pObject, DrawLocation::eFront);
//
//	// 死んでいたら
//	if (isDead_)
//	{
//		// デッドボタン描画
//		pDeadButtonSpr_->SetDrawCommand(pObject, DrawLocation::eFront);
//	}
//}
//
//void UIButtonDrawer::SetIsDead(const bool isDead)
//{
//	// あるなら
//	if (pDeadButtonSpr_)
//	{
//		// 代入
//		isDead_ = isDead;
//	}
//}
