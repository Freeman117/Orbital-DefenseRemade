#include "TemplateScene.hpp"
#include <UtH/Engine/UtHEngine.h>

using namespace uth;

bool TemplateScene::Init()
{
	shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	shader.Use();
	uthEngine.GetWindow().SetShader(&shader);

	turret = new Turret(spriteBatch);

	return true;
}

bool TemplateScene::Update(float dt)
{
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Right))
	{
		turret->Update(dt, 1);
	}

	if (uthInput.Keyboard.IsKeyPressed(Keyboard::D))
	{
		//turret->Update(dt,2);
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
	{
		turret->AddTurret(1, 1, 1);
	}
	if (uthInput.Keyboard.IsKeyPressed(Keyboard::Key3))
	{
		//turret->AddTurret(2,1,1);
	}
	return true;
}

bool TemplateScene::Draw()
{
	turret->Draw();

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