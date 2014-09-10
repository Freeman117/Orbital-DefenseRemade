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

	image = new GameObject();
	image->AddComponent(new Sprite("test2.tga"));
	image->transform.SetPosition(50.0f,50.0f);
	image->transform.SetScale(0.1f);

	turret = new Turret(spriteBatch);
	return true;

}
bool TestScene::DeInit()
{
	return true;
}

bool TestScene::Update(float dt)
{

	if(uthInput.Keyboard.IsKeyPressed(Keyboard::D))
	{
		orbit1angle += PI/3.0f;
		image->transform.SetPosition(100*cosf(orbit1angle),100*sinf(orbit1angle));
		if(constructed == true)
		{
		test2->transform.SetPosition(100*cosf(orbit1angle+PI/3),100*sinf(orbit1angle+PI/3));
		}
	}
	if(uthInput.Keyboard.IsKeyDown(Keyboard::Key1))
	{
	test2 = new GameObject();
	test2->AddComponent(new Sprite("test2.tga"));
	test2->transform.SetPosition(100*cosf(orbit1angle+PI/3),100*sinf(orbit1angle+PI/3));
	test2->transform.SetScale(0.1f);
	test2->transform.SetRotation(45.0f);
	constructed = true;
	}
	if(uthInput.Keyboard.IsKeyDown(Keyboard::Key2))
	{
		turret->AddTurret(1,1,1);
	}
	return true;
}
bool TestScene::Draw()
{
	image->Draw(uthEngine.GetWindow());
	if(constructed == true)
	{
	test2->Draw(uthEngine.GetWindow());
	}
	turret->Draw();
	return true;
}