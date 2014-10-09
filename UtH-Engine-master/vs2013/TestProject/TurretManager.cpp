#include "TurretManager.hpp"
#include <UtH/Engine/Engine.hpp>

TurretManager::TurretManager()
{
	orbit01Angle = 0.0f;
	orbit02Angle = 0.0f;
}
void TurretManager::CreateTurret(float type, float orb, float orbitPos)
{
	uth::GameObject* turret = new uth::GameObject();
	turret->AddComponent(new uth::Sprite("CannonTower.png"));
	turret->transform.SetScale(0.30f);
	turret->AddComponent(new Turret(type, orb, orbitPos));
	turrets.push_back(turret);
}
void TurretManager::RotateTurrets(int orbit,float angle)
{
	if (orbit == 1)
		orbit01Angle += angle;
	else if (orbit == 2)
		orbit02Angle += angle;

}
void TurretManager::UpdateTurrets(float deltaTime, EnemyManager* enemyManager)
{
	if (turrets.size() >= 1)
	{
		uth::GameObject* turret;
		Turret* turret_c;
		uth::GameObject* enemy;
		Enemy* enemy_c;

		int target_i = -1;

		for (int i = turrets.size() - 1; i >= 0; i--)
		{
			target_i = -1;
			turret = turrets[i];
			turret_c = turret->GetComponent<Turret>("Turret");
			if (turret_c ->orbit == 1)
				turret->transform.SetPosition(cosf(orbit01Angle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit, sinf(orbit01Angle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit);
			else if (turret_c->orbit == 2)
				turret->transform.SetPosition(cosf(orbit02Angle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit, sinf(orbit02Angle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit);

			float enemyPositionX = 0.0f;
			float enemyPositionY = 0.0f;
			float turretPositionX = turret->transform.GetPosition().x;
			float turretPositionY = turret->transform.GetPosition().y;
			float distanceToEnemy = 0.0f;
			float nearestEnemy = 1000.0f;

			for (int j = enemyManager->GetEnemies().size() - 1; j >= 0; j--)
			{
				enemy = enemyManager->GetEnemies()[j];
				enemy_c = enemy->GetComponent<Enemy>("Enemy");

				enemyPositionX = enemy->transform.GetPosition().x;
				enemyPositionY = enemy->transform.GetPosition().y;

				distanceToEnemy = sqrtf(pow((enemyPositionX - turretPositionX), 2) + pow((enemyPositionY - turretPositionY), 2));

				if (distanceToEnemy < turret_c->range && distanceToEnemy < nearestEnemy)
				{
					target_i = j;
					nearestEnemy = distanceToEnemy;

					std::cout << "TARGET " << target_i << std::endl;
					std::cout << "DISTANCE " << nearestEnemy << std::endl;
				}
			}
			if (target_i != -1)
			{
				enemy = enemyManager->GetEnemies()[target_i];
				enemy_c = enemy->GetComponent<Enemy>("Enemy");
				turret->transform.SetRotation(pmath::radiansToDegrees(atan2f(enemy->transform.GetPosition().y - turretPositionY, enemy->transform.GetPosition().x - turretPositionX)) + 90);
				enemy_c->TakeHit(turret_c->damage);
			}
		}
	}
}
void TurretManager::DrawTurrets()
{
	uth::GameObject* turret;
	for (int i = turrets.size() - 1; i >= 0; i--)
	{
		turret = turrets[i];
		turret->Draw(uthEngine.GetWindow());
	}
}