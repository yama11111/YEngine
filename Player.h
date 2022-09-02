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

	Object3D body[3];
	Model* model = nullptr;
	UINT tex = 0;
	Keys* keys = nullptr;
	Mouse* mouse = nullptr;
	bool play = false;
public:
	void Initialize(Model* model, const UINT tex);
	void InitStatus();
	void Update(RailCamera& rCamera, const bool play);
	void Draw(MatViewProjection& vP);
	void Draw2D();
	void Damege(const int damage) { status.hp -= damage; }
	void SetCamera(Mat4* camera) { this->camera = camera; }
	void SetVelocity(const Vec3& vel) { this->velocity = vel; }
	void SetPre(const Vec3& pre) { this->previous = pre; }
	void SetPos(const Vec3& pos) { this->obj.mW.pos = pos; }
	Vec3 GetWorldPos() override;
	void OnCollision(const int damage) override;
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets; }
private:
	void Move();
	void Adjust();
	void CalcVelocity();
	void Attack();
	void ModelInit();
};
