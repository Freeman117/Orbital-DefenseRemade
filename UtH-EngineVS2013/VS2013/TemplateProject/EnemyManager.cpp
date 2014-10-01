#include "EnemyManager.hpp"
#include <UtH/Engine/UtHEngine.h>


EnemyManager::EnemyManager()
{

}
void EnemyManager::SpawnEnemy(float health_,float armor_, float speed_, float angle_)
{
	uth::GameObject* enemy = new uth::GameObject();
	enemy->AddComponent(new Enemy(health_, armor_, speed_, pmath::degreesToRadians(angle_)));
	enemy->AddComponent(new uth::Sprite("CannonTower.png"));
	enemy->transform.SetScale(0.5f);

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
	for (int i = enemies.size(); i > 0; i--)
	{
		uth::GameObject* enemy = enemies[i-1];
		Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
		enemyC->SetDistance(enemyC->GetDistance() - enemyC->GetSpeed()*deltaTime);
		tempDistance = enemyC->GetDistance();
		tempAngle = enemyC->GetAngle();
		enemy->transform.SetPosition(cosf(tempAngle )*tempDistance , sinf(tempAngle) * tempDistance);
		enemy->transform.SetRotation(pmath::radiansToDegrees(-tempAngle)+90);

		if (enemyC->GetDistance() <= 0)
		{
			//Does not free any memory at the moment, needs to be fixed!
			enemies.erase(enemies.begin() + i-1);
		}

	}

}
void EnemyManager::DrawEnemies()
{
	for (int i = enemies.size(); i > 0; i--)
	{
		uth::GameObject* enemy = enemies[i-1];
		enemy->Draw(uthEngine.GetWindow());
	}
}