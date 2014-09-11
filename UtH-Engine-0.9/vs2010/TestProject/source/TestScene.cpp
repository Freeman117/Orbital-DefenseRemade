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
<<<<<<< HEAD
=======

>>>>>>> origin/master
	shader = new Shader();
	shader->LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	shader->Use();
    uthEngine.GetWindow().SetViewport(umath::rectangle(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
    uthEngine.GetWindow().SetShader(shader);

<<<<<<< HEAD
	orbit1angle = 0.0f;
	orbit2angle = 0.0f;
	orbitpos = 0;
	constructed = false;
=======
	test = new GameObject();
	test->AddComponent(new Sprite(umath::vector4(1,0,0,1),umath::vector2(128,128)));

	herp = new GameObject();
	herp->AddComponent(new Sprite(umath::vector4(0,0,1,1),umath::vector2(128,128)));
	herp->transform.SetPosition(128.0f,128.0f);

	orbit1angle = 0.0f;
	orbit2angle = 0.0f;
>>>>>>> origin/master

	image = new GameObject();
	image->AddComponent(new Sprite("test2.tga"));
	image->transform.SetPosition(50.0f,50.0f);
	image->transform.SetScale(0.1f);
<<<<<<< HEAD

	turret = new Turret(spriteBatch);
=======
>>>>>>> origin/master
	return true;

}
bool TestScene::DeInit()
{
	return true;
}

bool TestScene::Update(float dt)
{
<<<<<<< HEAD

=======
	if(uthInput.Keyboard.IsKeyDown(Keyboard::Up))
	{
		herp->transform.Move(0,-1.0f);
	}
>>>>>>> origin/master
	if(uthInput.Keyboard.IsKeyPressed(Keyboard::D))
	{
		orbit1angle += PI/3.0f;
		image->transform.SetPosition(100*cosf(orbit1angle),100*sinf(orbit1angle));
<<<<<<< HEAD
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
=======
>>>>>>> origin/master
	}
	return true;
}
bool TestScene::Draw()
{
<<<<<<< HEAD
	image->Draw(uthEngine.GetWindow());
	if(constructed == true)
	{
	test2->Draw(uthEngine.GetWindow());
	}
	turret->Draw();
=======
	test->Draw(uthEngine.GetWindow());
	herp->Draw(uthEngine.GetWindow());
	image->Draw(uthEngine.GetWindow());

>>>>>>> origin/master
	return true;
}