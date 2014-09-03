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

	test = new GameObject();
	test->AddComponent(new Sprite(umath::vector4(1,0,0,1),umath::vector2(128,128)));

	herp = new GameObject();
	herp->AddComponent(new Sprite(umath::vector4(0,0,1,1),umath::vector2(128,128)));
	herp->transform.SetPosition(128.0f,128.0f);

	return true;
}
bool TestScene::DeInit()
{
	return true;
}

bool TestScene::Update(float dt)
{
	if(uthInput.Keyboard.IsKeyDown(Keyboard::Up))
	{
		herp->transform.Move(0,1.0f);
	}
	return true;
}
bool TestScene::Draw()
{
	test->Draw(uthEngine.GetWindow());
	herp->Draw(uthEngine.GetWindow());
	return true;
}