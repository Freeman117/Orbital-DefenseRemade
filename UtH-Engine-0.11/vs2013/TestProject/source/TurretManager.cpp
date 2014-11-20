
#include "TurretManager.hpp"

TurretManager::TurretManager()
{
	orbit02Angle = 0.0f;
	turret01Sprite = new uth::Sprite("CannonTower.png");
	turret01Texture = uthRS.LoadTexture("TurretDesigns2.png");
	bullet01Texture = uthRS.LoadTexture("cannonProjectile.png");
	node01Texture = uthRS.LoadTexture("buttonTest.png");
	CreateNodes();
}
void TurretManager::CreateTurret(int type, int orb, int orbitPos)
{
	auto turret = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	turret->transform.SetScale(0.30f);
	if (type == 1)
	{
		turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 5, false, false));
		turret->AddComponent(new TurretCannon(orb,orbitPos));
	}
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

	UpdateNodes();
	
	for (int i = turrets.size() - 1; i >= 0; i--)
	{
		auto& turret = *turrets[i];
		auto& c = *turret.GetComponent<Turret>();

		if (c.GetOrbit() == 1)
			turret.transform.SetPosition(cosf(orbit01Angle + c.GetOrbitPos()*(pmath::pi / 3 / c.GetOrbit())) * 115 * c.GetOrbit(), sinf(orbit01Angle + c.GetOrbitPos()*(pmath::pi / 3 / c.GetOrbit())) * 115 * c.GetOrbit());
		else if (c.GetOrbit() == 2)
			turret.transform.SetPosition(cosf(orbit02Angle + c.GetOrbitPos()*(pmath::pi / 3 / c.GetOrbit())) * 115 * c.GetOrbit(), sinf(orbit02Angle + c.GetOrbitPos()*(pmath::pi / 3 / c.GetOrbit())) * 115 * c.GetOrbit());

		float turretPositionX = turret.transform.GetPosition().x;
		float turretPositionY = turret.transform.GetPosition().y;
		c.SetCooldown(c.GetCooldown() + deltaTime);
		nearbyEnemies = EnemyWithinRange(enemyManager, turretPositionX, turretPositionY, c.GetRange());

		if (nearbyEnemies.size() > 0)
		{
			turret.transform.SetRotation(pmath::radiansToDegrees(atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX)));
			if (c.CanShoot())
			{
				ShootBullet(turretPositionX, turretPositionY, atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX), c.GetBulletSpeed(), c.GetDamage(), c.GetRange(), c.GetAoe());
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
	std::vector<std::shared_ptr<uth::GameObject>> enemiesWithinAoE;

	for(int i = bullets.size() - 1; i >= 0; i--)
	{
		auto& bullet = *bullets[i];
		auto& c = *bullet.GetComponent<Bullet>();
		bullet.transform.Move(cosf(c.rotation)*c.speed*dt, sinf(c.rotation)*c.speed*dt);

		nearbyEnemies = EnemyWithinRange(enemyManager, bullet.transform.GetPosition().x, bullet.transform.GetPosition().y, c.hitBox);

		if (nearbyEnemies.size() > 0)
		{
			if (c.explosionradius > 0)
			{
				enemiesWithinAoE = EnemyWithinRange(enemyManager, nearbyEnemies[0]->transform.GetPosition().x, nearbyEnemies[0]->transform.GetPosition().y, c.explosionradius);
				for (int j = enemiesWithinAoE.size() - 1; j >= 0; j--)
				{
					enemy_c = enemiesWithinAoE[j]->GetComponent<Enemy>();
					enemy_c->TakeHit(c.damage);
				}
			}
			else
			{
				enemy_c = nearbyEnemies[0]->GetComponent<Enemy>();
				enemy_c->TakeHit(c.damage);
			}
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
void TurretManager::CreateNodes()
{
	for (int i = 0; i < 6; i++)
	{
		auto node = std::shared_ptr<Node>(new Node(1, i, orbit01Angle, node01Texture));
		nodes.push_back(node);
		AddChild(node);
	}
	for (int i = 0; i < 12; i++)
	{
		auto node = std::shared_ptr<Node>(new Node(2, i, orbit02Angle, node01Texture));
		nodes.push_back(node);
		AddChild(node);
	}
}
void TurretManager::UpdateNodes()
{
	for (int i = nodes.size() - 1; i >= 0; i--)
	{
		auto& node = *nodes[i];
		node.MoveNode(orbit01Angle, orbit02Angle);
		if (node.GetTrue())
		{
			CreateTurret(1, node.GetOrbit(), node.GetOrbitPos());
			//RemoveChild(node);
			//nodes.erase(nodes.begin() + i);
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