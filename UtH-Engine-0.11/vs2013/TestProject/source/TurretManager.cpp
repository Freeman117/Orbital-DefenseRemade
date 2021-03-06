
#include "TurretManager.hpp"

TurretManager::TurretManager()
{
	//orbit01Angle = 0.0f;
	orbit02Angle = 0.0f;
	turret01Sprite = new uth::Sprite("CannonTower.png");
	turret01Texture = uthRS.LoadTexture("pixelTurrets.png");
	bulletTexture = uthRS.LoadTexture("projectileSheet.png");
	node01Texture = uthRS.LoadTexture("buttonTest.png");
	towerButtonTexture = uthRS.LoadTexture("particle.png");
	disruptorProjectile = uthRS.LoadTexture("Projectile_Disruptor.png");
	
	RocketButton = uthRS.LoadTexture("RocketButton.png");
	RailgunButton = uthRS.LoadTexture("RailgunButton.png");
	DisruptorButton = uthRS.LoadTexture("disruptorButton.png");
	CannonButton = uthRS.LoadTexture("CannonButton.png");
	BeamButton = uthRS.LoadTexture("BeamButton.png");
	GatlingLaserButton = uthRS.LoadTexture("GatlingLaserButton.png");
	CancelButton = uthRS.LoadTexture("CancelButton.png");

	CreateNodes();

	towers[0] = new ns::Button(uthEngine.GetWindow(), CannonButton);
	towers[1] = new ns::Button(uthEngine.GetWindow(), GatlingLaserButton);
	towers[2] = new ns::Button(uthEngine.GetWindow(), BeamButton);
	towers[3] = new ns::Button(uthEngine.GetWindow(), RocketButton);
	towers[4] = new ns::Button(uthEngine.GetWindow(), DisruptorButton);
	towers[5] = new ns::Button(uthEngine.GetWindow(), RailgunButton);
	
	for (size_t i = 0; i < 6; i++)
	{
		towers[i]->transform.SetScale(0.6f);
		towerButtons.emplace_back(towers[i]);
		AddChild(towerButtons.back());
		towers[i]->SetActive(false);
		towers[i]->AddTag("Tower");
	}

	cancel = new ns::Button(uthEngine.GetWindow(), CancelButton);
	AddChild(cancel);
	cancel->SetActive(false);
	cancel->AddTag("Cancel");
	cancel->transform.SetScale(0.6f);

	cancel->setCallBack([&]()
	{
		poisto();
	});

	UI = false;
}
void TurretManager::CreateTurret(int type, int orb, int orbitPos)
{
	auto turret = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	turret->transform.SetScale(2.5f);
	if (type == 1)
	{
		turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 0, false, false));
		turret->AddComponent(new TurretCannon(orb,orbitPos));
	}
	else if (type == 2)
	{
		turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 3, false, false));
		turret->AddComponent(new TurretLazer(orb, orbitPos));
	}
	else if (type == 3)
	{
		turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 5, false, false));
		turret->AddComponent(new TurretBeam(orb, orbitPos));
		turret->transform.SetScale(2.0f);
	}
	else if (type == 4)
	{
		turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 4, false, false));
		turret->AddComponent(new TurretMissile(orb, orbitPos));
	}
	else if (type == 5)
	{
		turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 2, false, false));
		turret->AddComponent(new TurretDisruptor(orb, orbitPos));
		turret->transform.SetScale(1.85f);
	}
	else if (type == 6)
	{
		turret->AddComponent(new uth::AnimatedSprite(turret01Texture, 1, 4, 4, 5, 1, false, false));
		turret->AddComponent(new TurretMrk(orb, orbitPos));
		turret->transform.SetScale(2.70f);
	}
	AddChild(turret);
	turrets.push_back(turret);

	//AddTurretButtons();
}
void TurretManager::ShootBullet(float posX, float posY, float angle, float velocity, float damage, float range, float aoe, bool penetrate, float slowAmount,float crit,float armorPenetration,uth::Texture* texture)
{
	if (rand->GetFloat() > 0.8f)
		damage * crit;
	auto bullet = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	bullet->AddComponent(new uth::AnimatedSprite(texture, 1, 4, 2, 16.0f, 5, false, false));
	bullet->transform.SetScale(0.75f);
	bullet->transform.SetPosition(posX, posY);
	bullet->transform.SetRotation(pmath::radiansToDegrees(angle) + 90);
	bullet->AddComponent(new Bullet(posX, posY, angle, velocity, damage,range, aoe,penetrate,slowAmount,crit,armorPenetration));
	AddChild(bullet);
	bullets.push_back(bullet);
}
void TurretManager::ShootBullet(float posX, float posY, float angle, Turret &t)
{
	float damage = t.GetDamage();
	if (rand->GetFloat() > 0.8f)
		damage *= t.GetCrit();
	auto bullet = std::shared_ptr<uth::GameObject>(new uth::GameObject());
	bullet->AddComponent(new uth::AnimatedSprite(bulletTexture, t.GetFrameAmount(), 6, 8, 6.0f, t.GetStartFrame(), false, true));
	bullet->transform.SetScale(1.5f);
	bullet->transform.SetPosition(posX, posY);
	bullet->transform.SetRotation(pmath::radiansToDegrees(angle));
	bullet->AddComponent(new Bullet(posX, posY, angle, t.GetBulletSpeed(),damage, t.GetRange(), t.GetAoe(), t.GetPenetrate(), t.GetSlowAmount(),t.GetCrit(), t.GetPenetrate()));
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
				//ShootBullet(turretPositionX, turretPositionY, atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX), c.GetBulletSpeed(), c.GetDamage(), c.GetRange(), c.GetAoe(),c.GetPenetrate(),c.GetSlowAmount(),c.GetCrit(),c.GetPenetrate(),c.GetTexture());
				ShootBullet(turretPositionX, turretPositionY, atan2f(nearbyEnemies[0]->transform.GetPosition().y - turretPositionY, nearbyEnemies[0]->transform.GetPosition().x - turretPositionX), c);
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
					enemy_c->TakeHit(c.damage,c.armorPenetration);
					enemy_c->SetMovementMod(c.slowAmount, 1);
				}
			}
			else
			{
				enemy_c = nearbyEnemies[0]->GetComponent<Enemy>();
				enemy_c->TakeHit(c.damage, c.armorPenetration);
			}
			if (!c.penetrate)
			{
				RemoveChild(bullets[i]);
				bullets.erase(bullets.begin() + i);
			}
		}
		else if (c.MaxRangeTravelled(dt))
		{
			if (c.explosionradius > 0)
			{
				enemiesWithinAoE = EnemyWithinRange(enemyManager, bullet.transform.GetPosition().x, bullet.transform.GetPosition().y, c.explosionradius);
				for (int j = enemiesWithinAoE.size() - 1; j >= 0; j--)
				{
					enemy_c = enemiesWithinAoE[j]->GetComponent<Enemy>();
					enemy_c->TakeHit(c.damage, c.armorPenetration);
					enemy_c->SetMovementMod(c.slowAmount, 1);
				}
			}
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
		nodes.emplace_back(node);
		AddChild(node);
		node->AddTag("Node");
	}
	for (int i = 0; i < 12; i++)
	{
		auto node = std::shared_ptr<Node>(new Node(2, i, orbit02Angle, node01Texture));
		nodes.emplace_back(node);
		AddChild(node);
		node->AddTag("Node2");
	}
}
void TurretManager::UpdateNodes()
{
	for (int i = nodes.size() - 1; i >= 0; i--)
	{
		auto node = nodes[i];
		node->MoveNode(orbit01Angle, orbit02Angle);
		if (node->GetTrue())
		{
			nodes[i]->AddTag("Construct");
			AddTurretButtons();
			
			//if (node->GetOrbit() == 1)
				//CreateTurret(node->GetOrbitPos() + 1, node->GetOrbit(), node->GetOrbitPos());
			//else
				//CreateTurret(1, node->GetOrbit(), node->GetOrbitPos());

			//RemoveChild(node);
			//nodes.erase(nodes.begin() + i); Not necessary anymore since we can just hide the nodes
			UI = true;
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

void TurretManager::AddTurretButtons()
{
	if (UI == false)
	{
		towers[0]->transform.SetPosition(pmath::Vec2f(-524.f, -100.f));
		towers[1]->transform.SetPosition(pmath::Vec2f(-524.f, -50.f));
		towers[2]->transform.SetPosition(pmath::Vec2f(-524.f, 0.f));
		towers[3]->transform.SetPosition(pmath::Vec2f(-524.f, 50.f));
		towers[4]->transform.SetPosition(pmath::Vec2f(-524.f, 100.f));
		towers[5]->transform.SetPosition(pmath::Vec2f(-524.f, 150.f));

		for (auto t : towers)
			t->SetActive(true);

		//AddChild(cancel);
		cancel->SetActive(true);
		//cancelButton.emplace_back(cancel);
		cancel->transform.SetPosition(-524.f, 200.f);

		SearchNodes();

	}
}
void TurretManager::SearchNodes()
{
	for (int i = 0; i < nodes.size() - 1; i++)
	{
		auto& node = nodes[i];
		if (node->HasTag("Construct"))
		{
			towers[0]->setCallBack([&]()
			{
				CreateTurret(1, node->GetOrbit(), node->GetOrbitPos());
				poisto();
				node->RemoveTag("Construct");
				node->SetActive(false);
			});
			towers[1]->setCallBack([&]()
			{
				CreateTurret(2, node->GetOrbit(), node->GetOrbitPos());
				poisto();
				node->RemoveTag("Construct");
				node->SetActive(false);
			});
			towers[2]->setCallBack([&]()
			{
				CreateTurret(3, node->GetOrbit(), node->GetOrbitPos());
				poisto();
				node->RemoveTag("Construct");
				node->SetActive(false);
			});
			towers[3]->setCallBack([&]()
			{
				CreateTurret(4, node->GetOrbit(), node->GetOrbitPos());
				poisto();
				node->RemoveTag("Construct");
				node->SetActive(false);
			});
			towers[4]->setCallBack([&]()
			{
				CreateTurret(5, node->GetOrbit(), node->GetOrbitPos());
				poisto();
				node->RemoveTag("Construct");
				node->SetActive(false);
			});
			towers[5]->setCallBack([&]()
			{
				CreateTurret(6, node->GetOrbit(), node->GetOrbitPos());
				poisto();
				node->RemoveTag("Construct");
				node->SetActive(false);
			});

		}
	}
}

void TurretManager::RemoveTurretButtons()
{
	if (towerButtons.size() > 0)
	{
		for (int i = towerButtons.size()-1; i >= 0; i--)
		{
			towers[i]->SetActive(false);
		}
		cancel->SetActive(false);
		UI = false;
	}
}

void TurretManager::poisto()
{
	RemoveTurretButtons();
}