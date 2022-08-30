#pragma once
#include "PlayerBullet.h"
#include "Status.h"
#include "Scope.h"
#include "Mouse.h"
#include "Keys.h"
#include <memory>
#include <list>

class Player : public Collider 
{
private:
	Object3D obj{};
	Vec3 velocity{};
	Status status{};
	Vec2 t1{};
	Vec2 t2{};
	float shotT = 0.0f;

	std::unique_ptr<Scope> scope;
	std::list<std::unique_ptr<PlayerBullet>> bullets;

	Model* model = nullptr;
	UINT tex = 0;
	UINT bulletTex = 0;
	Mat4* camera = nullptr;
	Keys* keys = nullptr;
	Mouse* mouse = nullptr;
public:
	void Initialize(Model* model, const UINT tex, const UINT bulletTex);
	void Update(MatViewProjection& vP);
	void Draw(MatViewProjection& vP);
	void Draw2D();
	void SetVelocity(const Vec3& velocity) { this->velocity = velocity; }
	void Damege(const int damage) { status.hp -= damage; }
	void SetCamera(Mat4* camera) { this->camera = camera; }
	Vec3 GetWorldPos() override;
	void OnCollision(const int damage) override;
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets; }
private:
	void Move();
	void TimerUpdate();
	void Adjust();
	void Attack();
};
