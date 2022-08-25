#pragma once
#include "Keys.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "CollisionManager.h"

class Game
{
public:
	Keys* keys = nullptr;
	TextureManager* texM = nullptr;

	UINT enemyTex = 0;
	UINT playerTex = 0;
	UINT bulletTex = 0;

	Model* m1 = nullptr;

	std::unique_ptr<Player> player;
	std::list<std::unique_ptr<Enemy>> enemys;
	std::unique_ptr<CollisionManager> collManager;
	MatViewProjection vp;

	enum class Scene
	{
		Title,
		Play
	};

	Scene scene = Scene::Play;
public:
	Game();
	~Game();
	void Initialize();
	void Update();
	void Draw();
private:
	void Collision();
};

