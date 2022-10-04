#pragma once
#include "Keys.h"
#include "Mouse.h"
#include "PipelineSet.h"
#include "Sprite.h"
#include "Model.h"
//#include "Player.h"
//#include "EnemyManager.h"
//#include "Shake.h"
//#include "RailCamera.h"

class Game
{
public:
	Input::Keys* keys = nullptr;
	Input::Mouse* mouse = nullptr;
	//Math::Random* rand = nullptr;
	DX::GPUResource::TextureManager* texM = nullptr;
	DX::ShaderResourceView* srvH = nullptr;
	DX::PipelineSet pplnSet2D;
	DX::PipelineSet pplnSet3D;

	UINT plainTex = 0;

	Object::Model* m1 = nullptr;
	Object::Sprite* s1 = nullptr;
	Object::Transform t;
	Object::MatViewProjection vp;

public:
	Game();
	~Game();
	void Initialize();
	void Update();
	void Draw();
};

