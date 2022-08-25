#pragma once
#include "PlayerBullet.h"
#include "Keys.h"
#include <memory>
#include <list>

class Player : public Collider 
{
private:
	Object3D obj{};
	Model* model = nullptr;
	std::list<std::unique_ptr<PlayerBullet>> bullets;

	UINT tex = 0;
	UINT bulletTex = 0;
	Mat4* camera = nullptr;
	Keys* keys = nullptr;
public:
	void Initialize(Model* model, const UINT tex, const UINT bulletTex);
	void Update();
	void Draw(MatViewProjection& vP);
	Vec3 GetWorldPos() override;
	void OnCollision() override;
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets; }
	void SetCamera(Mat4* camera) { this->camera = camera; }
private:
	void Move();
	void Rotate();
	void Attack();
};
