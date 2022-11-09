#include "GameScene.h"
#include "Calc.h"
#include "Def.h"
#include <cassert>

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Game;

Keys* GameScene::keys_ = nullptr;
Mouse* GameScene::mouse_ = nullptr;
Pad* GameScene::pad_ = nullptr;
TextureManager* GameScene::pTexManager_ = nullptr;

void GameScene::StaticInitialize(TextureManager* pTexManager)
{
	assert(pTexManager);
	pTexManager_ = pTexManager;

	keys_ = Keys::GetInstance();
	mouse_ = Mouse::GetInstance();
	pad_ = Pad::GetInstance();
}

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize()
{
	plainTex = pTexManager_->Load(L"Resources/white.png", false);

	m1.reset(new Model());
	s1.reset(new Sprite({ 64,64 }));

	t1.Initialize({});
	t2.Initialize({});
	t3.Initialize({});

	vp.Initialize({});
}

void GameScene::Update()
{
	t1.Update();
	t2.Update();
	t3.Update();

	vp.Update();
}

void GameScene::Draw()
{
	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- 背景スプライト ----- //

	s1->Draw(t1, plainTex);

	// -------------------------- //
	Model::StaticSetDrawCommand();
	// --------- モデル --------- //

	m1->Draw(t2, vp, plainTex);

	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //

	s1->Draw(t3, plainTex);
	
	// -------------------------- //
}
