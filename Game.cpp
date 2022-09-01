#include "Game.h"
#include "Calc.h"
#include "MonoEye.h"
#include "WaveAngler.h"
#include "Croan.h"
#include "Octos.h"
#include "Def.h"

Game::Game() {}

Game::~Game()
{
	delete m1;
	delete s1;
}

void Game::Initialize()
{
	//ShowCursor(false);

	keys = Keys::GetInstance();
	mouse = Mouse::GetInstance();
	rand = Random::GetInstance();
	texM = TextureManager::GetInstance();
	srvH = DXSRVHeap::GetInstance();
	srvH->SetRootParameter();
	pplnSet2D.Create2D();
	pplnSet3D.Create3D();

	enemyTex = texM->Load(L"Resources/enemy.png");
	playerTex = texM->Load(L"Resources/player.png");
	plainTex = texM->Load(L"Resources/white.png", false);
	skyTex = texM->Load(L"Resources/sky.jpg", false);

	m1 = new Model();

	s1 = new Sprite(WIN_SIZE);

	Player* newPlayer = new Player();
	newPlayer->Initialize(m1, playerTex, plainTex);
	player.reset(newPlayer);

	WaveInit();

	CollisionManager* newCollManager = new CollisionManager();
	newCollManager->Initialize();
	collManager.reset(newCollManager);

	rCamera.Initialize({ 0,0,-100 });
}

void Game::Update()
{
	WaveUpdate();
	enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });
	rCamera.Update();
	if (scene == Scene::Title)
	{
		if (keys->IsTrigger(DIK_K)) scene = Scene::Play;
	}
	else if (scene == Scene::Play)
	{
		if (keys->IsTrigger(DIK_K)) scene = Scene::Title;
		
		player->Update(rCamera);
		//Move();
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			enemy->Update();
		}
		Collision();
	}
	vp = rCamera.GetViewProjectionD();
	vp.Update();
}

void Game::Draw()
{
	pplnSet2D.SetCommand2D();
	srvH->SetDescriptorHeaps();
	// ----- 背景スプライト ----- //
	
	s1->Draw(sky, skyTex);

	// -------------------------- //
	pplnSet3D.SetCommand3D();
	srvH->SetDescriptorHeaps();
	// --------- モデル --------- //

	if (scene == Scene::Title)
	{
		
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

	player->Draw2D();
	
	// -------------------------- //
}

void Game::Collision()
{
	collManager->Clear();
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player->GetBullets();
	collManager->PushBack(player.get());
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) 
	{
		collManager->PushBack2(bullet.get());
	}
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy->GetBullets();
		collManager->PushBack2(enemy.get());
		for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) 
		{
			collManager->PushBack(bullet.get());
		}
	}
	collManager->Update();
}

void Game::WaveInit()
{
	for (size_t i = 0; i < 4; i++)
	{
		int a = 1;
		int b = 1;
		if (i == 1 || i == 2) a *= -1;
		if (i == 2 || i == 3) b *= -1;
		std::unique_ptr<Enemy> newEnemy = std::make_unique<MonoEye>();
		newEnemy->SetPlayer(player.get());
		newEnemy->Initialize({100.0f * a , 40.0f * b, 100 }, m1, enemyTex, plainTex);
		enemys.push_back(std::move(newEnemy));
	}
}

void Game::WaveUpdate()
{
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		if (enemy->IsDead()) num++;
	}
	if (num >= 4)
	{
		WaveInit();
		num = 0;
	}
}

void Game::Move()
{
	int a = 1;
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		a *= -1;
		Vec3 pos = enemy->GetWorldPos();
		pos.x += 1.0f;
		if (pos.x <= -40 * a) pos.x = -40 * a;
		enemy->SetPos(pos);
	}
	
}
