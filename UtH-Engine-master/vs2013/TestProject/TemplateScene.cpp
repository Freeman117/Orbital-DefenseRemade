#include "TemplateScene.hpp"
#include <Uth/Engine/Engine.hpp>

using namespace uth;

bool TemplateScene::Init()
{
	shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	shader.Use();
	uthEngine.GetWindow().SetShader(&shader);

	testi = 0;
	testi2 = 1;
	health = 10;
	turretAngle = 0;
	moonbase = new GameObject();
	moonbase->AddComponent(new Sprite("moonBaseMockup2.png"));
	moonbase->transform.SetScale(0.5f);

	background = new GameObject();
	background->AddComponent(new Sprite("stars2.png"));
	background->transform.SetScale(0.7f);
	
	enemySpawnFrame = 0;

	std::array<uth::Texture*, 1> buttonTextures =
	{
		uthRS.LoadTexture("test2.tga")
	};

	m_buttons[0] = new ns::Button(uthEngine.GetWindow(), buttonTextures[0]);

	m_buttons[0]->setCallBack([]()
	{
		WriteLog("Button press detected");
	});

	m_buttons[0]->transform.SetPosition(0,0);

	return true;
}

bool TemplateScene::Update(float dt)
{
	enemySpawnFrame += dt;
	if (uthInput.Mouse.IsButtonPressed(Mouse::LEFT))
	{
		float targetX = uthInput.Common.Position().x;
		float targetY = uthInput.Common.Position().y;
		float fromX = (float)uthEngine.GetWindow().GetViewport().getRight() / 2;
		float fromY = (float)uthEngine.GetWindow().GetViewport().getBottom() / 2;
		turretManager.RotationChange(atan2f(targetY-fromY,targetX-fromX));
	}
	if (uthInput.Mouse.IsButtonDown(Mouse::LEFT))
	{
		float targetX = uthInput.Common.Position().x;
		float targetY = uthInput.Common.Position().y;
		float fromX = (float)uthEngine.GetWindow().GetViewport().getRight() / 2;
		float fromY = (float)uthEngine.GetWindow().GetViewport().getBottom() / 2;
		turretManager.RotationChange(atan2f(targetY - fromY, targetX - fromX),testi2);
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::W))
	{
		testi2 = 2;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::S))
	{
		testi2 = 1;
	}
	if (uthInput.Keyboard.IsKeyDown(Keyboard::D))
	{
		turretManager.RotateTurrets(testi2,2 * dt);
	}

	if (uthInput.Keyboard.IsKeyDown(Keyboard::A))
	{
		turretManager.RotateTurrets(testi2, -2 * dt);
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
	{

		turretManager.CreateTurret(1, testi2, testi);

		testi++;
	}
	if (enemySpawnFrame > 8)
	{
		float rand = randomizer->GetFloat(0.0f, 1.0f) * 360;
		for (int i = 0; i < 7; i++)
		{
			enemyManager.SpawnEnemy(50, 3, 50 + randomizer->GetFloat(0, 1) * 15, rand + randomizer->GetInt(0, 40));
		}
		//enemyManager.SpawnEnemy(50, 3, 50, randomizer->GetInt(0,360));
		//enemyManager.SpawnEnemy(50, 3, 60, randomizer->GetInt(0,360));
		//enemyManager.SpawnEnemy(50, 3, 50, randomizer->GetInt(0,360));
		//enemyManager.SpawnEnemy(50, 3, 60, randomizer->GetInt(0,360));
		//enemyManager.SpawnEnemy(50, 3, 50, randomizer->GetInt(0,360));
		//enemyManager.SpawnEnemy(50, 3, 60, randomizer->GetInt(0,360));
		enemySpawnFrame -= 8;
	}
	if (uthInput.Mouse.IsButtonPressed(uth::Mouse::LEFT))
	{
		//uthInput.Mouse.Position();
	}


	turretManager.UpdateTurrets(dt, &enemyManager);
	enemyManager.UpdateEnemies(dt, health);
	turretManager.UpdateBullets(dt, &enemyManager);
	std::cout << health << std::endl;
	return true;
}
bool TemplateScene::Draw()
{

	background->Draw(uthEngine.GetWindow());
	if (health > 0)
	moonbase->Draw(uthEngine.GetWindow());

	turretManager.DrawTurrets();
	enemyManager.DrawEnemies();
	turretManager.DrawBullets();
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