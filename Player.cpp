#include "Player.h"
#include <cassert>
#include "DInput.h"
#include "Calc.h"

void Player::Initialize(Model* model, const UINT tex, const UINT bulletTex)
{
	assert(model);
	this->model = model;
	this->tex = tex;
	this->bulletTex = bulletTex;
	keys = Keys::GetInstance();
	mouse = Mouse::GetInstance();
	Scope* newScope = new Scope();
	newScope->Initialize(model, bulletTex);
	scope.reset(newScope);

	obj.mW.pos = { 0, 0, 50 };
	obj.mW.scale = { 5.0, 5.0, 5.0 };
	velocity = { 0,0,1 };
	status.Initialize(100, 2.0f);
	SetRad(3.0f);
	SetDamage(0);
	SetAttribute(COLL_ATTRIBUTE_PLAYER);
	SetMask(~COLL_ATTRIBUTE_PLAYER);
}

void Player::Update(MatViewProjection& vP)
{
	scope->Update(mouse->Pos(), vP);
	bullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead();});
	Move();
	Adjust();
	obj.Update();
	if (camera) obj.mW.m *= *camera;
	Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) 
	{
		bullet->Update();
	}
}

void Player::Draw(MatViewProjection& vP) 
{
	scope->Draw3D(vP);
	model->Draw(obj, vP, tex);
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) 
	{
		bullet->Draw(vP);
	}
}

void Player::Draw2D()
{
	scope->Draw2D();
}

void Player::Move() 
{
	TimerUpdate();
	float p = 2.0f;
	status.speed.x = EaseIn(0.0f, status.power, t1.x, p) - EaseIn(0.0f, status.power, t2.x, p);
	status.speed.y = EaseIn(0.0f, status.power, t1.y, p) - EaseIn(0.0f, status.power, t2.y, p);

	obj.mW.pos += status.speed;

	const float LIMIT_X = 80;
	const float LIMIT_Y = 50;

	obj.mW.pos.x = max(obj.mW.pos.x, -LIMIT_X);
	obj.mW.pos.x = min(obj.mW.pos.x,  LIMIT_X);
	obj.mW.pos.y = max(obj.mW.pos.y, -LIMIT_Y);
	obj.mW.pos.y = min(obj.mW.pos.y,  LIMIT_Y);
}

void Player::TimerUpdate()
{
	float p = 0.1f;
	float d = 0.05f;
	if (keys->IsDown(DIK_RIGHT) || keys->IsDown(DIK_D))
	{
		t1.x += p;
		if (t1.x >= 1.0f) t1.x = 1.0f;
	}
	else 
	{
		t1.x -= d; 
		if (t1.x <= 0.0f) t1.x = 0.0f;
	}
	if (keys->IsDown(DIK_LEFT) || keys->IsDown(DIK_A))
	{
		t2.x += p;
		if (t2.x >= 1.0f) t2.x = 1.0f;
	}
	else
	{
		t2.x -= d;
		if (t2.x <= 0.0f) t2.x = 0.0f;
	}
	if (keys->IsDown(DIK_UP) || keys->IsDown(DIK_W))
	{
		t1.y += p;
		if (t1.y >= 1.0f) t1.y = 1.0f;
	}
	else
	{
		t1.y -= d;
		if (t1.y <= 0.0f) t1.y = 0.0f;
	}
	if (keys->IsDown(DIK_DOWN) || keys->IsDown(DIK_S))
	{
		t2.y += p;
		if (t2.y >= 1.0f) t2.y = 1.0f;
	}
	else
	{
		t2.y -= d;
		if (t2.y <= 0.0f) t2.y = 0.0f;
	}
}

void Player::Adjust() 
{
	obj.mW.rota = AdjustAngle(velocity);
}

Vec3 Player::GetWorldPos() 
{
	Vec3 pos = obj.mW.pos;
	return pos;
}

void Player::Attack() 
{
	float increase = 0.2f;
	float interval = 1.0f;
	if (scope->cursor->shot)
	{
		shotT += increase;
		if (interval <= shotT)
		{
			shotT = 0.0f;
			scope->cursor->SetShot(false);
		}
		else return;
	}
	if (mouse->IsDown(DIM_LEFT)) 
	{
		scope->cursor->SetShot(true);
		const float SPEED = 10.0f;
		Vec3 v = velocity;
		v *= SPEED;

		v = MultVec3Mat4(v, obj.mW.m);
		Vec3 pos = MultVec3Mat4(obj.mW.pos, obj.mW.m);

		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model, pos, v, bulletTex);
		bullets.push_back(std::move(newBullet));
	}
}

void Player::OnCollision(const int damage) 
{
	status.hp -= damage;
	status.CalcHp();
	obj.cbM.Color({ 1.0,0.0,0.0,1.0 });
}
