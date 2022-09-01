#pragma once
#include "Status.h"
#include "Speed.h"
#include "PlayerBullet.h"
#include "Scope.h"
#include "Mouse.h"
#include "Keys.h"
#include "Timer.h"
#include "RailCamera.h"
#include <memory>
#include <list>

class Player : public Collider 
{
public:
	std::unique_ptr<Scope> scope;
	Vec3 target{};
private:
	Object3D obj{};
	Status status{};
	Speed speed{};
	Vec3 velocity{};
	Vec3 previous{};
	Ease ease[4] = { {}, {}, {}, {} };

	Timer shotT{};
	Timer chargeT{};
	Timer coolT{};
	bool cool = false;
	std::list<std::unique_ptr<PlayerBullet>> bullets;

	Mat4* camera = nullptr;

	Model* model = nullptr;
	UINT tex = 0;
	UINT bulletTex = 0;
	Keys* keys = nullptr;
	Mouse* mouse = nullptr;
public:
	void Initialize(Model* model, const UINT tex, const UINT bulletTex);
	void InitStatus();
	void Update(RailCamera& rCamera);
	void Draw(MatViewProjection& vP);
	void Draw2D();
	void Damege(const int damage) { status.hp -= damage; }
	void SetCamera(Mat4* camera) { this->camera = camera; }
	Vec3 GetWorldPos() override;
	void OnCollision(const int damage) override;
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets; }
private:
	void Move();
	void Adjust();
	void CalcVelocity();
	void Attack();
};
