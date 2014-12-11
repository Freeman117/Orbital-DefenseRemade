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
	moneyTextBox->transform.SetPosition(pmath::Vec2f(-512.f, -236.f));

	testText = new Text("kenpixel.ttf", 12.f);
	textBox->AddComponent(testText);
	testText->SetText("TURRET DEFENSE INTENSIFIES",pmath::Vec4(1,0,1,1));
	
	moneyText = new Text("kenpixel.ttf", 12.f);
	moneyTextBox->AddComponent(moneyText);
	
	std::array<uth::Texture*, 2> buttonTextures =
	{
		uthRS.LoadTexture("particle.png"),
		uthRS.LoadTexture("particle.png")
	};
	buttons[0] = new ns::Button(uthEngine.GetWindow(), buttonTextures[0]);
	buttons[1] = new ns::Button(uthEngine.GetWindow(), buttonTextures[1]);

	buttons[0]->setCallBack([&]()
	{
		testi2 = 2;
	});
	buttons[1]->setCallBack([&]()
	{
		testi2 = 1;
	});

	buttons[0]->transform.SetPosition(pmath::Vec2f(-512.f,-200.f));
	buttons[1]->transform.SetPosition(pmath::Vec2f(-512.f,-200.f+buttons[0]->transform.GetSize().y+40.f));

	for (int i = 0; i < buttons.size(); i++)
	{
		auto b = buttons[i];
		uth::Layer::AddChild(b);
		b->transform.SetScale(2.0f);
	}

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
		//turretManager->poisto();
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
	{
		turretManager->CreateTurret(2, testi2, testi);

		testi++;
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Escape))
	{
		uthEngine.Exit();
	}
#endif
	
#if defined UTH_SYSTEM_ANDROID
	if (uthInput.Touch[0].Motion() == TouchMotion::DRAG)
	{
		pmath::Vec2f target = (uthInput.Touch[0].GetPosition());
		float fromX = uthEngine.GetWindow().GetViewport().getRight() / 2;
		float fromY = uthEngine.GetWindow().GetViewport().getBottom() / 2;
		turretManager->RotationChange(atan2f(target.y - fromY, target.x - fromX), testi2);
	}
#endif
	enemyManager->UpdateWaves(dt);

	//textBox->transform.SetPosition(-512.f + 10.f*randomi, -256.f + 10.f*randomi2);

	turretManager->UpdateTurrets(dt, enemyManager);
	enemyManager->UpdateEnemies(dt, health);
	turretManager->UpdateBullets(dt, enemyManager);
	
	std::stringstream mn;
	mn << money;
	moneyText->SetText(mn.str(), pmath::Vec4(1, 0, 0, 1));

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