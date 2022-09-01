#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "DXPipelineSet.h"
#include "Sprite.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Shake.h"
#include "RailCamera.h"

class Game
{
public:
	Keys* keys = nullptr;
	Mouse* mouse = nullptr;
	Random* rand = nullptr;
	TextureManager* texM = nullptr;
	DXSRVHeap* srvH = nullptr;
	DXPipelineSet pplnSet2D;
	DXPipelineSet pplnSet3D;

	UINT enemyTex = 0;
	UINT playerTex = 0;
	UINT plainTex = 0;
	UINT skyTex = 0;

	Model* m1 = nullptr;
	Sprite* s1 = nullptr;
	Object2D sky{};

	std::unique_ptr<Player> player;
	std::list<std::unique_ptr<Enemy>> enemys;
	std::unique_ptr<CollisionManager> collManager;

	MatViewProjection vp{};
	Shake* shake = nullptr;
	RailCamera rCamera;

	enum class Scene
	{
		Title,
		Play
	};

	Scene scene = Scene::Play;

	int num = 0;
public:
	Game();
	~Game();
	void Initialize();
	void Update();
	void Draw();
private:
	void WaveInit();
	void WaveUpdate();
	void Move();
	void Collision();
};

