#ifndef TEMPLATESCENE_HPP
#define TEMPLATESCENE_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Platform/Input.hpp>
#include "Turret.hpp"
#include <UtH/Engine/SpriteBatch.hpp>
#include "EnemyManager.hpp"
#include "TurretManager.hpp"
#include "Button.hpp"
#include <array>
#include <memory>
#include <UtH/Core/Randomizer.hpp>

class TemplateScene : public uth::Scene
{
public:
	TemplateScene();
	~TemplateScene();

	bool Init();
	bool DeInit();

	bool Update(float dt);
	bool Draw();

	int testi,testi2;
	float turretAngle;
	
private:
	uth::Shader shader;
	std::vector<uth::GameObject*> turrets;
	uth::SpriteBatch* spriteBatch;
	uth::GameObject* moonbase;
	uth::GameObject* background;
	uth::GameObject* turret;
	Turret* turretComponent;

	uth::Randomizer* randomizer;

	EnemyManager enemyManager;
	TurretManager turretManager;

	std::array<ns::Button*, 1> m_buttons;

};

#endif