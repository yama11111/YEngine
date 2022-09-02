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

	UINT plainTex = 0;

	Model* m1 = nullptr;

	UINT titleTex = 0;
	Sprite* titleS = nullptr;
	Object2D title{};

	UINT pushTex = 0;
	Sprite* pushS = nullptr;
	Object2D push{};
	
	UINT instructTex = 0;
	Sprite* instructS = nullptr;
	Object2D instruct{};

	UINT resetTex = 0;
	Sprite* resetS = nullptr;
	Object2D reset{};

	UINT skyTex = 0;
	Sprite* s1 = nullptr;
	Object2D sky{};

	Sprite* curten = nullptr;
	Object2D curtenF{};
	Object2D curtenB{};

	UINT doorTex = 0;
	Sprite* doorS = nullptr;
	Object2D door{};

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

	Scene scene = Scene::Title;
	bool change = false;
	bool start = false;
	bool flash = false;
	bool dark = false;
	float pos = 0.0f;
	int t1 = 0;

	int num = 0;
	int count = 0;
public:
	Game();
	~Game();
	void Initialize();
	void Update();
	void Draw();
private:
	void SceneInit();
	void WaveInit();
	void WaveUpdate();
	void Move();
	void Collision();
};

