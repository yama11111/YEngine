#include "Game.h"
#include "Calc.h"

Game::Game() {}

Game::~Game()
{
	delete m1;
}

void Game::Initialize()
{
	ShowCursor(false);

	keys = Keys::GetInstance();
	mouse = Mouse::GetInstance();
	texM = TextureManager::GetInstance();

	enemyTex = texM->Load(L"Resources/enemy.png");
	playerTex = texM->Load(L"Resources/player.png");
	plainTex = texM->Load(L"Resources/white.png", false);

	m1 = new Model();

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
		//if (mouse->IsTrigger(DIM_LEFT)) scene = Scene::Play;
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
