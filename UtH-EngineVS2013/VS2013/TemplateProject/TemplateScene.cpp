#include "TemplateScene.hpp"
#include <UtH/Engine/UtHEngine.h>

using namespace uth;

bool TemplateScene::Init()
{
	shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	shader.Use();
	uthEngine.GetWindow().SetShader(&shader);

	testi = 0;
	turretAngle = 0;
	moonbase = new GameObject();
	moonbase->AddComponent(new Sprite("moonBaseMockup2.png"));
	moonbase->transform.SetScale(0.5f);

	background = new GameObject();
	background->AddComponent(new Sprite("stars2.png"));
	background->transform.SetScale(0.7f);

	
	
	return true;
}

bool TemplateScene::Update(float dt)
{
	enemyManager.UpdateEnemies(dt);
	if (uthInput.Keyboard.IsKeyDown(Keyboard::D))
	{
		if (turrets.size() < 1)
		{
			return true;
		}
		else
			if (uthInput.Keyboard.IsKeyPressed(Keyboard::D))
			{
			turretAngle += 2 * dt;
			}

		if (uthInput.Keyboard.IsKeyDown(Keyboard::A))
		{
			if (turrets.size() < 1)
			{
				return true;
			}
			else
				turretAngle -= 2 * dt;
		}
		if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
		{

			GameObject* turret = new uth::GameObject();
			turret->AddComponent(new uth::Sprite("CannonTower.png"));
			turret->transform.SetScale(0.30f);
			turret->AddComponent(new Turret(1, 1, testi));
			turrets.push_back(turret);

			testi++;
		}
		if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key3))
		{
			enemyManager.SpawnEnemy(150, 3, 50, 60);
			enemyManager.SpawnEnemy(250, 3, 60, 70);
			enemyManager.SpawnEnemy(150, 3, 50, 80);
			enemyManager.SpawnEnemy(250, 3, 60, 90);
			enemyManager.SpawnEnemy(150, 3, 50, 100);
			enemyManager.SpawnEnemy(250, 3, 60, 110);
		}
		if (uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
		{
			//uthInput.Mouse.Position();
		}

		if (turrets.size() >= 1)
		{
			uth::GameObject* turret;
			Turret* turret_c;
			GameObject* enemy;
			Enemy* enemy_c;

			int target_i = -1;

			for (int i = turrets.size() - 1; i >= 0; i--)
			{
				target_i = -1;
				turret = turrets[i];
				turret_c = turret->GetComponent<Turret>("Turret");
				turret->transform.SetPosition(cosf(turretAngle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit, sinf(turretAngle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit);

				float enemyPositionX = 0.0f;
				float enemyPositionY = 0.0f;
				float turretPositionX = turret->transform.GetPosition().x;
				float turretPositionY = turret->transform.GetPosition().y;
				float distanceToEnemy = 0.0f;
				float nearestEnemy = 1000.0f;

				for (int j = enemyManager.GetEnemies().size() - 1; j >= 0; j--)
				{
					enemy = enemyManager.GetEnemies()[j];
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
					enemy = enemyManager.GetEnemies()[target_i];
					enemy_c = enemy->GetComponent<Enemy>("Enemy");
					turret->transform.SetRotation(pmath::radiansToDegrees(-atan2f(enemy->transform.GetPosition().y - turretPositionY, enemy->transform.GetPosition().x - turretPositionX)) - 90);
					enemy_c->TakeHit(turret_c->damage);
				}
			}
		}

		return true;
	}
}
bool TemplateScene::Draw()
{

	background->Draw(uthEngine.GetWindow());
	moonbase->Draw(uthEngine.GetWindow());

	for (int i = 0; i < turrets.size(); i++)
	{
		GameObject* turret = turrets[i];
		turret->Draw(uthEngine.GetWindow());
	}
	enemyManager.DrawEnemies();
	return true;
}

bool TemplateScene::DeInit()
{

	return true;
}

TemplateScene::TemplateScene()
{

}

TemplateScene::~TemplateScene()
{

}