#include "EnemyManager.hpp"
#include <UtH/UtHEngine.hpp>


EnemyManager::EnemyManager()
{
	enemytexture = uthRS.LoadTexture("asteroidMockup.png");
}
void EnemyManager::SpawnEnemy(float health_,float armor_, float speed_, float angle_)
{


	uth::GameObject* enemy = new uth::GameObject();
	enemy->AddComponent(new Enemy(health_, armor_, speed_, pmath::degreesToRadians(angle_)));
	enemy->AddComponent(new uth::AnimatedSprite(enemytexture,8,4,2,5,0,false,true));
	enemy->transform.SetScale(0.2f);

	//A bit wonky at the moment, propably need to be reworked.
	Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
	float tempDistance = enemyC->GetDistance();
	float tempAngle = enemyC->GetAngle();
	enemy->transform.SetPosition(cosf(tempAngle)*tempDistance, sinf(tempAngle) * tempDistance);
	enemies.push_back(enemy);
}
void EnemyManager::UpdateEnemies(float deltaTime, int &health)
{
	float tempDistance = 0.0f;
	float tempAngle = 0.0f;
	for (int i = enemies.size()-1; i >= 0; i--)
	{
		uth::GameObject* enemy = enemies[i];
		Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
		enemyC->SetDistance(enemyC->GetDistance() - enemyC->GetSpeed()*deltaTime);

		enemy->Update(deltaTime);

		tempDistance = enemyC->GetDistance();
		tempAngle = enemyC->GetAngle();
		enemy->transform.SetPosition(cosf(tempAngle )*tempDistance , sinf(tempAngle) * tempDistance);
		enemy->transform.SetRotation(pmath::radiansToDegrees(-tempAngle)+90);


		if (enemyC->GetDistance() <= 20)
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			health -= 1;
		}
		if (!enemyC->GetAlive())
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}

	}

}
void EnemyManager::DrawEnemies()
{
	for (int i = enemies.size()-1; i >= 0; i--)
	{
		uth::GameObject* enemy = enemies[i];
		enemy->Draw(uthEngine.GetWindow());
	}
}

std::vector<uth::GameObject*> EnemyManager::GetEnemies()
{
	return enemies;
}