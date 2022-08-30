#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "DXPipelineSet.h"
#include "Sprite.h"
#include "Scope.h"
#include "Player.h"
#include "Enemy.h"
#include "CollisionManager.h"

class Game
{
public:
	Keys* keys = nullptr;
	Mouse* mouse = nullptr;
	TextureManager* texM = nullptr;
	DXSRVHeap* srvH = nullptr;
	DXPipelineSet pplnSet2D;
	DXPipelineSet pplnSet3D;

	UINT enemyTex = 0;
	UINT playerTex = 0;
	UINT plainTex = 0;

	Model* m1 = nullptr;

	std::unique_ptr<Scope> scope;
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

