
#include "TurretManager.hpp"

TurretManager::TurretManager()
{
	orbit01Angle = 0.0f;
	orbit02Angle = 0.0f;
}
void TurretManager::CreateTurret(float type, float orb, float orbitPos)
{
	auto turret = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	turret->AddComponent(new uth::Sprite("CannonTower.png"));
	turret->transform.SetScale(0.30f);
	turret->AddComponent(new Turret(type, orb, orbitPos));
	turrets.push_back(turret);
}
void TurretManager::ShootBullet(float posX, float posY, float angle, float velocity, float damage, float range, float aoe)
{
	auto bullet = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	bullet->AddComponent(new uth::Sprite("CannonTower.png"));
	bullet->transform.SetScale(0.10f);
	bullet->AddComponent(new Bullet(posX, posY, angle, velocity, damage,range, aoe));
	bullet->transform.SetPosition(posX, posY);
	bullets.push_back(bullet);
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
		std::vector<std::shared_ptr<uth::GameObject>> nearbyEnemies;

		for(int i = turrets.size() - 1; i >= 0; i--)
		{
			auto& turret = *turrets[i];
			auto& c = *turret.GetComponent<Turret>();

			if (c.orbit == 1)
				turret.transform.SetPosition(cosf(orbit01Angle + c.orbitPos*(pmath::pi / 3)) * 100 * c.orbit, sinf(orbit01Angle + c.orbitPos*(pmath::pi / 3)) * 100 * c.orbit);
			else if (c.orbit == 2)
				turret.transform.SetPosition(cosf(orbit02Angle + c.orbitPos*(pmath::pi / 3)) * 100 * c.orbit, sinf(orbit02Angle + c.orbitPos*(pmath::pi / 3)) * 100 * c.orbit);

			float turretPositionX = turret.transform.GetPosition().x;
			float turretPositionY = turret.transform.GetPosition().y;

			nearbyEnemies = EnemyWithinRange(enemyManager, turretPositionX, turretPositionY, c.range);

			if (nearbyEnemies.size() > 0)
			{
				ShootBullet(turretPositionX, turretPositionY, atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX), 400, c.damage, c.range, c.aoe);
				turret.transform.SetRotation(pmath::radiansToDegrees(atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX)) + 90);
			}

			/*
			//for (int j = enemyManager->GetEnemies().size() - 1; j >= 0; j--)
			//{
			//	enemy = enemyManager->GetEnemies()[j];
			//	enemy_c = enemy->GetComponent<Enemy>("Enemy");

			//	enemyPositionX = enemy->transform.GetPosition().x;
			//	enemyPositionY = enemy->transform.GetPosition().y;

			//	distanceToEnemy = sqrtf(pow((enemyPositionX - turretPositionX), 2) + pow((enemyPositionY - turretPositionY), 2));

			//	if (distanceToEnemy < turret_c->range && distanceToEnemy < nearestEnemy)
			//	{
			//		target_i = j;
			//		nearestEnemy = distanceToEnemy;

			//		std::cout << "TARGET " << target_i << std::endl;
			//		std::cout << "DISTANCE " << nearestEnemy << std::endl;
			//	}
			//}
			//if (target_i != -1)
			//{
			//	enemy = enemyManager->GetEnemies()[target_i];
			//	enemy_c = enemy->GetComponent<Enemy>("Enemy");
			//	turretAngle = pmath::radiansToDegrees(atan2f(enemy->transform.GetPosition().y - turretPositionY, enemy->transform.GetPosition().x - turretPositionX)) + 90;
			//	turret->transform.SetRotation(turretAngle);
			//	ShootBullet(turretPositionX, turretPositionY, pmath::degreesToRadians(turretAngle-90), 400, 2, turret_c->range, 0);
			//}
			*/
		}
	}
}

//void TurretManager::DrawTurrets()
//{
//	uth::GameObject* turret;
//	for(size_t i = turrets.size()-1; i >= 0; i--)
//	{
//		turrets[i]->Draw(uthEngine.GetWindow());
//	}
//}

void TurretManager::UpdateBullets(float dt, EnemyManager* enemyManager)
{
	Enemy* enemy_c;

	std::vector<std::shared_ptr<uth::GameObject>> nearbyEnemies;

	for(int i = bullets.size() - 1; i >= 0; i--)
	{
		auto& bullet = *bullets[i];
		auto& c = *bullet.GetComponent<Bullet>();
		bullet.transform.Move(cosf(c.rotation)*c.speed*dt, sinf(c.rotation)*c.speed*dt);

		nearbyEnemies = EnemyWithinRange(enemyManager, bullet.transform.GetPosition().x, bullet.transform.GetPosition().y, c.hitBox);

		if (nearbyEnemies.size() > 0)
		{
			enemy_c = nearbyEnemies[0]->GetComponent<Enemy>();
			enemy_c->TakeHit(c.damage);
			bullets.erase(bullets.begin() + i);
		}
		else if (c.MaxRangeTravelled(dt))
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

//void TurretManager::DrawBullets()
//{
//	for(size_t i = bullets.size()-1; i >= 0; i--)
//	{
//		bullets[i]->Draw(uthEngine.GetWindow());
//	}
//}

//Returns us a vector of enemies that are within the given range, the closest one being [0]
std::vector<std::shared_ptr<uth::GameObject>> TurretManager::EnemyWithinRange(EnemyManager* enemyManager, float positionX, float positionY, float radius)
{
	std::vector<std::shared_ptr<uth::GameObject>> enemies;
	std::vector<pmath::Vec2> enemyDistances;
	float distanceToEnemy = 0;

	for(size_t i = enemyManager->GetEnemies().size() - 1; i >= 0; i--)
	{
		auto& enemy = *enemyManager->GetEnemies()[i];
		auto& c = *enemy.GetComponent<Enemy>();

		distanceToEnemy = sqrtf(pow((enemy.transform.GetPosition().x -positionX), 2) + pow((enemy.transform.GetPosition().y - positionY), 2)) - c.HitBox;

		if (distanceToEnemy <= radius)
		{
			enemyDistances.push_back(pmath::Vec2(distanceToEnemy, i));
		}
	}

	std::sort(enemyDistances.begin(), enemyDistances.begin() + enemyDistances.size());
	for(size_t i = 0; i < enemyDistances.size(); i++)
	{
		enemies.push_back(enemyManager->GetEnemies()[enemyDistances[i].y]);
	}

	return enemies;
}