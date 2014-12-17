
#include "EnemyManager.hpp"

EnemyManager::EnemyManager()
{
	asteroidTextures = uthRS.LoadTexture("asteroidSheet.png");
	pirateTextures = uthRS.LoadTexture("enemySpriteSheet.png");
	carrierTextures = uthRS.LoadTexture("CarrierSheet.png");
	currentWave = 1;
	InitWaves(currentWave - 1);
}

void EnemyManager::SpawnEnemy(int wave, int type, float angle)
{
	auto enemy = std::shared_ptr<uth::GameObject>(new GameObject());
	enemy->transform.SetPosition(cosf(angle) * 700, sinf(angle) * 700);
	if (type == 1)
	{
		enemy->AddComponent(new EnemyAsteroidSmall(wave,angle));
		enemy->AddComponent(new uth::AnimatedSprite(asteroidTextures, 8, 4, 2, 3, 0, false, true));
		enemy->transform.SetScale(1.0f);
	}
	else if (type == 2)
	{
		enemy->AddComponent(new EnemyAsteroidCluster(wave, angle));
		enemy->AddComponent(new uth::AnimatedSprite(asteroidTextures, 8, 4, 2, 3, 0, false, true));
		enemy->transform.SetScale(2.0f);
	}
	else if (type == 3)
	{
		enemy->AddComponent(new EnemyPirateScout(wave, angle));
		enemy->AddComponent(new uth::AnimatedSprite(pirateTextures,9, 3, 3, 3, 3, false, true));
		enemy->transform.SetScale(1.0f);
	}
	else if (type == 4)
	{
		enemy->AddComponent(new EnemyPirateStriker(wave, angle));
		enemy->AddComponent(new uth::AnimatedSprite(pirateTextures, 9, 3, 3, 3, 6, false, true));
		enemy->transform.SetScale(1.0f);
	}
	else if (type == 5)
	{
		enemy->AddComponent(new EnemyPirateMarauder(wave, angle));
		enemy->AddComponent(new uth::AnimatedSprite(pirateTextures, 9, 3, 3, 3, 0, false, true));
		enemy->transform.SetScale(1.0f);
	}
	else if (type == 6)
	{
		enemy->AddComponent(new EnemyPirateCarrier(wave, angle));
		enemy->AddComponent(new uth::AnimatedSprite(pirateTextures, 3, 1, 3, 3, 0, false, true));
		enemy->transform.SetScale(1.0f);
	}
	AddChild(enemy);
	enemies.push_back(enemy);
}
void EnemyManager::UpdateEnemies(float deltaTime, int &health)
{
	float tempDistance = 0.0f;
	float tempAngle = 0.0f;
	for(int i = enemies.size() - 1; i >= 0; i--)
	{
		auto& enemy = enemies[i];
		auto& c = *enemy->GetComponent<Enemy>();

		c.UpdateMovementSpeed(deltaTime);
		c.SetDistance(c.GetDistance() - c.GetSpeed() * deltaTime);
		enemy->Update(deltaTime);
		tempDistance = c.GetDistance();
		tempAngle = c.GetAngle();
		enemy->transform.SetPosition(cosf(tempAngle)*tempDistance, sinf(tempAngle) * tempDistance);
		enemy->transform.SetRotation(pmath::radiansToDegrees(-tempAngle) + 90);

		if (c.GetDistance() <= 0)
		{
			RemoveChild(enemy);
			enemies.erase(enemies.begin() + i);
			health -= 1;
		}
		if (!c.GetAlive())
		{
			c.OnDeath();
			RemoveChild(enemy);
			enemies.erase(enemies.begin() + i);
		}
	}

}
void EnemyManager::InitWaves(int wave)
{
	waves[0].Init(wave,1, 5,5);
	waves[1].Init(wave + 1, 1, 1.5f, 20);
	waves[2].Init(wave + 2, 1, 4.5f, 6,1,2.25f,12);
	waves[3].Init(wave + 3, 1, 1.5f, 20);
	waves[4].Init(wave + 4, 1, 1.5f, 20);
	waves[5].Init(wave + 5, 1, 1.5f, 20);
	waves[6].Init(wave + 6, 1, 1.5f, 20);
	waves[7].Init(wave + 7, 1, 1.5f, 20);
	waves[8].Init(wave + 8, 1, 1.5f, 20);
	waves[9].Init(wave + 9, 1, 1.5f, 20);
}
void EnemyManager::UpdateWaves(float dt)
{
	if (!waves[currentWave - 1].allEnemiesSpawned())
	{
		int nextEnemy = waves[currentWave - 1].getEnemy(dt);
		if (nextEnemy != 0)
		{
			float spawnAngle = randomizer->GetInt(0, 360);
			if (nextEnemy == 1 || nextEnemy == 3)
			{
				for (int i = 0; i < 3; i++)
				{
					SpawnEnemy(currentWave, nextEnemy, spawnAngle+pmath::degreesToRadians(randomizer->GetFloat()*40));
				}
			}
			else if (nextEnemy == 5)
			{
				for (int i = 0; i < 2; i++)
				{
					SpawnEnemy(currentWave, nextEnemy, spawnAngle +pmath::degreesToRadians(randomizer->GetFloat()*15));
				}
			}
			else
				SpawnEnemy(currentWave, nextEnemy, spawnAngle);
			std::cout << "Spawned enemy with type " << nextEnemy << ", current wave is " << currentWave<< "." << std::endl;
		}
	}
	else if (enemies.size() == 0)
	{
		currentWave += 1;
	}
}
std::vector<std::shared_ptr<uth::GameObject>> EnemyManager::GetEnemies()
{
	return enemies;
}