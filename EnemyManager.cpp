#include "EnemyManager.h"
#include "MonoEye.h"
#include "WaveAngler.h"
#include "Croan.h"
#include "Octos.h"
#include "Player.h"

void EnemyManager::Initialize(Player* player, Model* model, const UINT plainTex)
{
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Croan>();
	newEnemy->SetPlayer(player);
	newEnemy->Initialize({ 0, 40, 100 }, model, plainTex);
	enemys.push_back(std::move(newEnemy));

	//std::unique_ptr<Enemy> newEnemy2 = std::make_unique<Enemy>();
	//newEnemy2->SetPlayer(player.get());
	//newEnemy2->Initialize({ 50, 20, 50 }, m1, enemyTex, plainTex);
	//enemys.push_back(std::move(newEnemy2));

	//std::unique_ptr<Enemy> newEnemy3 = std::make_unique<Enemy>();
	//newEnemy3->SetPlayer(player.get());
	//newEnemy3->Initialize({ -50, 20, -10 }, m1, enemyTex, plainTex);
	//enemys.push_back(std::move(newEnemy3));
}

void EnemyManager::Update()
{
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update();
	}
}

void EnemyManager::Collision()
{
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy->GetBullets();
		collM->PushBack2(enemy.get());
		for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets)
		{
			collM->PushBack(bullet.get());
		}
	}
}


void EnemyManager::Draw(MatViewProjection& mVP)
{
	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw(mVP);
	}
}