#include "Game.h"
#include "Math/Calc.h"
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
	texM = DX::GPUResource::TextureManager::GetInstance();
	srvH = DX::ShaderResourceView::GetInstance();
	srvH->SetRootParameter();
	pplnSet2D.Create(DX::PipelineSet::Dimension::Two);
	pplnSet3D.Create(DX::PipelineSet::Dimension::Three);

	plainTex = texM->Load(L"Resources/white.png", false);
	titleTex = texM->Load(L"Resources/title.png", false);
	pushTex = texM->Load(L"Resources/tap.png", false);
	instructTex = texM->Load(L"Resources/instruct.png", false);
	skyTex = texM->Load(L"Resources/sky.jpg", false);
	doorTex = texM->Load(L"Resources/door.png", false);
	resetTex = texM->Load(L"Resources/reset.png", false);

	m1 = new Model();

	Vec2 back = WIN_SIZE;
	back += {50.0f, 50.0f};
	s1 = new Sprite(back);
	sky.mW.pos = { -25.0f,-25.0f,0.0f };

	titleS = new Sprite({ 1024.0f,256.0f });
	title.mW.pos = { WIN_SIZE.x / 2.0f - 512.0f, WIN_SIZE.y / 2.0f - 256.0f, 0.0f };
	title.Update();

	pushS = new Sprite({256.0f,128.0f});
	push.mW.pos = { WIN_SIZE.x / 2.0f - 128.0f, WIN_SIZE.y / 2.0f + 64.0f, 0.0f };
	push.Update();

	instructS = new Sprite({ 515.0f,152.0f });
	instruct.mW.pos = { WIN_SIZE.x / 2.0f + 240.0f, WIN_SIZE.y / 2.0f + 200.0f, 0.0f };
	instruct.mW.scale = { 0.75f,0.75f,0.75f };
	instruct.Update();

	resetS = new Sprite({ 256.0f,64.0f });
	reset.cbM.Color({ 1.0,1.0,1.0,0.0 });
	reset.Update();

	curten = new Sprite(WIN_SIZE);
	curtenB.cbM.Color({ 0.0,0.0,0.0,0.0 });
	curtenF.cbM.Color({ 0.0,0.0,0.0,0.0 });

	doorS = new Sprite({ 256.0f, 512.0f });
	door.mW.pos = { WIN_SIZE.x / 2.0f - 128.0f, WIN_SIZE.y / 2.0f - 256.0f, 0.0f };
	door.cbM.Color({ 1.0,1.0,1.0,0.0 });
	door.Update();

	Player* newPlayer = new Player();
	newPlayer->Initialize(m1, plainTex);
	player.reset(newPlayer);

	CollisionManager* newCollManager = new CollisionManager();
	newCollManager->Initialize();
	collManager.reset(newCollManager);

	rCamera.Initialize({ 0,0,-100 });
}

void Game::Update()
{
	if (scene == Scene::Title)
	{
		t1++;
		if (t1 >= 60) t1 = 0;

		if (mouse->IsTrigger(DIM_LEFT)) change = true;
		if (change)
		{
			curtenB.cbM.cMapMate->color.a += 0.1;
			curtenF.cbM.cMapMate->color.a += 0.1;
			if (curtenF.cbM.cMapMate->color.a >= 1.0f)
			{
				curtenF.cbM.cMapMate->color.a = 0.0;
				pos = -100.0f;
				player->SetPos({ -100.0f,0,50.0f });
				player->SetPre({ -1.0f,0,0 });
				player->SetVelocity({ -1.0f,0,0 });
				player->Update(rCamera, false);
				scene = Scene::Play;
			}
		}
	}
	else if (scene == Scene::Play)
	{
		if (change)
		{
			pos += 2.0f;
			player->SetPos({ pos,0,50.0f });
			if (pos >= 0)
			{
				pos = 0.0f;
				door.mW.pos.x += 1000;
				door.cbM.Color({ 1.0,1.0,1.0,1.0 });
				start = true;
				change = false;
			}
		}
		else if (start)
		{
			door.mW.pos.x -= 20.0f;
			if (door.mW.pos.x <= WIN_SIZE.x / 2.0f - 128.0f)
			{
				door.mW.pos.x = WIN_SIZE.x / 2.0f - 128.0f;
				player->SetVelocity({ 0.0f,0,1.0f });
				start = false;
				flash = true;
			}
		}
		else if (flash)
		{
			pos += 5.0f;
			curtenF.cbM.Color(GetColor({ 255, 255, 255, pos}));
			if (pos >= 255)
			{
				curtenB.cbM.Color({ 0.0,0.0,0.0,0.0 });
				door.cbM.Color({ 1.0,1.0,1.0,0.0 });
				reset.cbM.Color({ 1.0,1.0,1.0,1.0 });
				flash = false;
				dark = true;
			}
		}
		else if (dark)
		{
			pos -= 5.0f;
			curtenF.cbM.Color(GetColor({ 255, 255, 255, pos }));
			if (pos <= 0)
			{
				flash = false;
				dark = false;
				curtenF.cbM.Color({ 0.0,0.0,0.0,0.0 });
				pos = 0;
				WaveInit();
			}
		}
		else WaveUpdate();
		enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });
		rCamera.Update();

		if (keys->IsTrigger(DIK_R))
		{
			scene = Scene::Title;
			SceneInit();
		}
		
		player->Update(rCamera, !start && !change && !flash && !dark);
		//Move();
		for (std::unique_ptr<Enemy>& enemy : enemys)
		{
			enemy->Update();
		}
		Collision();
		vp = rCamera.GetViewProjectionD();
		vp.Update();
	}
	door.Update();
	curtenB.Update();
	curtenF.Update();
	title.Update();
	push.Update();
	reset.Update();
}

void Game::Draw()
{
	pplnSet2D.SetCommand();
	srvH->SetDescriptorHeaps();
	// ----- 背景スプライト ----- //

	Object2D s = sky;
	s.mW.pos += {rCamera.ShakeValue().x, rCamera.ShakeValue().x, 0.0f};
	s.Update();
	s1->Draw(s, skyTex);

	curten->Draw(curtenB, plainTex);
	doorS->Draw(door, doorTex);

	// -------------------------- //
	pplnSet3D.SetCommand();
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
	pplnSet2D.SetCommand();
	srvH->SetDescriptorHeaps();
	// ----- 前景スプライト ----- //

	if (scene == Scene::Title)
	{
		titleS->Draw(title, titleTex);
		if (t1 <= 30) pushS->Draw(push, pushTex);
		instructS->Draw(instruct, instructTex);
	}
	else
	{
		resetS->Draw(reset, resetTex);
		player->Draw2D();
	}
	curten->Draw(curtenF, plainTex);
	
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

void Game::SceneInit()
{
	change = false;
	start = false;
	flash = false;
	dark = false;
	pos = 0.0f;
	curtenB.cbM.Color({ 0.0,0.0,0.0,0.0 });
	curtenF.cbM.Color({ 0.0,0.0,0.0,0.0 });
	reset.cbM.Color({ 1.0,1.0,1.0,0.0 });
	door.mW.pos = { WIN_SIZE.x / 2.0f - 128.0f, WIN_SIZE.y / 2.0f - 256.0f, 0.0f };
	door.cbM.Color({ 1.0,1.0,1.0,0.0 });
	door.Update();
	player->InitStatus();
	enemys.clear();
	num = 0;
	count = 0;
}

void Game::WaveInit()
{
	if (!(num == count)) return;
	int r = rand->GetRand(1, 7);
	if (r == 1)
	{
		num = 4;
		for (size_t i = 0; i < num; i++)
		{
			int a = 1;
			int b = 1;
			if (i == 1 || i == 2) a *= -1;
			if (i == 2 || i == 3) b *= -1;
			std::unique_ptr<Enemy> newEnemy = std::make_unique<MonoEye>();
			newEnemy->SetPlayer(player.get());
			newEnemy->Initialize({ 100.0f * a , 40.0f * b, 250.0f }, m1, plainTex);
			enemys.push_back(std::move(newEnemy));
		}
	}
	else if (r == 2)
	{
		num = 5;

		std::unique_ptr<Enemy> newEnemy1 = std::make_unique<Octos>();
		newEnemy1->SetPlayer(player.get());
		newEnemy1->Initialize({ 100.0f, 40.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy1));

		std::unique_ptr<Enemy> newEnemy2 = std::make_unique<Octos>();
		newEnemy2->SetPlayer(player.get());
		newEnemy2->Initialize({ -100.0f, 40.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy2));

		std::unique_ptr<Enemy> newEnemy3 = std::make_unique<WaveAngler>();
		newEnemy3->SetPlayer(player.get());
		newEnemy3->Initialize({ 0.0f, 0.0f, 150.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy3));

		std::unique_ptr<Enemy> newEnemy4 = std::make_unique<MonoEye>();
		newEnemy4->SetPlayer(player.get());
		newEnemy4->Initialize({ 100.0f, -40.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy4));

		std::unique_ptr<Enemy> newEnemy5 = std::make_unique<MonoEye>();
		newEnemy5->SetPlayer(player.get());
		newEnemy5->Initialize({ -100.0f, -40.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy5));
	}
	else if (r == 3)
	{
		num = 3;

		std::unique_ptr<Enemy> newEnemy1 = std::make_unique<WaveAngler>();
		newEnemy1->SetPlayer(player.get());
		newEnemy1->Initialize({ 100.0f, -50.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy1));

		std::unique_ptr<Enemy> newEnemy2 = std::make_unique<WaveAngler>();
		newEnemy2->SetPlayer(player.get());
		newEnemy2->Initialize({ 0.0f, 50.0f, 150.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy2));

		std::unique_ptr<Enemy> newEnemy3 = std::make_unique<WaveAngler>();
		newEnemy3->SetPlayer(player.get());
		newEnemy3->Initialize({ -100.0f , -50.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy3));
	}
	else if (r == 4)
	{
		num = 9;

		for (size_t i = 0; i < 3; i++)
		{
			std::unique_ptr<Enemy> newEnemy1 = std::make_unique<Octos>();
			newEnemy1->SetPlayer(player.get());
			newEnemy1->Initialize({ 75.0f, -50.0f, 100.0f + (50.0f * i) }, m1, plainTex);
			enemys.push_back(std::move(newEnemy1));
		}

		for (size_t i = 0; i < 3; i++)
		{
			std::unique_ptr<Enemy> newEnemy2 = std::make_unique<MonoEye>();
			newEnemy2->SetPlayer(player.get());
			newEnemy2->Initialize({ 0.0f, 50.0f, 100.0f + (50.0f * i) }, m1, plainTex);
			enemys.push_back(std::move(newEnemy2));
		}

		for (size_t i = 0; i < 3; i++)
		{
			std::unique_ptr<Enemy> newEnemy3 = std::make_unique<Octos>();
			newEnemy3->SetPlayer(player.get());
			newEnemy3->Initialize({ -75.0f, -50.0f, 100.0f + (50.0f * i) }, m1, plainTex);
			enemys.push_back(std::move(newEnemy3));
		}
	}
	else if (r == 5)
	{
		num = 4;

		std::unique_ptr<Enemy> newEnemy1 = std::make_unique<Croan>();
		newEnemy1->SetPlayer(player.get());
		newEnemy1->Initialize({ 0.0f, 50.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy1));

		std::unique_ptr<Enemy> newEnemy2 = std::make_unique<Croan>();
		newEnemy2->SetPlayer(player.get());
		newEnemy2->Initialize({ -100.0f, 0.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy2));

		std::unique_ptr<Enemy> newEnemy3 = std::make_unique<Croan>();
		newEnemy3->SetPlayer(player.get());
		newEnemy3->Initialize({ 100.0f, 0.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy3));

		std::unique_ptr<Enemy> newEnemy4 = std::make_unique<Croan>();
		newEnemy4->SetPlayer(player.get());
		newEnemy4->Initialize({ 0.0f, -50.0f, 200.0f }, m1, plainTex);
		enemys.push_back(std::move(newEnemy4));
	}
	else if (r == 6)
	{
		num = 8;

		for (size_t i = 0; i < 4; i++)
		{
			std::unique_ptr<Enemy> newEnemy1 = std::make_unique<Octos>();
			newEnemy1->SetPlayer(player.get());
			newEnemy1->Initialize({ 20.0f + (20.0f * i), 0.0f, 100.0f + (50.0f * i) }, m1, plainTex);
			enemys.push_back(std::move(newEnemy1));
		}

		for (size_t i = 0; i < 4; i++)
		{
			std::unique_ptr<Enemy> newEnemy2 = std::make_unique<MonoEye>();
			newEnemy2->SetPlayer(player.get());
			newEnemy2->Initialize({ -20.0f - (20.0f * i), 0.0f, 100.0f + (50.0f * i) }, m1, plainTex);
			enemys.push_back(std::move(newEnemy2));
		}
	}
	else if (r == 7)
	{
		num = 16;
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				std::unique_ptr<Enemy> newEnemy1 = std::make_unique<MonoEye>();
				newEnemy1->SetPlayer(player.get());
				newEnemy1->Initialize({ 10.0f * cosf(PI / 2 * j) + 50.0f * cosf(PI / 2 * i),
										10.0f * sinf(PI / 2 * j) + 50.0f * sinf(PI / 2 * i),
										200.0f }, m1, plainTex);
				enemys.push_back(std::move(newEnemy1));
			}
		}
	}
}

void Game::WaveUpdate()
{
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		if (enemy->IsDead()) count++;
	}
	if (num <= count)
	{
		num = 0;
		count = 0;
		WaveInit();
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
		if (pos.x <= -40.0f * a) pos.x = -40.0f * a;
		enemy->SetPos(pos);
	}
	
}
