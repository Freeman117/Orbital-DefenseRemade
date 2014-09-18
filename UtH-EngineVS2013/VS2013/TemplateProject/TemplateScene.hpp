#ifndef TEMPLATESCENE_HPP
#define TEMPLATESCENE_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Platform/Input.hpp>
#include "Turret.hpp"
#include <UtH/Engine/SpriteBatch.hpp>


class TemplateScene : public uth::Scene
{
public:
	TemplateScene();
	~TemplateScene();

	bool Init();
	bool DeInit();

	bool Update(float dt);
	bool Draw();

	int testi;

private:
	uth::Shader shader;
	std::vector<uth::GameObject*> turrets;
	uth::SpriteBatch* spriteBatch;
	uth::GameObject* moonbase;
	uth::GameObject* background;
	
};

#endif