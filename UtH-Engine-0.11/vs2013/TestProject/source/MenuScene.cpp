#include "MenuScene.hpp"

MenuScene::MenuScene()
{

}

MenuScene::~MenuScene()
{

}

bool MenuScene::Init()
{
//pragma region is just a flavor, you can show/hide the block of code with a comment to make it look nice
#pragma region Camera
	auto& window = uthEngine.GetWindow();
	window.SetCamera(&menuCamera);
	menuCamera.SetSize(1280, 720);
	menuCamera.SetPosition(menuCamera.GetSize() / 2.f);
#pragma endregion Camera
	std::array<uth::Texture*, 2> buttonTextures =
	{
		uthRS.LoadTexture("test.tga"),
		uthRS.LoadTexture("test2.tga")
	};

	for (auto i : buttonTextures)
	{
		if (!i)
		{
			uth::WriteError("Texture loading failed");
			return false;
		}
	}

	buttons[0] = new ns::Button(window, buttonTextures[0]);
	buttons[1] = new ns::Button(window, buttonTextures[1]);

	buttons[0]->setCallBack([]()
	{
		//Start the game scene
		uthSceneM.GoToScene(1);
	});

	buttons[1]->setCallBack([]
	{
		//Exit
		uthEngine.Exit();
	});

	for (size_t i = 0; i < buttons.size(); i++)
	{
		auto b = buttons[i];

		b->transform.SetOrigin(uth::Origin::TopLeft);
		b->transform.SetPosition(100.f, 100.f + (i*50.f) + (i*b->transform.GetSize().y));
		uth::Layer::AddChild(b);
	}

	return true;
}

bool MenuScene::DeInit()
{
	return true;
}

void MenuScene::Update(float dt) //At the moment this isn't very important, unless we want the buttons to move on their own back and forth
{
	/*static const float halfPi = static_cast<float>(pmath::pi) / 2.f;

	static float sine = 0.f;
	static const float initial0 = buttons[0]->transform.GetPosition().y, 
		initial1 = buttons[1]->transform.GetPosition().x;
	sine += dt * halfPi;

	buttons[0]->transform.SetPosition(buttons[0]->transform.GetPosition().x, initial0 + 10.f*std::sinf(sine));
	buttons[1]->transform.SetPosition(buttons[1]->transform.GetPosition().x, initial1 + 10.f*std::sinf(sine));
	*/
	uth::Layer::Update(dt);
}