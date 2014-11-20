
#include "EnemyManager.hpp"

EnemyManager::EnemyManager()
{
	enemytexture = uthRS.LoadTexture("asteroidMockup.png");
}
void EnemyManager::SpawnEnemy(float health_,float armor_, float speed_, float angle_)
{
	auto enemy = std::shared_ptr<uth::GameObject>(new GameObject());
	enemy->AddComponent(new Enemy(health_, armor_, speed_, pmath::degreesToRadians(angle_)));
	enemy->AddComponent(new uth::AnimatedSprite(enemytexture,8,4,2,5,0,false,true));
	enemy->transform.SetPosition(cosf(angle_)*700, sinf(angle_) * 700);
	enemy->transform.SetScale(0.2f);
	AddChild(enemy);
	//A bit wonky at the moment, propably need to be reworked.
	//Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
	//float tempDistance = enemyC->GetDistance();
	//float tempAngle = enemyC->GetAngle();
	//enemy->transform.SetPosition(cosf(tempAngle)*tempDistance, sinf(tempAngle) * tempDistance);
	enemies.push_back(enemy);
}
void EnemyManager::SpawnEnemy(int wave, int type, float angle)
{
	auto enemy = std::shared_ptr<uth::GameObject>(new GameObject());
	enemy->transform.SetPosition(cosf(angle) * 700, sinf(angle) * 700);
	if (type == 1)
	{
		enemy->AddComponent(new EnemyAsteroidSmall(wave,angle));
		enemy->AddComponent(new uth::AnimatedSprite(enemytexture, 8, 4, 2, 5, 0, false, true));
		enemy->transform.SetScale(0.2f);
	}
	else if (type == 2)
	{
		enemy->AddComponent(new EnemyAsteroidCluster(wave, angle));
		enemy->AddComponent(new uth::AnimatedSprite(enemytexture, 8, 4, 2, 3, 0, false, true));
		enemy->transform.SetScale(0.5f);
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

		/*
		Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
		enemyC->SetDistance(enemyC->GetDistance() - enemyC->GetSpeed()*deltaTime);
		enemy->Update(deltaTime);

		tempDistance = enemyC->GetDistance();
		tempAngle = enemyC->GetAngle();
		enemy->transform.SetPosition(cosf(tempAngle )*tempDistance , sinf(tempAngle) * tempDistance);
		enemy->transform.SetRotation(pmath::radiansToDegrees(-tempAngle)+90);

		if (enemyC->GetDistance() <= 0)
		{
			RemoveChild(enemy)
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
		if (!enemyC->GetAlive())
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
		*/
	}

}


std::vector<std::shared_ptr<uth::GameObject>> EnemyManager::GetEnemies()
{
	return enemies;
}