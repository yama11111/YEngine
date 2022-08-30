#pragma once
#include "Sprite.h"

class Cursor
{
public:
	Vec2 pos = { 0,0 };
	Vec3 scale = { 1,1,1 };
	Vec4 color = { 1,1,1,1 };
	bool shot = false;
	bool target = false;
	bool charge = false;
	enum CursorTexNum
	{
		General = 0,
		Charge = 1,
		Num = 2,
	};
private:
	Object2D obj[4];
	Sprite* sprite[Num];
	UINT cursorTex[Num];
	UINT shadowTex[Num];
public:
	Cursor();
	void Initialize(Sprite* sprite[Num], const UINT cursorTex[Num], const UINT shadowTex[Num]);
	void Update();
	void Draw();
	void SetShot(const bool shot) { this->shot = shot; }
	void SetTarget(const bool target) { this->target = target; }
	void SetCharge(const bool charge) { this->charge = charge; }
private:
	void ObjUpdate();
};

