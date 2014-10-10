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

class TemplateScene : public uth::Scene
{
public:
	TemplateScene();
	~TemplateScene();

	bool Init();
	bool DeInit();

	void Update(float dt);
	bool Draw();

	int testi;
	float turretAngle;
	
private:
	uth::Shader shader;
	std::vector<uth::GameObject*> turrets;
	uth::SpriteBatch* spriteBatch;
	uth::GameObject* moonbase;
	uth::GameObject* background;
	uth::GameObject* turret;
	Turret* turretComponent;

	EnemyManager enemyManager;
	TurretManager turretManager;

	std::array<ns::Button*, 1> m_buttons;

};

#endif