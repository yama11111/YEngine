#include "Cursor.h"
#include "Calc.h"
#include <cassert>

Cursor::Cursor()
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
		obj[0].cbM.Color({1,1,1,0.5});
	}
}

void Cursor::Update()
{
	if (shot) color = { 230, 0, 20, 255 };
	else color = { 25, 185, 20, 255 };
	if (target) scale = { 1.5f, 1.5f, 1.0f };
	else scale = { 1.0f, 1.0f, 1.0f };

	ObjUpdate();
}

void Cursor::Draw()
{
	sprite[General]->Draw(obj[0], shadowTex[General]);
	sprite[General]->Draw(obj[1], cursorTex[General]);
	if (charge)
	{
		sprite[Charge]->Draw(obj[0], shadowTex[Charge]);
		sprite[Charge]->Draw(obj[1], cursorTex[Charge]);
	}
}

void Cursor::ObjUpdate()
{
	obj[1].cbM.Color(GetColor(color));
	for (size_t i = 0; i < 2; i++)
	{
		obj[i].mW.pos = {pos.x - 64.0f, pos.y - 64.0f, 0.0f};
		obj[i].Update();
	}
}
