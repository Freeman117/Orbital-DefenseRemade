#ifndef TEMPLATESCENE_HPP
#define TEMPLATESCENE_HPP

#include <UtH/Engine/Engine.hpp>
#include <UtH/Platform/Input.hpp>
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
private:
	uth::Shader shader;
	uth::GameObject* moonbase;
	uth::GameObject* background;
	uth::GameObject* textBox = new uth::GameObject();
	uth::Text* testText;
	uth::Randomizer* randomizer;

	EnemyManager* enemyManager;
	TurretManager* turretManager;
};

#endif