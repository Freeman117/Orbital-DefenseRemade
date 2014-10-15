#include "TurretManager.hpp"

TurretManager::TurretManager()
{
	orbit01Angle = 0.0f;
	orbit02Angle = 0.0f;
	turret01Sprite = new uth::Sprite("CannonTower.png");
	turret01Texture = uthRS.LoadTexture("CannonTower.png");
	bullet01Texture = uthRS.LoadTexture("cannonProjectile.png");
}
void TurretManager::CreateTurret(float type, float orb, float orbitPos)
{
	uth::GameObject* turret = new uth::GameObject();
	//turret->AddComponent(turret01Sprite);
	turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 1, 1, 5, 0, false, false));
	turret->transform.SetScale(0.30f);
	turret->AddComponent(new Turret(type, orb, orbitPos));
	turrets.push_back(turret);
}
void TurretManager::ShootBullet(float posX, float posY, float angle, float velocity, float damage, float range, float aoe)
{
	uth::GameObject* bullet = new uth::GameObject();
	//bullet->AddComponent(turret01Sprite);
	bullet->AddComponent(new uth::AnimatedSprite(bullet01Texture, 3, 4, 2, 5, 5, false, true));
	bullet->transform.SetScale(0.75f);
	bullet->transform.SetPosition(posX, posY);
	bullet->transform.SetRotation(pmath::radiansToDegrees(angle)+90);
	bullet->AddComponent(new Bullet(posX, posY, angle, velocity, damage, range, aoe));
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
	if (turrets.size() >= 1)
	{
		uth::GameObject* turret;
		Turret* turret_c;
		std::vector<uth::GameObject*> nearbyEnemies;

		for (int i = turrets.size() - 1; i >= 0; i--)
		{
			turret = turrets[i];
			turret_c = turret->GetComponent<Turret>("Turret");
			if (turret_c ->orbit == 1)
				turret->transform.SetPosition(cosf(orbit01Angle + turret_c->orbitPos*(pmath::pi / 3 / turret_c->orbit)) * 100 * turret_c->orbit, sinf(orbit01Angle + turret_c->orbitPos*(pmath::pi / 3 / turret_c->orbit)) * 100 * turret_c->orbit);
			else if (turret_c->orbit == 2)
				turret->transform.SetPosition(cosf(orbit02Angle + turret_c->orbitPos*(pmath::pi / 3 / turret_c->orbit)) * 100 * turret_c->orbit, sinf(orbit02Angle + turret_c->orbitPos*(pmath::pi / 3 / turret_c->orbit)) * 100 * turret_c->orbit);

			float turretPositionX = turret->transform.GetPosition().x;
			float turretPositionY = turret->transform.GetPosition().y;
			turret_c->cooldown += deltaTime;

			nearbyEnemies = EnemyWithinRange(enemyManager, turretPositionX, turretPositionY, turret_c->range);

			if (nearbyEnemies.size() > 0)
			{
				turret->transform.SetRotation(pmath::radiansToDegrees(atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX)) + 90);
				if (turret_c->cooldown >= turret_c->speed)
				{
					ShootBullet(turretPositionX, turretPositionY, atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX), 500, turret_c->damage, turret_c->range, turret_c->aoe);
					turret_c->cooldown = 0;
				}
			}
		}
	}
}
void TurretManager::DrawTurrets()
{
	uth::GameObject* turret;
	for (int i = turrets.size()-1; i >= 0; i--)
	{
		turret = turrets[i];
		turret->Draw(uthEngine.GetWindow());
	}
}
void TurretManager::UpdateBullets(float dt, EnemyManager* enemyManager)
{
	uth::GameObject* bullet;
	Bullet* bullet_c;
	Enemy* enemy_c;
	std::vector<uth::GameObject*> nearbyEnemies;

	for (int i = bullets.size() - 1; i >= 0; i--)
	{
		bullet = bullets[i];
		bullet_c = bullet->GetComponent<Bullet>("Bullet");
		bullet->transform.Move(cosf(bullet_c->rotation)*bullet_c->speed*dt, sinf(bullet_c->rotation)*bullet_c->speed*dt);

		nearbyEnemies = EnemyWithinRange(enemyManager, bullet->transform.GetPosition().x, bullet->transform.GetPosition().y, bullet_c->hitBox);

		if (nearbyEnemies.size() > 0)
		{
			enemy_c = nearbyEnemies[0]->GetComponent<Enemy>("Enemy");
			enemy_c->TakeHit(bullet_c->damage);
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
		else if (bullet_c->MaxRangeTravelled(dt))
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
}
void TurretManager::DrawBullets()
{
	uth::GameObject* bullet;
	for (int i = bullets.size()-1; i >= 0; i--)
	{
		bullet = bullets[i];
		bullet->Draw(uthEngine.GetWindow());
	}
}
//Returns us a vector of enemies that are within the given range, the closest one being [0]
std::vector<uth::GameObject*> TurretManager::EnemyWithinRange(EnemyManager* enemyManager, float positionX, float positionY, float radius)
{
	std::vector<uth::GameObject*> enemies;
	uth::GameObject* enemy;
	Enemy* enemy_c;
	float distanceToEnemy = 0;
	std::vector<pmath::Vec2> enemyDistances;
	for (int i = enemyManager->GetEnemies().size() - 1; i >= 0; i--)
	{
		enemy = enemyManager->GetEnemies()[i];
		enemy_c = enemy->GetComponent<Enemy>("Enemy");

		distanceToEnemy = sqrtf(pow((enemy->transform.GetPosition().x -positionX), 2) + pow((enemy->transform.GetPosition().y - positionY), 2))-enemy_c->HitBox;

		if (distanceToEnemy <= radius)
		{
			enemyDistances.push_back(pmath::Vec2(distanceToEnemy, i));
		}
	}
	std::sort(enemyDistances.begin(), enemyDistances.begin() + enemyDistances.size());
	for (int i = 0; i < enemyDistances.size(); i++)
	{
		enemies.push_back(enemyManager->GetEnemies()[enemyDistances[i].y]);
	}
	return enemies;
}