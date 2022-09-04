#include "Cursor.h"
#include "Math/Calc.h"
#include <cassert>

static const float INC = 0.05f;
static const float INC2 = 0.1f;

Cursor::Cursor() :
	ease(INC, 1.0f)
{
	for (size_t i = 0; i < Num; i++)
	{
		this->sprite[i] = nullptr;
		this->cursorTex[i] = 0;
		this->shadowTex[i] = 0;
	}
}

void Cursor::Initialize(Sprite* sprite[Num], const UINT cursorTex[Num], const UINT shadowTex[Num])
{
	for (size_t i = 0; i < Num; i++)
	{
		assert(sprite[i]);
		this->sprite[i] = sprite[i];
		this->cursorTex[i] = cursorTex[i];
		this->shadowTex[i] = shadowTex[i];
	}
	obj[0].cbM.Color({1,1,1,0.75});
	for (size_t i = 0; i < 4; i++)
	{
		obj2[i].cbM.Color({1,1,1,0.75});
	}
	ease.Initialize(INC, 1.0f);
	rock = false;
	cc = false;
}

void Cursor::InitStatus()
{
	pos = { 0,0 };
	scale = { 1,1,1 };
	color = { 1,1,1,1 };
	shot = false;
	target = false;
	charge = false;
	obj[0].cbM.Color({ 1,1,1,0.75 });
	for (size_t i = 0; i < 4; i++)
	{
		obj2[i].cbM.Color({ 1,1,1,0.75 });
	}
	ease.Initialize(INC, 1.0f);
	rock = false;
	cc = false;
}

void Cursor::Update()
{
	if (!cc)
	{
		if (shot) color = { 230, 0, 20, 255 };
		else color = { 25, 225, 40, 255 };
	}

	if (target) scale = { 0.75f, 0.75f, 1.0f };
	else scale = { 0.5f, 0.5f, 1.0f };

	ChargeUpdate();
	ColorChange();
	ObjUpdate();
}

void Cursor::Draw()
{
	sprite[General]->Draw(obj[0], shadowTex[General]);
	sprite[General]->Draw(obj[1], cursorTex[General]);
	if (charge)
	{
		for (size_t i = 0; i < 4; i++)
		{
			sprite[Charge]->Draw(obj2[i], shadowTex[Charge]);
			sprite[Charge]->Draw(obj2[i + 4], cursorTex[Charge]);
		}
	}
}

void Cursor::ChargeUpdate() 
{
	if (!charge)
	{
		rock = false;
		ease.Initialize(INC, 1.0f);
	}
	ease.Update(charge);
	if (!rock)
	{
		dist = ease.In(256.0f, 64.0f, 4.0f);
		if (ease.ratio == 1.0f)
		{
			rock = true;
			ease.Initialize(INC2, 1.0f);
		}
	}
	else
	{
		dist = ease.In(128.0f, 64.0f, 4.0f);
	}
}

void Cursor::ColorChange()
{
	if (charge && !cc && ease.ratio != 1.0f)
	{
		color = { 255,255,255,255 };
		cc = true;
	}
	if (cc && !rock)
	{
		color.r = ease.In(255, 230, 2.0f);
		color.g = ease.In(255, 230, 2.0f);
		color.b = ease.In(255, 20, 2.0f);
		if (shot)
		{
			color = { 230, 0, 20, 255 };
			cc = false;
		}
	}
	if (rock && dist == 64.0f) cc = false;
}

void Cursor::ObjUpdate()
{
	obj[1].cbM.Color(GetColor(color));
	for (size_t i = 0; i < 4; i++)
	{
		obj2[i + 4].cbM.Color(GetColor(color));
	}

	float aX = sprite[General]->size.x / 2.0f * scale.x;
	float aY = sprite[General]->size.y / 2.0f * scale.y;
	for (size_t i = 0; i < 2; i++)
	{
		obj[i].mW.pos = {pos.x - aX, pos.y - aY, 0.0f};
		obj[i].mW.scale = scale;
		obj[i].Update();
	}

	float bX = sprite[Charge]->size.x / 2.0f * scale.x;
	float bY = sprite[Charge]->size.y / 2.0f * scale.y;
	float cX = dist * scale.x;
	float cY = dist * scale.y;
	int tX = 1;
	int tY = 1;
	for (size_t i = 0; i < 4; i++)
	{
		if (i == 1) tX *= -1;
		if (i == 2) tY *= -1;
		if (i == 3) tX *= -1;

		obj2[i].mW.pos = { pos.x - tX * (bX + cX), pos.y - tY * (bY + cX), 0.0f };
		obj2[i].mW.scale = scale;
		obj2[i].mW.rota.z = PI / 2 * i;
		obj2[i].Update();
		obj2[i + 4].mW.pos = obj2[i].mW.pos;
		obj2[i + 4].mW.scale = obj2[i].mW.scale;
		obj2[i + 4].mW.rota.z = obj2[i].mW.rota.z;
		obj2[i + 4].Update();
	}
}
