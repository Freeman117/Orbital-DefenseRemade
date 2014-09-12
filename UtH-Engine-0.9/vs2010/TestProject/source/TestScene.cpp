#include "TestScene.hpp"

#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

const unsigned int sprites = 40;

TestScene::TestScene()
{}
TestScene::~TestScene()
{}

bool TestScene::Init()
{
	shader = new Shader();
	shader->LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	shader->Use();
    uthEngine.GetWindow().SetViewport(umath::rectangle(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
    uthEngine.GetWindow().SetShader(shader);

	orbit1angle = 0.0f;
	orbit2angle = 0.0f;
	orbitpos = 0;
	constructed = false;

	turret = new Turret(spriteBatch);
	return true;

}
bool TestScene::DeInit()
{
	return true;
}

bool TestScene::Update(float dt)
{
	if(uthInput.Keyboard.IsKeyPressed(Keyboard::Right))
	{
		turret->Update(dt,1);
	}

	if(uthInput.Keyboard.IsKeyPressed(Keyboard::D))
	{
		//turret->Update(dt,2);
	}
	if(uthInput.Keyboard.IsKeyPressed(Keyboard::Key2))
	{
		turret->AddTurret(1,1,1);
	}
	if(uthInput.Keyboard.IsKeyPressed(Keyboard::Key3))
	{
		//turret->AddTurret(2,1,1);
	}
	return true;
}
bool TestScene::Draw()
{
	turret->Draw();
	return true;
}