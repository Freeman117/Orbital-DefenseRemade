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
	//bool Draw();

	int testi, testi2, health;
	float enemySpawnFrame;
	float turretAngle;
	float money;
private:
	uth::Shader shader;
	uth::SpriteBatch* spriteBatch;
	uth::GameObject* moonbase;
	uth::GameObject* background;
	uth::GameObject* turret;
	Turret* turretComponent;

	uth::Randomizer* randomizer;

	EnemyManager* enemyManager;
	TurretManager* turretManager;

	std::array<ns::Button*, 1> m_buttons;

};

#endif