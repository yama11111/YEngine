#include "Scope.h"
#include "Calc.h"
#include "TextureManager.h"

void Scope::Initialize(Model* model, const UINT tex)
{
	TextureManager* texM = TextureManager::GetInstance();
	UINT cursorTex[Cursor::CursorTexNum::Num];
	UINT shadowTex[Cursor::CursorTexNum::Num];
	cursorTex[0] = texM->Load(L"Resources/cursor.png", false);
	cursorTex[1] = cursorTex[0];
	shadowTex[0] = texM->Load(L"Resources/cursor_shadow.png", false);
	shadowTex[1] = shadowTex[0];
	s[0] = new Sprite({ 128, 128 });
	s[1] = new Sprite({ 128, 128 });

	Cursor* newCursor = new Cursor();
	newCursor->Initialize(s, cursorTex, shadowTex);
	cursor.reset(newCursor);

	Ray* newRay = new Ray();
	newRay->Initialize({}, model, tex);
	newRay->SetLength(1000.0f);
	newRay->obj.cbM.Color({ 1,0,0,0.5f });
	ray.reset(newRay);
}

void Scope::Update(const Vec2& pos, const MatViewProjection& vP)
{
	//cursor->SetShot(true);
	cursor->pos = pos;
	ray->SetStart({vP.view.eye.x, vP.view.eye.y, vP.view.eye.z});
	Vec3 velocity = WorldPos(pos, 0.0f, vP);
	velocity -= vP.view.eye;
	ray->SetVelocity(velocity);

	cursor->Update();
	ray->Update();
}

void Scope::Draw2D()
{
	cursor->Draw();
}

void Scope::Draw3D(MatViewProjection& vP)
{
	ray->Draw(vP);
}

Scope::~Scope()
{
	for (size_t i = 0; i < 2; i++)
	{
		if (s[i] != nullptr) delete s[i];
	}
}
