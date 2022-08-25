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
	obj.mW.pos = { 0, 0, 50 };
	SetRad(3.0f);
	SetAttribute(COLL_ATTRIBUTE_PLAYER);
	SetMask(~COLL_ATTRIBUTE_PLAYER);
}

void Player::Update() 
{
	bullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead();});
	Move();
	Rotate();
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
	model->Draw(obj, vP, tex);
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) 
	{
		bullet->Draw(vP);
	}
}

//void Player::DebugText(const Vector2& leftTop) 
//{
//	debugText->SetPos(leftTop.x, leftTop.y);
//	debugText->Printf("Player");
//	debugText->SetPos(leftTop.x + 20, leftTop.y + 20);
//	debugText->Printf("translation : (%f, %f, %f)",
//		wt.translation_.x, wt.translation_.y, wt.translation_.z);
//	debugText->SetPos(leftTop.x + 20, leftTop.y + 40);
//	debugText->Printf("rotation : (%f, %f, %f)",
//		wt.rotation_.x, wt.rotation_.y, wt.rotation_.z);
//}

void Player::Move() 
{
	Vec3 move = { 0, 0, 0 };
	const float power = 1.0f;
	if (keys->IsDown(DIK_W)) move.y += power;
	if (keys->IsDown(DIK_S)) move.y -= power;
	if (keys->IsDown(DIK_D)) move.x += power;
	if (keys->IsDown(DIK_A)) move.x -= power;

	obj.mW.pos += move;

	const float LIMIT_X = 80;
	const float LIMIT_Y = 50;

	obj.mW.pos.x = max(obj.mW.pos.x, -LIMIT_X);
	obj.mW.pos.x = min(obj.mW.pos.x,  LIMIT_X);
	obj.mW.pos.y = max(obj.mW.pos.y, -LIMIT_Y);
	obj.mW.pos.y = min(obj.mW.pos.y,  LIMIT_Y);
}

void Player::Rotate() 
{
	Vec3 rota = { 0, 0, 0 };
	const float power = 0.05f;
	if (keys->IsDown(DIK_E)) rota.y += power;
	if (keys->IsDown(DIK_Q)) rota.y -= power;

	obj.mW.rota += rota;
}

Vec3 Player::GetWorldPos() 
{
	Vec3 pos = obj.mW.pos;
	return pos;
}

void Player::Attack() 
{
	if (keys->IsTrigger(DIK_SPACE)) 
	{
		const float SPEED = 10.0f;
		Vec3 velocity(0, 0, SPEED);

		velocity = MultVec3Mat4(velocity, obj.mW.m);
		Vec3 pos = MultVec3Mat4(obj.mW.pos, obj.mW.m);

		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model, pos, velocity, bulletTex);
		bullets.push_back(std::move(newBullet));
	}
}

void Player::OnCollision() { obj.cbM.Color({ 1.0,0.0,0.0,1.0 }); }
