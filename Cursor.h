#pragma once
#include "Sprite.h"
#include "Ease.h"

class Cursor
{
public:
	Vec2 pos = { 0,0 };
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
	Vec3 scale = { 1,1,1 };
	Vec4 color = { 1,1,1,1 };

	float dist = 0.0f;
	Ease ease;
	bool rock = false;
	bool cc = false;

	Object2D obj[2];
	Object2D obj2[8];
	Sprite* sprite[Num];
	UINT cursorTex[Num];
	UINT shadowTex[Num];
public:
	Cursor();
	void Initialize(Sprite* sprite[Num], const UINT cursorTex[Num], const UINT shadowTex[Num]);
	void InitStatus();
	void Update();
	void Draw();
	void SetShot(const bool shot) { this->shot = shot; }
	void SetTarget(const bool target) { this->target = target; }
	void SetCharge(const bool charge) { this->charge = charge; }
private:
	void ChargeUpdate();
	void ColorChange();
	void ObjUpdate();
};

