#include "EnemyManager.hpp"
#include <UtH/Engine/UtHEngine.h>


EnemyManager::EnemyManager()
{

}
void EnemyManager::SpawnEnemy()
{
	//Only spawns one kind of enemies, the method needs to be expanded to fit multiple needs.
	uth::GameObject* enemy = new uth::GameObject();
	enemy->AddComponent(new Enemy(5, 5, 2, 1));
	enemy->AddComponent(new uth::Sprite("CannonTower.png"));
	enemy->transform.SetScale(0.5f);

	//A bit wonky at the moment, propably need to be reworked.
	Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
	float tempDistance = enemyC->Distance();
	float tempAngle = enemyC->GetAngle();
	enemy->transform.SetPosition(cosf(tempAngle)*tempDistance, sinf(tempAngle) * tempDistance);
	enemies.push_back(enemy);
}
void EnemyManager::UpdateEnemies()
{
	float tempDistance = 0.0f;
	float tempAngle = 0.0f;
	for (int i = 0; i < enemies.size(); i++)
	{
		
		uth::GameObject* enemy = enemies[i];
		Enemy* enemyC = enemy->GetComponent<Enemy>("Enemy");
		tempDistance = enemyC->Distance();
		tempAngle = enemyC->GetAngle();
		enemy->transform.SetPosition(cosf(tempAngle )*tempDistance , sinf(tempAngle) * tempDistance);
		enemy->transform.SetRotation(pmath::radiansToDegrees(tempAngle)-270); //Does not return the right angle, needs to be fixed.
	}

}
void EnemyManager::DrawEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		uth::GameObject* enemy = enemies[i];
		enemy->Draw(uthEngine.GetWindow());
	}
}