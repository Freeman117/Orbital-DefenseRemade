#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include <UtH/UtHEngine.hpp>
#include <pmath/PMath.hpp>
#include "Enemy.hpp"
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Renderer/Texture.hpp>
#include <UtH/Engine/GameObject.hpp>


class EnemyManager : public uth::GameObject
{
public:
	EnemyManager();
	~EnemyManager(){};

	void UpdateEnemies(float deltaTime, int &health);
	void DrawEnemies();
	void SpawnEnemy(float healt, float armor, float speed, float angle);

	std::vector<std::shared_ptr<uth::GameObject>> GetEnemies();
	uth::Texture* enemytexture;
protected:
	std::vector<std::shared_ptr<uth::GameObject>> enemies;
};

#endif