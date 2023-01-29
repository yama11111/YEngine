#include "PushUIDrawer.h"

using YUIDrawer::PushUIDrawer;

void PushUIDrawer::Initialize(const YMath::Vec3& startPos, const YMath::Vec3& endPos)
{
	obj_.Initialize({startPos});

	endPos_ =  startPos - endPos;

	Reset();
}

void PushUIDrawer::Reset()
{
	InitializeSlimeAction();
}

void PushUIDrawer::Update()
{
	UpdateSlimeAction();

	YMath::Vec3 p = endPos_;
	YMath::Vec3 s = SlimeActionValue();

	obj_.UpdateMatrix({ p, {}, s });
}

void PushUIDrawer::Draw()
{
	pButtons_[isPush_]->Draw(obj_);
}

void PushUIDrawer::Push()
{
	isPush_ = true;
}

void PushUIDrawer::PushSlime()
{
	ActivateSlimeAction({ {}, {0.1f,-0.1f,0}, {-0.1f,0.1f,0} }, 4);
	Push();
}

void PushUIDrawer::SetSprites(YGame::Sprite2D* on, YGame::Sprite2D* off)
{
	pButtons_[0] = on;
	pButtons_[1] = off;
}
