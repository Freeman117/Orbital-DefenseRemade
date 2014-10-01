#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include <UtH/Engine/UtHEngine.h>
#include <pmath/PMath.hpp>
#include "Enemy.hpp"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager(){};

	void UpdateEnemies(float deltaTime);
	void DrawEnemies();
	void SpawnEnemy(float healt, float armor, float speed, float angle);

	std::vector<uth::GameObject*> GetEnemies();

protected:
	std::vector<uth::GameObject*> enemies;
};

#endif ENEMYMANAGER_HPP