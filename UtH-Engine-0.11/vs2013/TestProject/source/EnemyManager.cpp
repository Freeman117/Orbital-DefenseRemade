
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
	enemy->transform.SetScale(0.2f);
	AddChild(enemy);
	//A bit wonky at the moment, propably need to be reworked.
	Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
	float tempDistance = enemyC->GetDistance();
	float tempAngle = enemyC->GetAngle();
	enemy->transform.SetPosition(cosf(tempAngle)*tempDistance, sinf(tempAngle) * tempDistance);
	enemies.push_back(enemy);
}
void EnemyManager::UpdateEnemies(float deltaTime)
{
	float tempDistance = 0.0f;
	float tempAngle = 0.0f;
	for(int i = enemies.size() - 1; i > 0; i--)
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
		}
		if (!c.GetAlive())
		{
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

//void EnemyManager::DrawEnemies()
//{
//	for(size_t i = enemies.size(); i > 0; i--)
//	{
//		uth::GameObject& enemy = enemies[i-1];
//		enemy.Draw(uthEngine.GetWindow());
//	}
//}

std::vector<std::shared_ptr<uth::GameObject>> EnemyManager::GetEnemies()
{
	return enemies;
}