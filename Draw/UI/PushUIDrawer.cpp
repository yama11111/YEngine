//#include "PushUIDrawer.h"
//
//using YGame::PushUIDrawer;
//
//void PushUIDrawer::Initialize(const YMath::Vector3& startPos, const YMath::Vector3& endPos)
//{
//	obj_.Initialize({startPos});
//
//	endPos_ =  startPos - endPos;
//
//	Reset();
//}
//
//void PushUIDrawer::Reset()
//{
//	InitializeSlimeAction();
//}
//
//void PushUIDrawer::Update()
//{
//	UpdateSlimeAction();
//
//	YMath::Vector3 p = endPos_;
//	YMath::Vector3 s = SlimeActionValue();
//
//	obj_.UpdateMatrix({ p, {}, s });
//}
//
//void PushUIDrawer::Draw()
//{
//	pButtons_[isPush_]->Draw(obj_.get());
//}
//
//void PushUIDrawer::Push()
//{
//	isPush_ = true;
//}
//
//void PushUIDrawer::PushSlime()
//{
//	ActivateSlimeAction({ {}, {0.1f,-0.1f,0}, {-0.1f,0.1f,0} }, 4);
//	Push();
//}
//
//void PushUIDrawer::SetSprites(YGame::Sprite2D* on, YGame::Sprite2D* off)
//{
//	pButtons_[0] = on;
//	pButtons_[1] = off;
//}
