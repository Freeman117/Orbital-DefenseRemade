#ifndef TEMPLATESCENE_HPP
#define TEMPLATESCENE_HPP

#include <UtH/UtHEngine.hpp>
#include "Turret.hpp"
#include "EnemyManager.hpp"
#include "TurretManager.hpp"
#include "Button.hpp"
#include <array>
#include <memory>


class TemplateScene : public uth::Scene
{
public:
	TemplateScene();
	~TemplateScene();

	bool Init();
	bool DeInit();

	void Update(float dt);

	int testi, testi2, health;
	float enemySpawnFrame;
	float turretAngle;
	float money;

	//void setTestiValue(){ testi2 = 2; }

private:
	//uth::Shader shader;
	uth::GameObject* moonbase;
	uth::GameObject* background;

	uth::GameObject* textBox = new uth::GameObject();
	uth::GameObject* moneyTextBox = new uth::GameObject();

	uth::Text* testText;
	uth::Text* moneyText;
	
	//std::array<ns::Button*, 2> buttons;
	ns::Button* ToggleOrbit;

	uth::Randomizer* randomizer;

	EnemyManager* enemyManager;
	TurretManager* turretManager;
};

#endif