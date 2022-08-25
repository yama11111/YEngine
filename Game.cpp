#include "Game.h"
#include "DInput.h"

Game::Game() {}

Game::~Game()
{
	delete m1;
}

void Game::Initialize()
{
	keys = Keys::GetInstance();
	texM = TextureManager::GetInstance();

	enemyTex = texM->Load(L"Resources/enemy.png");
	playerTex = texM->Load(L"Resources/player.png");
	bulletTex = texM->Load(L"Resources/white.png", false);

	m1 = new Model();

	Player* newPlayer = new Player();
	newPlayer->Initialize(m1, playerTex, bulletTex);
	player.reset(newPlayer);

	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	newEnemy->SetPlayer(player.get());
	newEnemy->Initialize({ 0, 40, 100 }, 0, m1, enemyTex, bulletTex);
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
	switch (scene)
	{
	case Game::Scene::Title:
		if (keys->IsTrigger(DIK_K)) scene = Scene::Play;
		break;
	case Game::Scene::Play:
		if (keys->IsTrigger(DIK_K)) scene = Scene::Title;
		
		player->Update();
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			enemy->Update();
		}
		Collision();
		break;
	default:
		break;
	}

}

void Game::Draw()
{
	switch (scene)
	{
	case Game::Scene::Title:
		break;
	case Game::Scene::Play:
		player->Draw(vp);
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			enemy->Draw(vp);
		}
		break;
	default:
		break;
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
