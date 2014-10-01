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
	enemyManager.UpdateEnemies();
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::D))
	{
<<<<<<< HEAD
		turretAngle += 2 * dt;
=======
		if (turrets.size() < 1)
		{
			return true;
		}
		for (int i = turrets.size() - 1; i >= 0; i--)
		{
			
		}
>>>>>>> origin/master
	}

	if (uthInput.Keyboard.IsKeyPressed(Keyboard::D))
	{

	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
	{
		
	    GameObject* turret = new uth::GameObject();
		turret->AddComponent(new uth::Sprite("CannonTower.png"));
		turret->transform.SetScale(0.30f);
		turret->AddComponent(new Turret(1,1,testi));
		turrets.push_back(turret);
		
		testi++;
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key3))
	{
		enemyManager.SpawnEnemy();
	}
	if (uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
	{
		//uthInput.Mouse.Position();
	}

	if (turrets.size() >= 1)
	{
		for (int i = turrets.size() - 1; i >= 0; i--)
		{
			uth::GameObject* turret = turrets[i];
			Turret* turret_c = turret->GetComponent<Turret>("Turret");
			turret->transform.SetPosition(cosf(turretAngle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit, sinf(turretAngle + turret_c->orbitPos*(pmath::pi / 3)) * 100 * turret_c->orbit);
		}
	}

	return true;
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