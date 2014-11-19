#include "TemplateScene.hpp"


using namespace uth;

bool TemplateScene::Init()
{
	//shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	//shader.Use();
	//uthEngine.GetWindow().SetShader(&shader);

	testi = 0;
	testi2 = 1;
	health = 10;
	turretAngle = 0;
	enemySpawnFrame = 0;
	money = 5000.0f;
	
	background = new GameObject();
	AddChild(background);
	background->AddComponent(new Sprite("stars2.png"));
	background->transform.SetScale(0.7f);

	moonbase = new GameObject();
	AddChild(moonbase);
	moonbase->AddComponent(new Sprite("moonBaseMockup2.png"));
	moonbase->transform.SetScale(0.5f);

	AddChild(enemyManager = new EnemyManager());

	AddChild(turretManager = new TurretManager());

	AddChild(moneyTextBox);
	AddChild(textBox);
	textBox->transform.SetPosition(pmath::Vec2f(-512.f,-256.f));
	moneyTextBox->transform.SetPosition(pmath::Vec2f(-512.f, 236.f));

	testText = new Text("kenpixel.ttf", 12.f);
	textBox->AddComponent(testText);
	testText->SetText("TURRET DEFENSE INTENSIFIES",pmath::Vec4(1,0,1,1));
	
	//std::string str("%f", money);

	moneyText = new Text("kenpixel.ttf", 12.f);
	moneyTextBox->AddComponent(moneyText);
	moneyText->SetText("prkl", pmath::Vec4(1, 0, 0, 1));

	return true;
}

void TemplateScene::Update(float dt)
{
	enemySpawnFrame += dt;
#if defined UTH_SYSTEM_WINDOWS
	if (uthInput.Mouse.IsButtonPressed(Mouse::LEFT))
	{
		float targetX = uthInput.Common.Position().x;
		float targetY = uthInput.Common.Position().y;
		float fromX = (float)uthEngine.GetWindow().GetViewport().getRight() / 2;
		float fromY = (float)uthEngine.GetWindow().GetViewport().getBottom() / 2;
		turretManager->RotationChange(atan2f(targetY - fromY, targetX - fromX));
	}
	if (uthInput.Mouse.IsButtonDown(Mouse::LEFT))
	{
		float targetX = uthInput.Common.Position().x;
		float targetY = uthInput.Common.Position().y;
		float fromX = (float)uthEngine.GetWindow().GetViewport().getRight() / 2;
		float fromY = (float)uthEngine.GetWindow().GetViewport().getBottom() / 2;
		turretManager->RotationChange(atan2f(targetY - fromY, targetX - fromX), testi2);
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
		turretManager->RotateTurrets(testi2,2 * dt);
	}

	if (uthInput.Keyboard.IsKeyDown(Keyboard::A))
	{
		turretManager->RotateTurrets(testi2, -2 * dt);
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key1))
	{
		turretManager->UpgradeTurret(money);
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
	{
		turretManager->CreateTurret(1, testi2, testi);

		testi++;
	}
#endif
	
#if defined UTH_SYSTEM_ANDROID
	if (uthInput.Touch[0].Motion() == TouchMotion::TAP)
	{
		pmath::Vec2f target = (uthInput.Touch[0].GetPosition());
		float fromX = uthEngine.GetWindow().GetViewport().getRight() / 2;
		float fromY = uthEngine.GetWindow().GetViewport().getBottom() / 2;
		turretManager->RotationChange(atan2f(target.y - fromY, target.x - fromX), testi2);
	}
#endif

	if (enemySpawnFrame > 8)
	{
		float rand = randomizer->GetFloat(0.0f, 1.0f) * 360;
		for (int i = 0; i < 7; i++)
		{
			enemyManager->SpawnEnemy(50, 3, 50 + randomizer->GetFloat(0, 1) * 15, rand + randomizer->GetInt(0, 40));
		}
		enemySpawnFrame -= 8;
		//enemyManager->SpawnEnemy(150, 3, 50, 60);
		//enemyManager->SpawnEnemy(250, 3, 60, 70);
		//enemyManager->SpawnEnemy(150, 3, 50, 80);
		//enemyManager->SpawnEnemy(250, 3, 60, 90);
		//enemyManager->SpawnEnemy(150, 3, 50, 100);
		//enemyManager->SpawnEnemy(250, 3, 60, 110);
	}

	//float randomi = randomizer->GetFloat(0.f, 1.f);
	//float randomi2 = randomizer->GetFloat(0.f, 1.f);
	//textBox->transform.SetPosition(-450.f+10.f*randomi, -256.f+10.f*randomi2);

	turretManager->UpdateTurrets(dt, enemyManager);
	enemyManager->UpdateEnemies(dt, health);
	turretManager->UpdateBullets(dt, enemyManager);

	Scene::Update(dt);
	return;
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