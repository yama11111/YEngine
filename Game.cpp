#include "Game.h"
#include "Calc.h"
#include "Def.h"
#include <cassert>

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Object;

Keys* Game::keys_ = nullptr;
Mouse* Game::mouse_ = nullptr;
Pad* Game::pad_ = nullptr;
TextureManager* Game::pTexManager_ = nullptr;

void Game::StaticInitialize(TextureManager* pTexManager)
{
	assert(pTexManager != nullptr);
	pTexManager_ = pTexManager;

	keys_ = Keys::GetInstance();
	mouse_ = Mouse::GetInstance();
	pad_ = Pad::GetInstance();
}

Game::Game() {}

Game::~Game() {}

void Game::Initialize()
{
	plainTex = pTexManager_->Load(L"Resources/white.png", false);

	m1.reset(new Model());
	s1.reset(new Sprite({ 64,64 }));

	t1.Initialize({});
	t2.Initialize({});
	t3.Initialize({});

	vp.Initialize({});
}

void Game::Update()
{
	t1.Update();
	t2.Update();
	t3.Update();

	vp.Update();
}

void Game::Draw()
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
