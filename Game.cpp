#include "Game.h"
#include "Calc.h"
#include "Def.h"

using namespace Input;
using namespace DX;
using namespace Math;
using namespace Object;

Game::Game() {}

Game::~Game()
{
	delete m1;
	delete s1;
}

void Game::Initialize()
{
	keys = Keys::GetInstance();
	mouse = Mouse::GetInstance();
	texM = GPUResource::TextureManager::GetInstance();
	srvH = ShaderResourceView::GetInstance();
	srvH->SetRootParameter();
	pplnSet2D.Create(PipelineState::Dimension::Two);
	pplnSet3D.Create(PipelineState::Dimension::Three);

	plainTex = texM->Load(L"Resources/white.png", false);

	m1 = new Model();
	s1 = new Sprite({ 64,64 });
}

void Game::Update()
{
	t.Update();
	vp.Update();
}

void Game::Draw()
{
	pplnSet2D.SetCommand();
	srvH->SetDescriptorHeaps();
	// ----- 背景スプライト ----- //

	s1->Draw(t, plainTex);

	// -------------------------- //
	pplnSet3D.SetCommand();
	srvH->SetDescriptorHeaps();
	// --------- モデル --------- //

	//m1->Draw(t, vp, plainTex);

	// -------------------------- //
	pplnSet2D.SetCommand();
	srvH->SetDescriptorHeaps();
	// ----- 前景スプライト ----- //
	
	// -------------------------- //
}
