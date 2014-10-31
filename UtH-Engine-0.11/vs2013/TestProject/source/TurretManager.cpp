
#include "TurretManager.hpp"

TurretManager::TurretManager()
{
	orbit01Angle = 0.0f;
	orbit02Angle = 0.0f;
	turret01Sprite = new uth::Sprite("CannonTower.png");
	turret01Texture = uthRS.LoadTexture("TurretDesigns2.png");
	bullet01Texture = uthRS.LoadTexture("cannonProjectile.png");
}
void TurretManager::CreateTurret(int type, int orb, int orbitPos)
{
	auto turret = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 5, false, false));
	turret->transform.SetScale(0.30f);
	turret->AddComponent(new Turret(type, orb, orbitPos));
	AddChild(turret);
	turrets.push_back(turret);
}
void TurretManager::ShootBullet(float posX, float posY, float angle, float velocity, float damage, float range, float aoe)
{
	auto bullet = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	bullet->AddComponent(new uth::AnimatedSprite(bullet01Texture, 1, 4, 2, 6, 5, false, true));
	bullet->transform.SetScale(0.75f);
	bullet->transform.SetPosition(posX, posY);
	bullet->transform.SetRotation(pmath::radiansToDegrees(angle) + 90);
	bullet->AddComponent(new Bullet(posX, posY, angle, velocity, damage,range, aoe));
	AddChild(bullet);
	bullets.push_back(bullet);
}
void TurretManager::RotateTurrets(int orbit,float angle)
{
	if (orbit == 1)
		orbit01Angle += angle;
	else if (orbit == 2)
		orbit02Angle += angle;

}
void TurretManager::RotationChange(float angle)
{
	currentAngle = angle;
}
void TurretManager::RotationChange(float angle, int orbit)
{
	float rotation = -(currentAngle -= angle);
	RotateTurrets(orbit, rotation);
	currentAngle = angle;
}
void TurretManager::UpdateTurrets(float deltaTime, EnemyManager* enemyManager)
{
		std::vector<std::shared_ptr<uth::GameObject>> nearbyEnemies;

		for (int i = turrets.size() - 1; i >= 0; i--)
		{
			auto& turret = *turrets[i];
			auto& c = *turret.GetComponent<Turret>();

			if (c.orbit == 1)
				turret.transform.SetPosition(cosf(orbit01Angle + c.orbitPos*(pmath::pi / 3 / c.orbit)) * 115 * c.orbit, sinf(orbit01Angle + c.orbitPos*(pmath::pi / 3 / c.orbit)) * 115 * c.orbit);
			else if (c.orbit == 2)
				turret.transform.SetPosition(cosf(orbit02Angle + c.orbitPos*(pmath::pi / 3 / c.orbit)) * 115 * c.orbit, sinf(orbit02Angle + c.orbitPos*(pmath::pi / 3 / c.orbit)) * 115 * c.orbit);

			float turretPositionX = turret.transform.GetPosition().x;
			float turretPositionY = turret.transform.GetPosition().y;
			c.cooldown += deltaTime;
			nearbyEnemies = EnemyWithinRange(enemyManager, turretPositionX, turretPositionY, c.range);

			if (nearbyEnemies.size() > 0)
			{
				turret.transform.SetRotation(pmath::radiansToDegrees(atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX)));
				if (c.cooldown >= c.speed)
				{
					ShootBullet(turretPositionX, turretPositionY, atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX), 400, c.damage, c.range, c.aoe);
					c.cooldown = 0;
				}
			}
		}
}
void TurretManager::UpgradeTurret(float &money)
{
	for (int i = turrets.size() - 1; i >= 0; i--)
	{
		auto& turret = *turrets[i];
		auto& c = *turret.GetComponent<Turret>();

		c.Upgrade(money);
		std::cout << money << std::endl;
	}
}

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
			RemoveChild(bullets[i]);
			bullets.erase(bullets.begin() + i);
		}
		else if (c.MaxRangeTravelled(dt))
		{
			RemoveChild(bullets[i]);
			bullets.erase(bullets.begin() + i);
		}
	}
}

//Returns us a vector of enemies that are within the given range, the closest one being [0]
std::vector<std::shared_ptr<uth::GameObject>> TurretManager::EnemyWithinRange(EnemyManager* enemyManager, float positionX, float positionY, float radius)
{
		std::vector<std::shared_ptr<uth::GameObject>> enemies;
		std::vector<pmath::Vec2> enemyDistances;
		float distanceToEnemy = 0;

		for (int i = enemyManager->GetEnemies().size() - 1; i >= 0; i--)
		{
			//This returns an invalid value, repair necessary
			auto& enemy = *enemyManager->GetEnemies()[i];
			auto& c = *enemy.GetComponent<Enemy>();

			distanceToEnemy = sqrtf(pow((enemy.transform.GetPosition().x - positionX), 2) + pow((enemy.transform.GetPosition().y - positionY), 2)) - c.HitBox;

			if (distanceToEnemy <= radius)
			{
				//enemyDistances.push_back(pmath::Vec2(distanceToEnemy, i));
				enemyDistances.emplace_back(pmath::Vec2(distanceToEnemy, i));
			}
		}

		std::sort(enemyDistances.begin(), enemyDistances.begin() + enemyDistances.size());
		for (size_t i = 0; i < enemyDistances.size(); i++)
		{
			//enemies.push_back(enemyManager->GetEnemies()[enemyDistances[i].y]);
			enemies.emplace_back(enemyManager->GetEnemies()[enemyDistances[i].y]);
		}

		return enemies;
}