#include "TemplateScene.hpp"


using namespace uth;

bool TemplateScene::Init()
{
	shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	shader.Use();
	uthEngine.GetWindow().SetShader(&shader);

	testi = 0;
	turretAngle = 0;

	background = new GameObject();
	AddChild(background);
	background->AddComponent(new Sprite("stars2.png"));
	background->transform.SetScale(0.7f);

	moonbase = new GameObject();
	AddChild(moonbase);
	moonbase->AddComponent(new Sprite("moonBaseMockup2.png"));
	moonbase->transform.SetScale(0.5f);

	
	std::array<uth::Texture*, 1> buttonTextures =
	{
		uthRS.LoadTexture("test.tga")
	};

	m_buttons[0] = new ns::Button(uthEngine.GetWindow(), buttonTextures[0]);

	m_buttons[0]->setCallBack([]()
	{
		WriteLog("KAIKKI KUOLI SAATANA");
	});

	for (int i = 0; i < m_buttons.size(); i++)
	{
		auto b = m_buttons[i];

		b->transform.SetPosition(0, 0);
		b->transform.SetScale(0.4f);
		AddChild(b);
	}
	
	
	return true;
}

void TemplateScene::Update(float dt)
{


		if (uthInput.Keyboard.IsKeyDown(Keyboard::D))
		{
			turretManager.RotateTurrets(1,2 * dt);
		}

		if (uthInput.Keyboard.IsKeyDown(Keyboard::A))
		{
			turretManager.RotateTurrets(1, -2 * dt);
		}
		if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
		{

			turretManager.CreateTurret(1, 1, testi);

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

		turretManager.UpdateTurrets(dt, &enemyManager);
		enemyManager.UpdateEnemies(dt);
		turretManager.UpdateBullets(dt, &enemyManager);
		for (int i = 0; i < m_buttons.size(); i++)
		{
			m_buttons[i]->Update(dt);
		}

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