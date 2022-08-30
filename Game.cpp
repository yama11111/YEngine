#include "Game.h"
#include "Calc.h"

Game::Game() {}

Game::~Game()
{
	delete m1;
	for (size_t i = 0; i < Cursor::CursorTexNum::Num; i++)
	{
		delete s[i];
	}
}

void Game::Initialize()
{
	ShowCursor(false);

	keys = Keys::GetInstance();
	mouse = Mouse::GetInstance();
	texM = TextureManager::GetInstance();
	srvH = DXSRVHeap::GetInstance();
	srvH->SetRootParameter();
	pplnSet2D.Create2D();
	pplnSet3D.Create3D();

	enemyTex = texM->Load(L"Resources/enemy.png");
	playerTex = texM->Load(L"Resources/player.png");
	plainTex = texM->Load(L"Resources/white.png", false);

	cursorTex[0] = texM->Load(L"Resources/cursor.png", false);
	cursorTex[1] = cursorTex[0];
	cursorShadowTex[0] = texM->Load(L"Resources/cursor_shadow.png", false);
	cursorShadowTex[1] = cursorShadowTex[0];

	m1 = new Model();

	s[0] = new Sprite({128, 128});
	s[1] = new Sprite({128, 128});

	Cursor* newCursor = new Cursor();
	newCursor->Initialize(s, cursorTex, cursorShadowTex);
	cursor.reset(newCursor);

	Ray* newRay = new Ray();
	newRay->Initialize({}, m1, plainTex);
	newRay->SetLength(20.0f);
	ray.reset(newRay);

	Player* newPlayer = new Player();
	newPlayer->Initialize(m1, playerTex, plainTex);
	player.reset(newPlayer);

	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->SetPlayer(player.get());
	newEnemy->Initialize({ 0, 40, 100 }, 0, m1, enemyTex, plainTex);
	enemys.push_back(std::move(newEnemy));

	//std::unique_ptr<Enemy> newEnemy2 = std::make_unique<Enemy>();
	//newEnemy2->SetPlayer(player.get());
	//newEnemy2->Initialize({ 50, 20, 100 }, 1, m1, enemyTex, bulletTex);
	//enemys.push_back(std::move(newEnemy2));

	//std::unique_ptr<Enemy> newEnemy3 = std::make_unique<Enemy>();
	//newEnemy3->SetPlayer(player.get());
	//newEnemy3->Initialize({ -50, 20, 100 }, 2, m1, enemyTex, bulletTex);
	//enemys.push_back(std::move(newEnemy3));

	CollisionManager* newCollManager = new CollisionManager();
	newCollManager->Initialize();
	collManager.reset(newCollManager);
}

void Game::Update()
{
	if (scene == Scene::Title)
	{
		if (mouse->IsTrigger(DIM_LEFT)) cursor->SetShot(true);
		cursor->pos = mouse->Pos();
		cursor->Update();
		
		ray->SetStart(WorldPos(mouse->Pos(), vp));
		ray->Update();
	}
	else if (scene == Scene::Play)
	{
		if (keys->IsTrigger(DIK_K)) scene = Scene::Title;
		
		player->Update();
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			enemy->Update();
		}
		Collision();
	}
}

void Game::Draw()
{
	pplnSet2D.SetCommand2D();
	srvH->SetDescriptorHeaps();
	// ----- 背景スプライト ----- //
	
	// -------------------------- //
	pplnSet3D.SetCommand3D();
	srvH->SetDescriptorHeaps();
	// --------- モデル --------- //

	if (scene == Scene::Title)
	{
		ray->Draw(vp);
	}
	else if (scene == Scene::Play)
	{
		player->Draw(vp);
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			enemy->Draw(vp);
		}
	}

	// -------------------------- //
	pplnSet2D.SetCommand2D();
	srvH->SetDescriptorHeaps();
	// ----- 前景スプライト ----- //

	cursor->Draw();

	// -------------------------- //
}

void Game::Collision()
{
	collManager->Clear();
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player->GetBullets();
	collManager->PushBack(player.get());
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) 
	{
		collManager->PushBack(bullet.get());
	}
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy->GetBullets();
		collManager->PushBack(enemy.get());
		for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) 
		{
			collManager->PushBack(bullet.get());
		}
	}
	collManager->Update();
}
