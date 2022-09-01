#include "Player.h"
#include <cassert>
#include "DInput.h"
#include "Calc.h"
#include "Shake.h"

static const Vec3 POS = { 0, 0, 50 };
static const Vec3 SCALE = { 5.0f, 5.0f, 5.0f };
static const float RAD = 3.0f;

static const int HP = 100;
static const int LIMIT = 60 * 1.5;

static const float POWER = 2.0f;
static const float INC_S = 0.1f;
static const float DEC_S = 0.05f;

static const float LIMIT_X = 80.0f;
static const float LIMIT_Y = 50.0f;

static const float SPEED_B = 20.0f;
static const float INTERVAL = 5.0f;

static const float SPEED_C = 10.0f;
static const float CHARGE = 90.0f;
static const float COOL = 20.0f;

static const float INC_T = 1.0f;

static const float SPEED_R = PI / 180.0f;

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

	InitStatus();
}

void Player::InitStatus()
{
	obj.mW.pos = POS;
	obj.mW.scale = SCALE;
	velocity = { 0,0,1 };
	previous = { 0,0,1 };

	status.Initialize(HP, LIMIT);
	speed.Initialize({}, POWER);
	for (size_t i = 0; i < 4; i++)
	{
		ease[i].Initialize(INC_S, DEC_S);
	}
	shotT.Initialize(INTERVAL, INC_T);
	chargeT.Initialize(CHARGE, INC_T);
	coolT.Initialize(COOL, INC_T);
	cool = false;
	target = { 0,0,0 };

	SetRad(RAD);
	SetDamage(0);
	SetAttribute(COLL_ATTRIBUTE_PLAYER);
	SetMask(~COLL_ATTRIBUTE_PLAYER);
	scope->InitStatus();
}

void Player::Update(RailCamera& rCamera)
{
	bullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead();});
	scope->Update(mouse->Pos(), rCamera.GetViewProjection());
	Move();
	Adjust();
	CalcVelocity();
	obj.Update();
	if (camera) obj.mW.m *= *camera;
	Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) 
	{
		bullet->Update();
	}

	if (status.isHit) 
	{
		rCamera.Shaking(2.5, 0.5);
		status.isHit = false;
	}
	if (status.isInvisible)
	{
		obj.cbM.Color(GetColor({ 255, 0, 0, 255 }));
	}
	else
	{
		obj.cbM.Color({ 1,1,1,1 });
	}
	status.Update();
}

void Player::Draw(MatViewProjection& vP) 
{
	//scope->Draw3D(vP);
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
	ease[0].Update(keys->IsRight());
	ease[1].Update(keys->IsLeft());
	ease[2].Update(keys->IsUp());
	ease[3].Update(keys->IsUnder());

	speed.value.x = ease[0].In(0.0f, speed.power, 2.0f) - ease[1].In(0.0f, speed.power, 2.0f);
	speed.value.y = ease[2].In(0.0f, speed.power, 2.0f) - ease[3].In(0.0f, speed.power, 2.0f);

	obj.mW.pos += speed.value;

	obj.mW.pos.x = max(obj.mW.pos.x, -LIMIT_X);
	obj.mW.pos.x = min(obj.mW.pos.x,  LIMIT_X);
	obj.mW.pos.y = max(obj.mW.pos.y, -LIMIT_Y);
	obj.mW.pos.y = min(obj.mW.pos.y,  LIMIT_Y);
}

void Player::Adjust() 
{
	if (previous.x != velocity.x)
	{
		if (previous.x < velocity.x)
		{
			previous.x += SPEED_R;
			if (previous.x >= velocity.x) previous.x = velocity.x;
		}
		if (previous.x > velocity.x) 
		{
			previous.x -= SPEED_R;
			if (previous.x <= velocity.x) previous.x = velocity.x;
		}
	}
	if (previous.y != velocity.y)
	{
		if (previous.y < velocity.y)
		{
			previous.y += SPEED_R;
			if (previous.y >= velocity.y) previous.y = velocity.y;
		}
		if (previous.y > velocity.y)
		{
			previous.y -= SPEED_R;
			if (previous.y <= velocity.y) previous.y = velocity.y;
		}
	}
	if (previous.z != velocity.z)
	{
		if (previous.z < velocity.z)
		{
			previous.z += SPEED_R;
			if (previous.z >= velocity.z) previous.z = velocity.z;
		}
		if (previous.z > velocity.z)
		{
			previous.z -= SPEED_R;
			if (previous.z <= velocity.z) previous.z = velocity.z;
		}
	}

	obj.mW.rota = AdjustAngle(previous);
}

void Player::CalcVelocity()
{
	if (scope->cursor->target)
	{
		velocity = target;
		velocity -= GetWorldPos();
		velocity = velocity.Normalized();
		scope->cursor->target = false;
	}
	else
	{
		velocity = scope->worldPos;
		velocity -= GetWorldPos();
		velocity = velocity.Normalized();
	}
}

void Player::Attack() 
{
	if (!scope->cursor->shot)
	{
		chargeT.Update();
		if (chargeT.IsEnd())
		{
			scope->cursor->charge = true;
		}
	}

	if (cool)
	{
		coolT.Update();
		if (coolT.IsEnd())
		{
			cool = false;
		}
	}

	if (scope->cursor->charge)
	{
		if (mouse->IsDown(DIM_LEFT))
		{
			scope->cursor->SetShot(true);
			Vec3 v = velocity;
			v *= SPEED_C;

			//v = MultVec3Mat4(v, obj.mW.m);
			//Vec3 pos = MultVec3Mat4(obj.mW.pos, obj.mW.m);

			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(GetWorldPos(), v, true, model, bulletTex);
			bullets.push_back(std::move(newBullet));

			scope->cursor->charge = false;
			chargeT.Reset();
			cool = true;
		}
	}
	else if (!cool)
	{
		if (scope->cursor->shot)
		{
			shotT.Update();
			if (shotT.IsEnd())
			{
				scope->cursor->SetShot(false);
				shotT.Reset();
			}
			else return;
		}
		if (mouse->IsDown(DIM_LEFT))
		{
			scope->cursor->SetShot(true);
			Vec3 v = velocity;
			v *= SPEED_B;

			//v = MultVec3Mat4(v, obj.mW.m);
			//Vec3 pos = MultVec3Mat4(obj.mW.pos, obj.mW.m);

			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(GetWorldPos(), v, false, model, bulletTex);
			bullets.push_back(std::move(newBullet));

			chargeT.Reset();
		}
	}
}

Vec3 Player::GetWorldPos() 
{
	Vec3 pos = obj.mW.pos;
	return pos;
}

void Player::OnCollision(const int damage) 
{
	status.Damage(damage);
	status.isHit = true;
}
